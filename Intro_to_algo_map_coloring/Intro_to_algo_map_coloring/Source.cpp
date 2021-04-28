#include <iostream>
using namespace std;

#define Node_type int

class Vertex
{
public:
	Vertex(int d = 0, Adjnode* f = NULL) : degree(d), first(f) {};
	~Vertex();

private:
	int degree;
	Adjnode* first;
};

Vertex::~Vertex()
{
}

class Adjnode
{
public:
	Adjnode(Node_type nn = 0, Adjnode* n = NULL): node_num(nn), next(n){};
	~Adjnode();

private:
	Node_type node_num;
	Adjnode* next;
};

Adjnode::~Adjnode()
{
}

class Graph
{
public:
	Graph(int vn = 0);
	void Create_graph();
	~Graph();

private:
	Vertex* vertexs;
	int vertex_num;
};

void Graph::Create_graph()
{

}

Graph::Graph(int vn)
{
	vertexs = new Vertex[vn];
	vertex_num = vn;
}

Graph::~Graph()
{
	delete[] vertexs;
	vertex_num = 0;
}

int main()
{
	
	return 0;
}