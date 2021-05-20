#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
using namespace std;
#define Node_type int

class Adjnode
{
public:
	Adjnode(Node_type nn = 0, Adjnode* n = NULL) : node_num(nn), next(n) {};
	~Adjnode();
	friend class Graph;
	friend class Vertex;
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

class Vertex
{
public:
	Vertex(Node_type v = (Node_type) 0, int d = 0, Adjnode* f = NULL, int lcn = 0, int vc = -1) :
		vertex(v), degree(d), first(f), Left_color_num(lcn), vertex_color(vc) {
		able_color = NULL;
	};
	~Vertex();
	friend class Graph;
	friend class Adjnode;
private:
	/* Store the vertex message */
	Node_type vertex;
	/* Store the degree of the message */
	int degree;
	/* Store the adjacent vertex in list form */
	Adjnode* first;
	/* Store the number of the color node can use */
	int Left_color_num;
	/* Store the color the node being colored */
	int vertex_color;
	/* Store the color message */
	int* able_color;
};

/* May have problem */
Vertex::~Vertex()
{
	if (able_color != NULL)
	{
		delete[] able_color;
	}
	if (first != NULL)
	{
		Adjnode* p = first;
		while (p->next)
		{
			Adjnode* Delete = p;
			p = p->next;
			delete Delete;
		}
		delete p;
	}
}

/* Not ordered graph */
class Graph
{
public:
	Graph(int vn = 0, int cn = 0);
	void Create_graph(ifstream& OpenFile);
	void Add_edge(Node_type source, Node_type dest);
	void Search_the_adjacent(Node_type source);
	void Initialize_colored_map(int vertex_nu, int color_nu);
	void Delete_colored_map(int vertex_nu);
	int Color_the_vertex(Node_type vertex_num);

	void Coloring_map(int colored_num);
	~Graph();
	friend class Vertex;
	friend class Adjnode;

private:
	/* the vertexs are colored */
	int colored_num;
	/* solution of coloring map */
	int** colored_map;
	/* minimum number of color a vertex can choose in the graph */
	int min_color_num;
	/* Stores the vertexs message */
	Vertex* vertexs;
	/* Stores the number of vertex */
	int vertex_num;
	/* Stores the number of color */
	int color_num;
	/* Stores the list of the nodes that have max degree and minimum choice of color */
	vector<Node_type> max_degree_nodes;
	/* Stores the max degree in the graph so far */
	int max_degree;
	/* Stores the number of solution */
	int solution_num;
};

/* Atomic operation of coloring a vertex */
int Graph::Color_the_vertex(Node_type vertex_num)
{
	Adjnode* p = vertexs[vertex_num].first;
	for (int i = 0; i < this->color_num; i++)
	{
		/* 0 means the color can be used */
		if (vertexs[vertex_num].able_color[i] == 0)
		{
			/* 2 means the color is used as this vertex color*/
			vertexs[vertex_num].able_color[i] = 2;
			vertexs[vertex_num].vertex_color = i;
			while (p)
			{
				/* 1 means the color is used by a adjadence node */
				vertexs[p->node_num].able_color[i] = 1;
				/* if the vertex not be colored and the degree of it is not 0 */
				if (vertexs[p->node_num].degree != 0 && vertexs[p->node_num].vertex_color == -1)
				{
					vertexs[p->node_num].degree--;
				}
				this->colored_num++;
				p = p->next;
			}
		}
	}
	return vertexs[vertex_num].vertex_color;
}

/* Node start from 1 */
void Graph::Initialize_colored_map(int vertex_nu, int color_nu)
{
	int i;
	colored_map = new int* [vertex_nu + 1];
	for (i = 1; i < vertex_nu + 1; i++)
	{
		colored_map[i] = new int [color_nu];
	}
}

/* Node start from 1 */
void Graph::Delete_colored_map(int vertex_nu)
{
	int i;
	for (i = 1; i < vertex_nu + 1; i++)
	{
		delete[] colored_map[i];
	}
	delete[] colored_map;
}

/* In order to find out the adjacent node */
void Graph::Search_the_adjacent(Node_type source)
{
	Adjnode* p = vertexs[source].first;
	if (p != NULL)
	{
		cout << "Source node " << source << " 's adjacent nodes are:";
		while (p->next != NULL)
		{
			cout << ' ' << p->node_num;
			p = p->next;
		}
		cout << ' ' << p->node_num << endl;
	}
	else
	{
		cout << "Source node " << source << " is isolated" << endl;
	}
}

/* TODO: Need to improve the robustness, but now need to finish the experiment */
Graph::Graph(int vn, int cn)
{
	vertexs = new Vertex[vn + 1];
	colored_map = new int*[vn + 1];
	int i;
	/* Time complexity: O(N) */
	for (i = 1; i < vn + 1; i++)
	{
		vertexs[i].vertex = i;
		vertexs[i].Left_color_num = cn;
		vertexs[i].able_color = new int[cn];
	}
	vertex_num = vn;
	color_num = cn;
	Initialize_colored_map(vertex_num, colored_num);
	solution_num = 0;
	max_degree = 0;
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

			/* get the max degree nodes and max degree number */
			if (vertexs[source].degree > max_degree)
			{
				/* As there has a larger degree num, so the origin max nodes are not the first choice, and we need to empty it */
				vector<Node_type>().swap(max_degree_nodes);
				max_degree_nodes.push_back(source);
				max_degree = vertexs[source].degree;
				//max_degree_node = source;
			}
			else if (vertexs[source].degree == max_degree)
			{
				max_degree_nodes.push_back(source);
			}

			if (vertexs[dest].degree > max_degree)
			{
				/* Same as the source part */
				vector<Node_type>().swap(max_degree_nodes);
				max_degree_nodes.push_back(dest);
				max_degree = vertexs[dest].degree;
				//max_degree_node = dest;
			}
			else if (vertexs[dest].degree == max_degree)
			{
				max_degree_nodes.push_back(dest);
			}

		}
	}
}

