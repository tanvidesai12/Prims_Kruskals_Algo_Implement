typedef char keytype;
struct key_list
{
	keytype vertex;
	int key;
	struct key_list *next;
};
typedef struct key_list keylist;//structure to keep a list of key values corresponding to each vertex 
struct mstSet
{
	keytype v;
	struct mstSet *nxt;
};
typedef struct mstSet mst;//list to store the vertices in the mst
struct nd
{
    keytype vertex;
	int weight;
    struct nd* next;
};
typedef struct nd node;//list that stores the vertices adjacent to every vertex in adjlist

struct list
{
	keytype vertex;
	node *right;
	struct list *next;
};
typedef struct list adjlist;//list to store all vertices in the graph

struct graph
{
    keytype numVertices;
    adjlist *head;//pointer to the first node of adjlist
};
typedef struct graph Graph; //structure that stores the total number of vertices and the starting pointer of adjlist
struct mst_edges
{
	keytype src,dest;
	int weight;
	struct mst_edges *next;
};
typedef struct mst_edges edges;//stores the edges that form the mst
struct Source
{
	keytype vertex,src;
	struct Source *next;
};
typedef struct Source source;//in prims algorithm,when the key values are updated, this list is used to store the source vertex of the vertex whose key value is updated
node* createNode(keytype v,int weight);
char is_mst(mst *f,char ch);
char find_small(keylist *f,mst *start);
void print_edges(edges *es);
Graph* createGraph(int vertices);
void addEdge(Graph* graph);
void display(Graph* graph);
void prims(Graph *graph);
void kruskal(Graph *graph);
void swap(edges *a, edges *b);
void sort_weights(edges *first);
void print_ed(edges *es);
