#include <iostream>
#include <string>

class p_node {

public:
    //constructors
    p_node(); // virtual root constructor
    p_node(int r,int c){pos_r=r;pos_c=c; virtual_root_node=false; node_val=0;} // only the position is initialized all the rest is not

    // check 4 neighbour to identify open or close
    void establish_node_belonging_to_root();

    // reset all links and var of the node is not open value = (1)
    void reset_node_on_zero();

    // moving pointers
    p_node * up;
    p_node *down;
    p_node *left;
    p_node *right;
    //----------------

    p_node *next_traversal; // next traversal node in the search
    p_node *prev_traversal; // previous traversal node in the search
    p_node *root; // point to the root node helps to identify different subsetsin the system



    bool virtual_root_node; // is this a root node?

    // postion and value of the node
    int node_val; //-1 virtual node , 0 closed node , 1 open node. 
    int pos_r;
    int pos_c;
    int dim; 


    


};


// NET FUNCTIONS

// build a network function with traversal connection via traversal node
// output the root of the net.
p_node * build_net(const int &dim);
// print traversal noed of the net , nodes will be kept and trated in sequence
void print_traversal_net( p_node * , int);
// print net vertically touching all elements from top to down and from left to right
void print_vertical_net(p_node *, int);
// print node values as a matrix
void print_values_net(p_node *, int);
// print graphical net before percolation process
void print_graphical_net(p_node *, int);
// print non null fatherhood
// this print will give an overview on connected items
void print_common_father(p_node *, int);
// search node by position r,c
p_node * search_by_pos ( p_node *,  const int  , const int , int );
// stabilish link with neighbourood
p_node * build_neighbour( p_node *  , int );
//estabilish links in a lighter and more efficient way than th eprevious
void build_neighbour_light(p_node  *);
//fill net with p closed node and 1-p open node
// input probability for a node to be open and root node
void fill_net(p_node *root,const double &p, int dim);
// i need to check every node pathernal common root
// this funciton will check every neighnour and will 
//fix the common root for erach of them
void check_every_node_openspace(p_node * node, const int &dim);


