#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "/usr/kraken/include/resolve_dep.h"
#include "/usr/kraken/include/graph.h"



void resolve_dep(Graph *graph)
{

  printf("i find the graph");
  for (int i=0;i<graph->nbr_node;i++){
 
    graph->node_array[i]->visited=0;
   


  }


  for (int i=0;i<graph->nbr_node;i++){


    if(!graph->node_array[i]->visited){

      
      install_pkg_dfs(graph->node_array[i]);
    }
 

  }

  

  
}


void install_pkg_dfs(Node *node){

  if (node->visited){
    return;



  }

  for (int i=0;i<node->nbr_dep;i++){

    install_pkg_dfs(node->dep_array[i]);


  }

  printf("[install] %s-%s \n",node->pkg_name,node->version);


  char command [512];


  // Download  the package in /sources
   snprintf(command, sizeof(command),"sudo kraken download %s",node->pkg_name);
    system(command);


  // Prepare for the build

    snprintf(command, sizeof(command), "sudo kraken prepare %s", node->pkg_name);

    system(command);


    // Build the package

    snprintf(command, sizeof(command), "sudo kraken build %s", node->pkg_name);

    system(command);

    //TBD: WE NEED TO RESOLVE THIS TEST MAYBE WE NEED TO ASK THE USER BEFORE START TESTING THE PACKAGE 
    // Test the package

    // snprintf(command, sizeof(command), "sudo kraken test %s", node->pkg_name);

    // system(command);
      
    // preinstall
    snprintf(command, sizeof(command), "sudo kraken preinstall  %s", node->pkg_name);

    system(command);
  
    //fake isntall the package 

    snprintf(command, sizeof(command), "sudo kraken fakeinstall  %s", node->pkg_name);

    system(command);
    // Install the package

    snprintf(command, sizeof(command), "sudo kraken install %s", node->pkg_name);

    system(command);

    // postinstall
    snprintf(command, sizeof(command), "sudo kraken postinstall  %s", node->pkg_name);

    system(command);

    node->visited = 1;


  
}
