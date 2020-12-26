#include <iostream>
#include "node.hpp"

using namespace std;

// this constructor is for virtual node only
// the constructor for inner node is implemented in the node.hpp file
p_node::p_node() {

    //--------------
    up=nullptr;
    down=nullptr;
    left=nullptr;
    right=nullptr;
    root=this; // root point to himself 
    next_traversal=nullptr; // next traversal node in the search

    //--------------
    virtual_root_node=true; // is this a visrtual root node?

    // position initialized to -1 is the node ios just virtual
    pos_c=-1; // posizione di colonna 
    pos_r=-1; // posizione di riga
    node_val=-1; //-1 is a virtual node, 0 closed node, 1 open node can be connected for percolation

};


// build network function
// 1 build virtual element
// build all elements and link with traversal network
// links also Vtop and Vbot
p_node* build_net(const int &dim){

p_node *root_n= new p_node(); // init the virtual node

p_node *bottom_root_n = new p_node(); // init the virtual node

p_node *prev = root_n;

root_n->dim=dim;
  

    for (int j=0;j<dim;j++) 
    {

        for (int k=0;k<dim;k++) 
        {
                p_node *node =new p_node(j,k); // make a new node
                node->dim=dim; // save the dimension
                prev->next_traversal = node; // point the old node to the nex one
                node->prev_traversal = prev;
                prev = node; // the address of prev is node now
        }

    }
    // link the bottom virtual node to the traversal network
    prev->next_traversal=bottom_root_n; 
    bottom_root_n->prev_traversal=prev;
    // connect the bottom virtual node to the upper virtual node
    // that connetion makes the net circular
    bottom_root_n->next_traversal = root_n;
    root_n->prev_traversal=bottom_root_n;
    bottom_root_n->down = root_n;
    // double link the 2 virtual nodes via upper link also
    // now the upper virtual node is connected sing the UP link to the
    // bottom virtual node.
    root_n->up=bottom_root_n;
    // give Vbot the asme root as Vtop 
    bottom_root_n->root=root_n;

    return root_n;

}


// print traversal network 
void print_traversal_net( p_node * root , int dim) 
{

        p_node *node  = root;

        for (int i=0;i<(dim*dim)+1;i++) 
            {
                std::cout<<node->pos_r <<" "<<node->pos_c<<std::endl;

                node = node->next_traversal;   
            }
}


// print net vertically touching all elements from 
// top to down and from left to right
void print_vertical_net(p_node * root, int dim){

    p_node *node  = root->next_traversal;

     p_node *node_rc  = node;

    for (int j = 0;j<dim;j++) {


            for (int k =0;k<dim;k++) 
            {
                    std::cout<<"("<<node->pos_r<<" "<<node->pos_c<<") ";

                    node = node->down;
            }

            node_rc = node_rc->right;
            node = node_rc;
            std:cout<<std::endl;
    }

    std::cout<<std::endl;
}

// print network by values
// making a vetical scan
void print_values_net(p_node * root, int dim)
    {
    p_node *node  = root->next_traversal;

    for (int i = 0;i<dim*dim;i++) 
        {
           
                if (i%dim==0)
                        {

                        
                        std:cout<<std::endl;

                        }

            std::cout<<"("<<node->node_val<<") ";
            node = node->next_traversal;
           
        }

    std::cout<<std::endl;
}


// print net before percolation process
void print_graphical_net(p_node *root, int dim){

 p_node *node  = root->next_traversal;

    for (int i = 0;i<dim*dim;i++) 
        {
           
                if (i%dim==0)
                        {

                            std:cout<<std::endl;

                        }
                if(node->node_val==1)
                        {

                        std::cout<<" "; // perculation flow

                        }
                else 
                        if (node->node_val==0) 
                            {
                            std::cout<<"¤";
                            }

                                 
                            

            node = node->next_traversal;
           
        }

    std::cout<<std::endl;


}

// print non null fatherhood
// this print will give an overview on connected items
void print_common_father(p_node *root, int dim){

 p_node *node  = root->next_traversal;

    for (int i = 0;i<dim*dim;i++) 
        {
           
                if (i%dim==0)
                        {

                            std:cout<<std::endl;

                        }
            if(node->root!=nullptr)
                    {

                        std::cout<<"#"; // perculation flow

                    }
                        else if (node->node_val==1) {std::cout<<" ";}

                                else   { std::cout<<"+";}

                            

            node = node->next_traversal;
           
        }

    std::cout<<std::endl;
    }







// search element by position r,c
p_node * search_by_pos ( p_node *root,  const int r , const int  c , int dim){

 p_node  *node = root->next_traversal; // I need to bypass the first virtual node

 for (int j=0;j<dim;j++) {

     for (int k=0;k<dim;k++) {

            if (node->pos_c == c && node->pos_r == r) 
                
                {  
                    return node; 
                }

                else 
                {
                    node = node->next_traversal; // switch to next node
                }

     }

 }
        return nullptr; // if none is found return nullptr

}


