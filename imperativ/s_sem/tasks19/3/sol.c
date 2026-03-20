#include <stdlib.h>
#include <string.h>
#include "sol.h"

static int g_verCount = 0;
static int* g_edgeCounts = NULL;
static int* g_offsets = NULL;   
static Edge* g_allEdges = NULL; 

void init() {
    g_verCount = getVerticesCount();

    Edge* tempInput = (Edge*)malloc(300005 * sizeof(Edge));
    g_edgeCounts = (int*)calloc(g_verCount, sizeof(int));
    
    int edgeIdx = 0;
    Edge current;
    int totalIncidentEntries = 0;


    while (readEdge(&current)) {
        tempInput[edgeIdx++] = current;
        g_edgeCounts[current.from]++;
        g_edgeCounts[current.to]++;
        totalIncidentEntries += 2;
    }

    g_offsets = (int*)malloc((g_verCount + 1) * sizeof(int));
    g_allEdges = (Edge*)malloc(totalIncidentEntries * sizeof(Edge));
    
    int currentOffset = 0;
    for (int i = 0; i < g_verCount; i++) {
        g_offsets[i] = currentOffset;
        currentOffset += g_edgeCounts[i];
    }
    g_offsets[g_verCount] = currentOffset;

    int* currentPos = (int*)malloc(g_verCount * sizeof(int));
    memcpy(currentPos, g_offsets, g_verCount * sizeof(int));


    for (int i = 0; i < edgeIdx; i++) {
        Edge e = tempInput[i];
    
        int posF = currentPos[e.from]++;
        g_allEdges[posF].from = e.from;
        g_allEdges[posF].to = e.to;
        g_allEdges[posF].weight = e.weight;
        
        int posT = currentPos[e.to]++;
        g_allEdges[posT].from = e.to;
        g_allEdges[posT].to = e.from;
        g_allEdges[posT].weight = e.weight;
    }

    free(tempInput);
    free(currentPos);
}

int getEdgesCount(int iVertex) {
    if (iVertex < 0 || iVertex >= g_verCount) return 0;
    return g_edgeCounts[iVertex];
}

Edge getIncidentEdge(int iVertex, int iIndex) {
    int startIdx = g_offsets[iVertex];
    return g_allEdges[startIdx + iIndex];
}