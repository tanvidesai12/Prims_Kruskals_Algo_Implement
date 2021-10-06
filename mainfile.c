#include<stdio.h>
#include<stdlib.h>
#include"adj.h"
void main()
{
	int ch,n,max_edges;
	Graph *graph=NULL;
	printf("\t\tImplementation of Graph using adjacency list and finding Minimum Spanning Tree using Prim's algorithm & Kruskal's algorithm\t\t\n\n");
	do{
		printf("\n1:Create Graph.\n");	
		printf("\n2:Display Adjacency List For The Graph\n");
		printf("\n3.Min Spanning Tree using Prims algorithm\n");
		printf("\n4.Min Spanning Tree using Kruskals algorithm\n");
		printf("\n5:Exit.\n");
		printf("\n\nEnter Your Choice:");
		scanf("%d",&ch);
		switch(ch)
		  {
			case 1:	printf("\n\nEnter Number Of Vertices (The vertices will be named in alphabetical order) : ");
				scanf("%d",&n);
				max_edges=(n*(n-1))/2;
				printf("Maximum number of edges %d",max_edges);
				graph = createGraph(n);
				addEdge(graph);
				printf("\nAll edges are added sucessfully.\n");
				break;

          		case 2:printf("\n The adjacency list for the graph is");
				display(graph);
				break;
				
			case 3:printf("\nPrims Algorithm\n");
				prims(graph);
				break;
				
			case 4:printf("\nKruskal's Algorithm\n");
				kruskal(graph);
				break;
				
			case 5:break;
			default : printf("Invalid Choice\n" );
		}
		  
	}while(ch!=5);
           
}
   
