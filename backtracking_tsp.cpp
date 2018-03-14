#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int** weight_matrix = NULL;
int min_cost = 1000000000;
std::vector<int> optimal_path;

// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};

// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};

// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

void create_matrix(int n)
{
    weight_matrix = new int*[n];
    for(int i = 0; i < n; ++i)
    weight_matrix[i] = new int[n];
}

void AllHamiltonianPaths(Graph* graph, int v,bool visited [],vector<int> path,int n)
{
	// if all the vertices are visited, then
	// hamiltonian path exists
	if (path.size() == n)
	{
		// print hamiltonian path
		int temp_cost = 0;
		for (std::vector<int>::iterator it = path.begin() ; it != path.end(); it++){
            std::vector<int>::iterator gt=it;
            gt++;
            if(gt!=path.end())
			    temp_cost = temp_cost + weight_matrix[*it][*(gt)];
            else
                temp_cost = temp_cost + weight_matrix[*it][0];
		}
		if(temp_cost<min_cost)
        {
          /*for(std::vector<int>::iterator t = path.begin() ; t != path.end(); ++t){
               optimal_path.push_back(*t);
            }*/
            optimal_path=path;
            min_cost=temp_cost;
		}
        else if(temp_cost==min_cost)
        {
            for(std::vector<int>::iterator t = path.begin() ; t != path.end(); ++t)
            {
               optimal_path.push_back(*t);
            }
        }
		return;
	}

	// Check if every edge starting from vertex v leads
	// to a solution or not
	struct AdjListNode* pCrawl = graph->array[v].head;
	while(pCrawl)
    {
        // process only unvisited vertices as hamiltonian
        // path visits each vertex exactly once

            int val = pCrawl->dest;
            //cout<<val<<" ";
        if(!visited[val])
        {
            visited[val] = true;
            path.push_back(val);
            AllHamiltonianPaths(graph, val, visited, path,n);
            visited[val] = false;
			path.pop_back();
        }
        pCrawl= pCrawl->next;
	}
}

// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    int n,module;
    cout<<"enter no of vertex n: ";
    cin>>n;
    srand(0);
    cout<<"enter maximum weight(weights will be randomly generated): ";
    cin>>module;
    create_matrix(n);
    struct Graph* graph = createGraph(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(j!=i){
                weight_matrix[i][j] = (rand() % (module+1));
                addEdge(graph,i,j);
            }else{
                weight_matrix[i][j] = 0;
            }
        }
    }

    // print the adjacency list representation of the above graph

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<weight_matrix[i][j]<<" ";
        }
        cout<<endl;
    }

    int start = 0;

	// add starting node to the path
	vector<int> path;
	path.push_back(start);

	// mark start node as visited
	bool visited[n];
 	visited[start] = true;

	AllHamiltonianPaths(graph,start, visited, path,n);
    cout<<min_cost<<endl;
    int i=0;
    for (std::vector<int>::iterator it = optimal_path.begin() ; it != optimal_path.end(); it++)
    {
        ++i;
            cout << *it << " ";
        if(i%n==0)
            cout<<"0\n";
    }
    cout<<"\n";
    return 0;
}