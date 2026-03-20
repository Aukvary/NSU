#ifndef EDGELISTS_SOL_579846984654
#define EDGELISTS_SOL_579846984654
typedef struct {
int from, to;
int weight;
} Edge;
//==============================================
//call these functions to get the graph data:
//returns N --- the number of vertices in the graph
int getVerticesCount();
//reads the next edge from the edge list
//if there is next edge, returns 1 and stores that edge to *oEdge
//if there is no next edge, returns 0 without touching pointer
int readEdge(Edge *oEdge);
//==============================================
//implement these functions in your solution:
//this function is called first to initialize graph
//you are expected to read graph here and fill internal data structures
void init();
//returns number of edges indicent to vertex iVertex
int getEdgesCount(int iVertex);
//returns iIndex-th edge incident to the vertex iVertex
//it must have .from == Vertex and .to denoting the other end
Edge getIncidentEdge(int iVertex, int iIndex);
#endif