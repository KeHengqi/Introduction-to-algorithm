#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
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
	void Create_graph(ifstream& OpenFile);
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

void Graph::Create_graph(ifstream& OpenFile)
{
	char type;
	Node_type source, dest;
	while (!OpenFile.eof())
	{
		OpenFile >> type;
		int i;
		if (type == 'e')
		{
			OpenFile >> source >> dest;
			Add_edge(source, dest);
		}
	}

}

/* Need to be updated */
Graph::~Graph()
{
	delete[] vertexs;
	vertex_num = 0;
}

/* Read the file */
void File_input(ifstream& OpenFile, int& num_of_vertice, int& num_of_edge, int& num_of_color)
{
		//ifstream OpenFile(file_path);
		char message_type;
		char useless_message[300];
		char color_message[300];
		strcpy(color_message, "number of classes");
		char* temp_color_message;
		while (!OpenFile.eof())
		{
			OpenFile.get(message_type);
			if (message_type == 'c')
			{
				/* get the useless message */
				OpenFile.getline(useless_message, 300);
				/* If the string has message of coloring, then get the number of color */
				if (strstr(useless_message, color_message))
				{
					temp_color_message = strrchr(useless_message, ' ');
					strcpy(color_message, temp_color_message);

				}
			}
			else if (message_type == 'p')
			{
				string useless;
				int num_of_vertice;
				int num_of_edge;
				OpenFile >> useless >> num_of_vertice >> num_of_edge;
				cout << num_of_vertice << ' ' << num_of_edge << endl;
				return;
			}
		}
}

Graph* graph;

int main()
{
	char input_type;
	cin >> input_type;
	if (input_type == 'f' || input_type == 'F')
	{
		string file_name;
		cin >> file_name;
		string path = "./" + file_name;
		/* Read the graph from the file */
		ifstream OpenFile(path);
		int num_of_vertice, num_of_edge, num_of_color;
		File_input(OpenFile, num_of_vertice, num_of_edge, num_of_color);
		graph = new Graph(num_of_vertice);
		graph->Create_graph(OpenFile);


		delete graph;
		OpenFile.close();
	}
	
	return 0;
}