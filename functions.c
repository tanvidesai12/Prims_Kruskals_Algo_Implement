#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include"adj.h"
node* createNode(keytype v,int weight)//creating nodes
{
	node* newNode = malloc(sizeof(node));
	newNode->vertex = v;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}
 

Graph* createGraph(int vertices)//creates the adjlist list
{
	int i,ch=97;
	adjlist *prev=NULL;
	adjlist *first=NULL;
	Graph* graph =(Graph*)malloc(sizeof(Graph));
	graph->numVertices = vertices;//num vertices

	for (i = 0; i < vertices; i++)//initialising adjlist
	{  
		adjlist *temp=(adjlist*)malloc(sizeof(adjlist)); 
	 	temp->vertex=ch++; 
		temp->right=NULL;
		if(prev!=NULL)
		{
			prev->next=temp; 
			temp->next=NULL;
		}
		else
		{
			temp->next=prev;		
			first=temp;
		}
		prev=temp;
	} 
	graph->head=first;
	return graph;
}
 
void addEdge(Graph* graph)//for each vertex in adjlist ,it adds edges adjacent to it
{
	int i,weight;
	char dest,ch='y',v;
	node *prev=NULL,*tmp;
	adjlist *temp=graph->head;
	i=0;
	while(i<((graph->numVertices)-1))//each edge can be connected to other n-1 edges
	{
		if(ch=='y')
		{
			printf("\nEnter the destination vertex for vertex %c:",temp->vertex);
			scanf(" %c",&dest);
			printf("\nEnter the weight for %c - %c edge:",temp->vertex,dest);
			scanf("%d",&weight);
			node* newNode = createNode(dest,weight);
			if(temp->right==NULL)
				temp->right=newNode;
			else
			{
				tmp=temp->right;
				while(tmp->next!=NULL)
					tmp=tmp->next;
				tmp->next=newNode;
			}
			printf("\nDo you want to continue for vertex %c??[y/n]:",temp->vertex);
			scanf(" %c",&ch);
			
		}
		i++;			
		if(ch=='n')
		{
			if(temp->next!=NULL)
			{
				temp=temp->next;
				ch='y';
				i=0;
				
			}
			else 
				break;
		}
		
	}
	if(i==((graph->numVertices)-1)&&temp->next!=NULL)//if user tries to enter more than possible number of adjacent edges for each vertex
		printf("\nInvalid data..");
   
}
void display(Graph* graph)//displays the adjacency list for the graph created
{
	adjlist *temp=graph->head;
	node *tmp;
	while(temp!=NULL)
	{
		printf("\n %c:",temp->vertex);
		tmp=temp->right;
		while(tmp!=NULL)
		{
			printf("-> %c [%d]",tmp->vertex,tmp->weight);
			tmp=tmp->next;
		}
		temp=temp->next;
	}
}
char is_mst(mst *start,keytype ch)//checks if vertex ch is present in the mstSet,returns 'f' if not present
{
	char val='f';
	mst *temp=start;//temp pointer to traverse through the list
	while(temp!=NULL)
	{
		if(temp->v==ch)
			val='t';
		temp=temp->nxt;
	}
	return val;
}
char find_small(keylist *first,mst *start)//finds the vertex with smallest key value and which is not included in the mstSet
{
	keylist *temp=first;
	int small=INT_MAX;
	char s_vertex;//smallest vertex
	while(temp!=NULL)
	{
		if(temp->key<small && is_mst(start,temp->vertex)=='f')
		{
			small=(temp->key);
			s_vertex=(temp->vertex);
		}
		temp=temp->next;
	}
	return s_vertex;
}
void printmst(mst *start)//prints the vertices in the mstSet
{
	mst *temp=start;
	printf("\nThe mstSet is:");
	while(temp!=NULL)
	{
		printf("%c ",temp->v);
		if(temp->nxt!=NULL)
			printf("-> ");
		temp=temp->nxt;
	}
}
void print_edges(edges *es)//prints the edges that form the minimum spanning tree and prints the minimum cost of the spanning tree
{
	int sum=0;
	edges *e=es;//es is the starting pointer of the list, e is used to traverse through the list
	printf("\nThe edges are:\nEdges \tWeight\n");
	while(e!=NULL)
	{
		printf("%c - %c\t %d\n",e->src,e->dest,e->weight);
		sum+=(e->weight);
		e=e->next;
	}
	printf("\nThe minimum cost of spanning tree is=%d",sum);
}
int is_updtd(source *start,keytype v)//finds and returns the source vertex of the vertex 'v'
{
	char src;
	source *temp=start;	
	while(temp!=NULL)
	{
		if(v==(temp->vertex))
		{
			src=(temp->src);
		}
		temp=(temp->next);
	}
	return src;
}		
void prims(Graph *graph)//finds the mst using prims algorithm
{
	int v=graph->numVertices,i,cnt;
	keylist *first,*prev=NULL,*kt;//kt is a pointer to the new node created in this list and to traverse this list
	mst *prv=NULL,*start=NULL,*mt;//mt is a pointer to the new node created in this list
	node *tmp;
	edges *ep=NULL,*es=NULL;//ep is pointer which points to prevoius node in this list,es is the starting pointer of this list
	source *sp=NULL,*s=NULL,*st;//sp-pointer to previous, s-starting pointer, st-to traverse the list 
	char ch=97,s_vertex;//s_vertex-smallest vertex
	for(i=0;i<v;i++)//this loop creates a list to store key values for every vertex and initializes all key values to INT_MAX
	{
		keylist *kt=(keylist*)malloc(sizeof(keylist));
		kt->vertex=ch++;
		kt->key=INT_MAX;
		kt->next=NULL;
		
		if(prev!=NULL)
			prev->next=kt;
		else
			first=kt;
		prev=kt;
	}
	first->key=0;//initially the key of source vertex is set to 0
	char c;
	int found=0;//to check if vertex is found in the 'source' list
	adjlist *temp;
	for(cnt=0;cnt<v;cnt++)
	{
		mst *mt=(mst*)malloc(sizeof(mst));
		mt->nxt=NULL;
		if(prv!=NULL)
			prv->nxt=mt;
		else
			start=mt;
		prv=mt;
		s_vertex=find_small(first,start);//finds the vertex with smallest key which is not included in mst
		mt->v=s_vertex;//adds the vertex to the mstSet
		
		temp=graph->head;
		while(temp!=NULL)//iterates through adjlist
		{
			if(temp->vertex==s_vertex)
			{
				kt=first;//kt is of type keylist used to traverse the list
				tmp=temp->right;//tmp-of type 'node' [vertices adjacent to each vertex in adjlist]
				while(kt!=NULL)
				{
					
					if(tmp->vertex==kt->vertex)//to check if vertex in keylist is equal to the vertex adjacent to the last vertex in the mstSet
					{
						if(tmp->weight<kt->key && is_mst(start,kt->vertex)=='f')//to check if adjacent vertex has weight less than the key value and that this adjacent vertex is not included in mstSet
						{
							kt->key=tmp->weight;//the key value of the vertex is updated
							
							st=s;//s-start pointer of type 'source' to store the source vertex of a vertex when its key value is updated,st-traverses the list 
							if(st==NULL) 
							{
								source *new=(source*)malloc(sizeof(source));
								new->next=NULL;
								new->vertex=(kt->vertex);
								new->src=(temp->vertex);
								s=new;
								sp=new;
							}
							else
							{
								
								while(st!=NULL)//to check if vertex is already present in the list 
								{
									if((kt->vertex)==(st->vertex))//if present then only update the source
									{
										st->src=(temp->vertex);
										found=1;
										break;
									}
									st=(st->next);
								}
								if(found==0)//if not present in the list then creates a new node in the list
								{
									source *new=(source*)malloc(sizeof(source));
									new->next=NULL;
									new->vertex=(kt->vertex);
									new->src=(temp->vertex);
									sp->next=new;
									sp=new;
								}
								found=0;//found is reset to 0
							}
							
						}
						kt=kt->next;
						tmp=temp->right;
					}
					else
						if(tmp->next!=NULL)//moves to the next adjacent vertex if present
							tmp=tmp->next;
						else//if no more adjacent vertices then moves to next vertex in keylist and reinitializes 'tmp'
						{
							kt=kt->next;
							tmp=temp->right;
						}
						
				}
				
				if(cnt<v-1)//to add edge in the mst 
				{
					edges *e=(edges*)malloc(sizeof(edges));
					e->src=is_updtd(s,find_small(first,start));//adds source vertex from 'source' list
					e->dest=find_small(first,start);//adds the vertex with smallest key value and nt in mst, as dest vertex 
					e->next=NULL;
					if(ep!=NULL)
						ep->next=e;
					else
						es=e;
					ep=e;
					temp=graph->head;
					while(temp!=NULL)//iterates through adjlist and adds the weight to the edge that is being stored in mst
					{
						if(temp->vertex==(e->src))
						{
							tmp=temp->right;
							while(tmp!=NULL)
							{
								if(tmp->vertex==(e->dest))
								{
									e->weight=tmp->weight;
									break;
								}
								tmp=tmp->next;
							}
						}
						temp=temp->next;
					}
				}
				break;
			}
			temp=temp->next;
		}
	}
	printmst(start);
	print_edges(es);
}