// linking node process
// need search_by_pos
p_node * build_neighbour( p_node * root , int dim) {

p_node  *node = root->next_traversal; //  I need to bypass the first virtual node

for (int i=0;i<(dim*dim);i++) {

            // upper link for the first row is the virtual node
            if(node->pos_r==0) 
                    
                    {
                        node->up=root; 
                    }

            // top virtual and bottom virtual are connected
            // top virtual is conencted to the bottom via upper link
            // bottom virtual is conencted to the top via down link and trasversal
            if (node->pos_r==dim-1) 
            {
                   // root up is connected  othe virtual bottom 
                   node->down = root->prev_traversal;


            }

            // check DOWN+up link
            if (node->pos_r<(dim-1) &&  node->down == nullptr) 
            { 
                
                node->down = search_by_pos( root, (node->pos_r)+1 ,(node->pos_c), dim); // save downer node

                node->down->up = node; // save upper node
                
            }            

        
            // check right+left link
            if (node->pos_c<(dim-1) &&  node->right == nullptr) 
            { 
                
                node->right = search_by_pos( root, (node->pos_r) ,(node->pos_c)+1, dim); // save right node

                node->right->left = node; // save left node
                
            }  
           
            node = node->next_traversal; // shift node


    }

return root;
}

void build_neighbour_light(p_node  * root){

p_node *node = root->next_traversal;

int dim = root->dim;

for (int i=0;i<(dim*dim);i++) {

            // upper link for the first row is the virtual node
            if(node->pos_r==0) 
                    
                    {
                        node->up=root; 
                    }

            // top virtual and bottom virtual are connected
            // top virtual is conencted to the bottom via upper link
            // bottom virtual is conencted to the top via down link and trasversal
            if (node->pos_r==dim-1) 
            {
                   // root up is connected  othe virtual bottom 
                   node->down = root->prev_traversal;


            }

            // scan node
            if (node->pos_r>=0 && node->pos_r<(dim-1)) {

                    p_node * node_t = node;

                    // move node_t traversally of n-dim positions
                    for (int i =0 ;i<dim;i++) 
                    {

                            node_t = node_t->next_traversal;

                    }

                    node->down = node_t;
                    node_t->up = node;


            }


            // upper link for the first row is the virtual node
            if(node->pos_c==0) 
                    
                    {
                        node->right=node->next_traversal;
                        node->next_traversal->left = node; 
                    }

            if(node->pos_c==dim-1) 
                    
                    {
                        node->left=node->prev_traversal;
                        node->prev_traversal->right= node; 
                    }

             if (node->pos_c>=0 && node->pos_c<(dim-1)) {

                    p_node * node_t = node;

                    // move node_t traversally of n-dim positions
                    

                    node_t = node_t->next_traversal;

                
                    node->right = node_t;
                    node_t->left = node;


            }

           
            node = node->next_traversal; // shift node


    }





}



// checl all 
void p_node::establish_node_belonging_to_root(){


        bool found_root=false;

        // if this node is not blocked
        if (this->node_val==1){

            // up left right and down are set in neighbor net function 

                if(this->up!= nullptr && this->up->root!=nullptr) // VIRTUAL NODE *root = self
                
                    {

                        this->root=this->up->root;
                        found_root=true;
                                

                    }                
                    
                if(this->left!=nullptr && this->left->root!=nullptr) 
                
                    {

                        this->root=this->left->root;
                        found_root=true;        

                    }   

                if(this->right!=nullptr && this->right->root!=nullptr) 
                
                    {

                        this->root=this->right->root;
                        found_root=true;        

                    }  

                 if(this->down!=nullptr && this->down->root!=nullptr && this->down->node_val!=-1) 
                
                    {

                        this->root=this->down->root;
                        found_root=true;        

                    }  


                // we check up down left and right if we found a root we change anything else
                if (found_root){


                        if (this->pos_r>0 &&/*this->up!=nullptr &&*/ this->up->node_val==1)
                         {
                                this->up->down = this;
                                this->up->root=this->root;
                         }

                        if (this->pos_c>0 &&/*this->left!=nullptr &&*/ this->left->node_val==1)
                        {
                                this->left->right = this;
                                 this->left->root=this->root;
                        }


                        if (this->pos_c<this->dim-1 &&/*this->right!=nullptr &&*/ this->right->node_val==1)
                        {
                                this->right->left = this;
                                 this->right->root=this->root;
                        }


                        if (this->pos_r<this->dim-1 &&/*this->down!=nullptr &&*/ this->down->node_val==1) 
                        {
                                this->down->up = this;
                                this->down->root=this->root;
                        }

                

                }


                
        }


};


// reset node links if is zero
void p_node::reset_node_on_zero()
        {
                this->root=nullptr;
        }



//fill net with p closed node and 1-p open node
// input probability for a node to be open and root node
void fill_net(p_node *root,const double &p, int dim){

        srand(time(NULL));

        p_node * node = root->next_traversal; // skip 1st visrtual node

        for (int i = 0;i<dim*dim;i++) {

        // generation of random number
        double r = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX)+1.0 );

        // check if the node == 0 at the start all nodes are blocked
                    if (node->node_val==0) 
                                {

                                if (p>=r) {  node->node_val=1;  }  else 
                                        { 
                                                // set the value to 0 to be closed
                                                node->node_val=0; 
                                                // reset node pointers so they dont 
                                                // connect to anything exept trasversal links
                                                node->reset_node_on_zero();        
                                        }

                                }
                                    node = node->next_traversal;


        }


}


// i need to check every node pathernal common root
// this funciton will check every neighnour and will 
//fix the common root for erach of them
void check_every_node_openspace(p_node * root, const int &dim){

 p_node * node = root->next_traversal; // skip virtual node

 for (int i =0; i<dim*dim; i++) {

     node->establish_node_belonging_to_root();

     node = node->next_traversal;

 }


}