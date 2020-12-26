#include <iostream>
#include <cstdlib> // randomization
#include <ctime> // randomizatio timer
#include <cmath>
#include "node.hpp"



int main()
{
    int dim;  // matrix dimension
    
    double p; // matrix probability to be open

    std::cout<<"Insert sqare side lenght: "<<std::endl;
    std::cin>>dim;


    std::cout<<"Insert probability for a node to be open: "<<std::endl;
    std::cin>>p;

    // build my net and double-link traversal
    p_node *root = build_net(dim);

    // estabilish link to each node with neighbors 
    //root = build_neighbour( root, dim );
    build_neighbour_light(root);

    // fill net with random values of probability p (ex 0.5)
    fill_net(root,p,dim);
    
    //print TUI of the net
    print_graphical_net(root,dim);
    
    // recycle the net to cover all missed spots
    for (int i =0;i<dim;i++)
            {
            check_every_node_openspace(root,dim);
            }
        
    print_common_father(root,dim);

   
    return 0;
}

