#include <iostream>
using namespace std;

#define Node_type int

class Vertex
{
public:
	Vertex(Node_type v = (Node_type) 0, int d = 0, Adjnode* f = NULL, int lcn = 0) :vertex(v),  degree(d), first(f), Left_color_num(lcn) {};
	~Vertex();
	friend class Graph;
private:
	/* Store the vertex message */
	Node_type vertex;
	/* Store the degree of the message */
	int degree;
	/* Store the adjacent vertex in list form */
	Adjnode* first;
	/* Store the number of the color node can use */
	int Left_color_num;
};

/* TODO: update the function */
Vertex::~Vertex()
{
}

class Adjnode
{
public:
	Adjnode(Node_type nn = 0, Adjnode* n = NULL): node_num(nn), next(n){};
	~Adjnode();
	friend class Graph;
private:
	/* Store the vertex message */
	Node_type node_num;
	/* Store the adjacent node message in list form */
	Adjnode* next;
};

/* TODO: Need to update */
Adjnode::~Adjnode()
{
}

/* Not ordered graph */
class Graph
{
public:
	Graph(int vn = 0);
	void Create_graph();
	void Add_edge(Node_type source, Node_type dest);
	~Graph();
	friend class Vertex;
	friend class Adjnode;

private:
	Vertex* vertexs;
	int vertex_num;
};

/* TODO: Need to improve the robustness, but now need to finish the experiment */
Graph::Graph(int vn)
{
	vertexs = new Vertex[vn];
	int i;
	/* Time complexity: O(N) */
	for (i = 0; i < vn; i++)
	{
		vertexs[i].vertex = i;
	}
	vertex_num = vn;
}

/* Add edge function */
void Graph::Add_edge(Node_type source, Node_type dest)
{
	if (vertexs[source].first == NULL)
	{
		/* Source node -> Adjacent node */
		/* If there are no record source -> dest, then there doesn't have the record dest -> source */
		/* Atomic operation */
		vertexs[source].first = new Adjnode(dest, NULL);
		vertexs[source].degree++;

		/* As a unorderd graph, we need to add the edge of adjacent node */
		/* Adjacent node -> Source node */
		if (vertexs[dest].first == NULL)
		{
			/* Atomic operation */
			vertexs[dest].first = new Adjnode(source, NULL);
			vertexs[dest].degree++;
		}
		else
		{
			Adjnode* p = vertexs[dest].first;
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = new Adjnode(source, NULL);
			vertexs[dest].degree++;
		}
	}
	else
	{
		/* Source node -> Adjacent node */
		Adjnode* p = vertexs[source].first;
		while (p->next != NULL)
		{
			/* No need to add */
			/* if source -> dest has record, then there must has a record dest -> source, so we can break here */
			if (p->node_num == dest)
			{
				cout << "Redundant edge" << endl;
				return;
			}
			p = p->next;
		}
		p->next = new Adjnode(dest, NULL);
		/* If success, then up the degree */
		vertexs[source].degree++;

		/* Adjacent node -> Source node */
		if (vertexs[dest].first == NULL)
		{
			vertexs[dest].first = new Adjnode(source, NULL);
			vertexs[dest].degree++;
		}
		else
		{
			Adjnode* p = vertexs[dest].first;
			while (p->next != NULL)
			{
				p = p->next;
			}
			p->next = new Adjnode(source, NULL);
			vertexs[dest].degree++;
		}
	}
}

void Graph::Create_graph()
{
	char type;
	Node_type source, dest;
	cin >> type;
	int i;
	if (type == 'e')
	{
		cin >> source >> dest;
		Add_edge(source, dest);
	}

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