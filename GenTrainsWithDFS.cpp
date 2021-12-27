// Coded by: Stukalov Sergey (Willem White).
#include <iostream>
#include <fstream>
#include <ctime>
#include <list>
#include <vector>

using namespace std;

class Graph {
private:
    // Number of vertices
    int V;
    // Pointer to adjacency list
    list<int>* adj;
    // DFS recursive helper functions
    bool DFS_findCycle(int s, int* visited, vector<int>* cycle);
    // Detect cycle
    int flag = 0;

public:
    //Default constructor
    Graph();
    // Constructor prototype
    Graph(int v);
    // Destructor prototype
    ~Graph();

    // Method to add an edge
    void addEdge(int v, int w);

    // Adjancacy matrix to list in the graph
    void matrixToList(int** adjMatrix, int vertexSize);

    // Method for BFS traversal give a source "s"
    bool findCycle(int* cycle);
};

Graph::Graph() {
    this->V = 0;
    this->flag = 0;
    this->adj = nullptr;
}

// Constructer with number of vertices
Graph::Graph(int v) {
    // Set number of vertices
    this->V = v;
    this->flag = 0;
    // Create new adjacency list
    v ? adj = new list<int>[v] : this->adj = nullptr;
}

// Constructer with number of vertices
Graph::~Graph() {
    // Deleting adjacency list
    adj->~list();
}

// Implementation of method to add edges
void Graph::addEdge(int v, int w) {
    this->adj[v].push_back(w);
}

void Graph::matrixToList(int** adjMatrix, int vertexSize) {
    if (!adjMatrix)
        return;
    if (!vertexSize)
        return;
    if (!adj) adj = new list<int>[vertexSize];

    for (int i = 0; i < vertexSize; i++) {
        for (int j = 0; j < vertexSize; j++) {
            if (adjMatrix[i][j]) this->addEdge(i, j);
        }
    }
    this->V = vertexSize;
}

bool Graph::DFS_findCycle(int s, int* visited, vector<int>* path) {
    if (this->flag == 1) return true;
    else {
        // Visited but did not leave
        visited[s] = 1;
        path->push_back(s);
        // Go through the adjacency list
        for (auto i = adj[s].begin(); i != adj[s].end(); i++) {
            // If not visited, travel through that vertex
            if (!visited[*i]) {
                DFS_findCycle(*i, visited, path);
            }
            // If visited but did not leave - cycle
            if (visited[*i] == 1 && *i != s && !this->flag) {
                path->push_back(*i);
                this->flag = 1; return true;
            }
            if (this->flag) return true;
        }
        visited[s] = 2;
        path->pop_back();
        return false;
    }
}

// Perform DFS given a starting vertex 0
bool Graph::findCycle(int* cycle) {
    // Start with all vertices as not visited
    int* visited = new int[V];
    vector<int> path;

    for (int i = 0; i < V; i++) {
        visited[i] = 0; cycle[i] = 0;
    }

    for (int j = 0; j < this->V; j++) {

        if (!visited[j]) {

            if (DFS_findCycle(j, visited, &path)) {

                int i = path.size() - 2;
                cycle[path.at(path.size() - 1)] = 1;

                while (path.at(i) != path.at(path.size() - 1)) {
                    cycle[path.at(i)] = 1;
                    i--;
                }
                delete[] visited;
                return true;
            }
        }
    }

    delete[] visited;
    return false;
}

int main() {
    /* TEST_CODE
    int size = 5;
    Graph g(size);

    int* mat1 = new int[5]{ 0,1,0,0,0 };
    int* mat2 = new int[5]{ 0,0,1,0,0 };
    int* mat3 = new int[5]{ 0,0,0,1,0 };
    int* mat4 = new int[5]{ 1,0,0,0,0 };
    int* mat5 = new int[5]{ 0,0,0,0,0 };
    int** matrix = new int* [5]{ mat1,mat2,mat3,mat4,mat5 };

    // Reading matrix
    g.matrixToList(matrix, size);
    int* cycle = new int[size];
    bool isCycle = g.findCycle(cycle);


    for (int i = 0; i < size; i++)
        cout << cycle[i] << " ";
    */
    srand(time(NULL));

    fstream fs;
    fs.open("train10.csv", fstream::out | fstream::in | fstream::app);

    if (!fs.is_open()) {
        cerr << "ERROR: File is not open..." << endl;
    }
    fs << "aa,ab,ac,ad,ae,af,ag,ah,ai,aj,"
        << "ba,bb,bc,bd,be,bf,bg,bh,bi,bj,"
        << "ca,cb,cc,cd,ce,cf,cg,ch,ci,cj,"
        << "da,db,dc,dd,de,df,dg,dh,di,dj,"
        << "ea,eb,ec,ed,ee,ef,eg,eh,ei,ej,"
        << "fa,fb,fc,fd,fe,ff,fg,fh,fi,fj,"
        << "ga,gb,gc,gd,ge,gf,gg,gh,gi,gj,"
        << "ha,hb,hc,hd,he,hf,hg,hh,hi,hj,"
        << "ia,ib,ic,id,ie,if,ig,ih,ii,ij,"
        << "ja,jb,jc,jd,je,jf,jg,jh,ji,jj,"
        << "isCycle:" << endl;

    /* CODE_FOR_GENERATING_TRAIN5
    fs << "aa,ab,ac,ad,ae,"
        << "ba,bb,bc,bd,be,"
        << "ca,cb,cc,cd,ce,"
        << "da,db,dc,dd,de,"
        << "ea,eb,ec,ed,ee,"
        << "isCycle:" << endl;
    */
    for (int k = 0; k < 1000000; k++) {

        // Graph init
        int size = 10;
        Graph g(size);
        int** matrix = new int* [size];
        for (int i = 0; i < size; i++) {
            matrix[i] = new int[size];
            for (int j = 0; j < size; j++)
                matrix[i][j] = 0;
        }

        if (k % 7 == 0) {
            // Random adj matrix 
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++)
                    matrix[i][j] = rand() % 2;
            }
        }
        else {
            for (int i = 0; i < size; i++) {
                int j = rand() % size, m = rand() % size;
                matrix[j][m] = 1;
            }
        }

        // Reading matrix
        g.matrixToList(matrix, size);
        int* cycle = new int[size];
        // Find cycle:
        bool isCycle = g.findCycle(cycle);

        // Output matrix
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                fs << matrix[i][j] << ",";

        // Output boolean (isCycle?):
        fs << isCycle << endl;

        // Free memory:
        for (int i = 0; i < size; i++)
            delete[] matrix[i];
        delete[] matrix;
    }
    return 0;
}