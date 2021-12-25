// A C++ program to print topological
// sorting of a DAG
#include <iostream>
#include <list>
#include <stack>
using namespace std;

class Graph
{
  int V;          //no of vertices
  list<int> *adj; //pointer to an array containing adj listsList

  // A function used by topologicalSort
  void topologicalSortUtil(int v, bool visited[],stack<int>& Stack);

public:
  Graph(int V); //contructor
  void addEdge(int v, int w);
  void topologicalSort();

  void printMatrix();
};

Graph::Graph(int V)
{
  this->V = V;
  adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
  // Add w to v's list
  adj[v].push_back(w);
}

// A recursive function used by topologicalSort
void Graph::topologicalSortUtil(int v, bool visited[],
                                stack<int>& Stack)
{
    // Mark the current node as visited.
    visited[v] = true;
 
    // Recur for all the vertices
    // adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            topologicalSortUtil(*i, visited, Stack);
 
    // Push current vertex to stack
    // which stores result
    Stack.push(v);
}

// The function to do Topological Sort.
// It uses recursive topologicalSortUtil()
void Graph::topologicalSort()
{
  stack<int> Stack;

  // Mark all the vertices as not visited
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++)
    visited[i] = false;

  // Call the recursive helper function
  // to store Topological
  // Sort starting from all
  // vertices one by one
  for (int i = 0; i < V; i++)
    if (visited[i] == false)
      topologicalSortUtil(i, visited, Stack);

  // Print contents of stack
  while (Stack.empty() == false)
  {
    cout << Stack.top() << " ";
    Stack.pop();
  }
}

void Graph::printMatrix()
{
}

int main()
{
  Graph g(6);
  g.addEdge(5, 2);
  g.addEdge(5, 0);
  g.addEdge(4, 0);
  g.addEdge(4, 1);
  g.addEdge(2, 3);
  g.addEdge(3, 1);

  g.topologicalSort();
}