void print_ed(edges *es)
{
	//int sum=0;
	edges *e=es;
	printf("\nThe edges are:\nEdges \tWeight\n");
	while(e!=NULL)
	{
		printf("%c - %c\t %d\n",e->src,e->dest,e->weight);
		e=e->next;
	}
	
}


void sort_weights(edges *first)
{
	int swapd;
	edges *ft,*ptr=NULL;
	do
	{
		swapd=0; 
  		ft=first;
		while(ft->next != ptr) 
		{ 
		    if(ft->weight > ft->next->weight) 
		    {  
		        swap(ft, ft->next); 
		        swapd=1; 
		    } 
		    ft=ft->next; 
		} 
       		 ptr= ft; 
   	 } 
   	 while(swapd); 
}

void swap(edges *a, edges *b) 
{ 
	int wt=0,s=0,d=0;
	wt=a->weight;
	a->weight=b->weight; 
   	b->weight=wt;
  	
  	s=a->src;
  	a->src=b->src;
  	b->src=s;
  	
  	d=a->dest;
  	a->dest=b->dest;
  	b->dest=d;
     
} 
	
void kruskal(Graph *graph)
{
	int src,adj,count=0,i=0, v=graph->numVertices,j,k=0;
	char visited[10],pr,p1,p2;
	adjlist *temp=graph->head;
	node *tmp;
	edges *prev=NULL,*first,*start=NULL,*ptr2;
	while(temp!=NULL)
	{
		src=temp->vertex;
		tmp=temp->right;
		while(tmp!=NULL)
		{
			adj=tmp->vertex;
			if(adj>src)
			{
				
				edges *e=(edges*)malloc(sizeof(edges));
				e->src=src;
				e->dest=adj;
				e->weight=tmp->weight;
				e->next=NULL;
				if(prev!=NULL)
					prev->next=e;
				else
					first=e;
				prev=e;
				//count++;
			}	
			tmp=tmp->next;
		}
		temp=temp->next;
	
	}
	print_ed(first);
	sort_weights(first);
	printf("\n After sorting");
	print_ed(first);
	ptr2=first;//first is the starting pointer of sorted array of edges,ptr2 is used to traverse through this array
	prev=NULL;
	while(k<(v-1))
	{		
		if(ptr2==first)//first edge to be inserted
		{				
			edges *ptr=(edges*)malloc(sizeof(edges));
			ptr->next=NULL;
			if(prev!=NULL)
				prev->next=ptr;
			else
				start=ptr;
			prev=ptr;
			ptr->src=first->src;
			ptr->dest=first->dest;
			ptr->weight=first->weight;
			ptr2=first->next;
			visited[i++]=first->src;//add src vertex to visited
			visited[i++]=first->dest;//add dest vertex to visited
			k++;
		}
		else
		{
			
			j=0;
			p1='f',p2='f';//p1=to check if src is visited,p2=to check if dest vertex is visited
			while(j<i)//'i' is the last index of visited array,'j' is used to traverse this array
			{
				if(ptr2->src==visited[j])
					p1='t';
				if(ptr2->dest==visited[j++])
					p2='t';
			}
			
			if(p1=='f'||p2=='f')//only if both p1 and p2 are 't' then this "if block" will not be executed (when both src and dest vertex are visited)
			 
			{			
				edges *ptr=(edges*)malloc(sizeof(edges));
				ptr->next=NULL;
				if(prev!=NULL)
					prev->next=ptr;
				else
					start=ptr;
				prev=ptr;
				ptr->src=ptr2->src;
				ptr->dest=ptr2->dest;
				ptr->weight=ptr2->weight;
				if(p1=='f')//if src is not visited put it in visited array
					visited[i++]=ptr2->src;
				if(p2=='f')//if dest is not visited put it in visited array
					visited[i++]=ptr2->dest;
				k++;
			}		
			ptr2=ptr2->next;
		}
				
	}
	j=0;
	printf("\nThe visited vertices are:\n");//prints the visited array
	while(j<i)
	{
		printf("%c ",visited[j++]);
	}
	print_edges(start);	
	
			
}