/* i start from 1 */
void Graph::Coloring_map(int colored_num)
{
	if (colored_num == 0)
	{
		Color_the_vertex(this->max_degree_nodes.front());
		Coloring_map(++colored_num);
	}
	else if (colored_num == this->vertex_num)
	{
		solution_num++;
	}
	else
	{ 
		int min_color = this->min_color_num;
		int max_degree_num = this->max_degree;
		for (int i = 1; i < vertex_num + 1; i++)
		{
			if (vertexs[i].Left_color_num == min_color)
			{
				if ()
			}
		}
	}
}

/* Need to be updated */
Graph::~Graph()
{
	delete[] vertexs;
	Delete_colored_map(vertex_num);
	vertex_num = 0;
}

/* Read the file */
void File_input(ifstream& OpenFile, int& num_of_vertice, int& num_of_edge, int& num_of_color)
{
		//ifstream OpenFile(file_path);
		char message_type;
		char useless_message[300];
		char color_message[300];
		strcpy_s(color_message, "number of classes");
		char* temp_color_message;
		/* In order to take only one color message */
		int color_flag = 0;
		while (!OpenFile.eof())
		{
			OpenFile.get(message_type);
			if (message_type == 'c')
			{
				/* get the useless message */
				OpenFile.getline(useless_message, 300);
				/* If the string has message of coloring, then get the number of color */
				if (strstr(useless_message, color_message) && color_flag == 0)
				{
					temp_color_message = strrchr(useless_message, ' ');
					strcpy_s(color_message, temp_color_message);
					/* May have problem */
					temp_color_message = strtok(color_message, " ");
					int color_num = atoi(temp_color_message);
					num_of_color = color_num;
					/* Only take one time */
					color_flag = 1;
				}
			}
			else if (message_type == 'p')
			{
				string useless;
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
		graph = new Graph(num_of_vertice, num_of_color);
		graph->Create_graph(OpenFile);


		delete graph;
		OpenFile.close();
	}
	
	return 0;
}