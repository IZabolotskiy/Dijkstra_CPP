#include <iostream>
#include <vector>

#define INT_MAX 10000000

using namespace std;

void DeikstrasAlgTest();

int main() {
	DeikstrasAlgTest();
	return 0;
}

class Node;
class Edge;

void Deikstras();
vector<Node*>* AdjoingRemainingNodes(Node* node);
Node* ExtractSmallest(vector<Node*>& nodes);
int Distance(Node* node1, Node* node2);
bool Contains(vector<Node*>& nodes, Node* node);
void PrintShortestRouteTo(Node* destination);

vector<Node*> nodes;
vector<Edge*> edges;

class Node {
public:
	Node(int id)
		: id(id), previous(NULL), distanceFromStart(INT_MAX) {
		nodes.push_back(this);
	}

public:
	int id;
	Node* previous;
	int distanceFromStart;
};

class Edge {
public:
	Edge(Node* node1, Node* node2, int distance)
		: node1(node1), node2(node2), distance(distance) {
		edges.push_back(this);
	}
	bool Connects(Node* node1, Node* node2) {
		return (node1 == this->node1 &&
				node2 == this->node2);
			
	}

public:
	Node* node1;
	Node* node2;
	int distance;
};

void DeikstrasAlgTest() {
	setlocale(LC_ALL, "rus");
	cout << "сколько вершин вы хотите задать?" << endl;
	int n2;
	cin >> n2;
	Node** nodes = new Node * [n2];
	for (int i = 0; i < n2; i++) {
		nodes[i] = new Node(i + 1);
	}
	cout << "сколько дуг вы хотите задать?" << endl;
	int n;
	cin >> n;
	Edge** e = new Edge * [n];
	cout << "Последовательно введите начало дуги, её конец и вес дуги \nназвание вершины должно быть представлено натуральным числом" << endl;
	for (int i = 0; i < n; i++) {
		int c1, c2;
		int len;
		cin >> c1 >> c2 >> len;

		e[i] = new Edge(nodes[c1 - 1], nodes[c2 - 1], len);
	}
	cout << "Введите первый и последний пункт" << endl;
	int n4, n5;
	cin >> n4 >> n5;
	nodes[n4 - 1]->distanceFromStart = 0;
	Deikstras();
	PrintShortestRouteTo(nodes[n5 - 1]);
}

void Deikstras() {
	while (nodes.size() > 0) {
		Node* smallest = ExtractSmallest(nodes);
		vector<Node*>* adjoingNodes =
			AdjoingRemainingNodes(smallest);

		const int size = adjoingNodes->size();
		for (int i = 0; i < size; ++i) {
			Node* adjoing = adjoingNodes->at(i);
			int distance = Distance(smallest, adjoing) +
				smallest->distanceFromStart;

			if (distance < adjoing->distanceFromStart) {
				adjoing->distanceFromStart = distance;
				adjoing->previous = smallest;
			}
		}
		delete adjoingNodes;
	}
}

Node* ExtractSmallest(vector<Node*>& nodes) {
	int size = nodes.size();
	if (size == 0) return NULL;
	int smallestPosition = 0;
	Node* smallest = nodes.at(0);
	for (int i = 1; i < size; ++i) {
		Node* current = nodes.at(i);
		if (current->distanceFromStart <
			smallest->distanceFromStart) {
			smallest = current;
			smallestPosition = i;
		}
	}
	nodes.erase(nodes.begin() + smallestPosition);
	return smallest;
}

vector<Node*>* AdjoingRemainingNodes(Node* node) {
	vector<Node*>* adjoingNodes = new vector<Node*>();
	const int size = edges.size();
	for (int i = 0; i < size; ++i) {
		Edge* edge = edges.at(i);
		Node* adjoing = NULL;
		if (edge->node1 == node) {
			adjoing = edge->node2;
		}
		if (adjoing && Contains(nodes, adjoing)) {
			adjoingNodes->push_back(adjoing);
		}
	}
	return adjoingNodes;
}

int Distance(Node* node1, Node* node2) {
	const int size = edges.size();
	for (int i = 0; i < size; ++i) {
		Edge* edge = edges.at(i);
		if (edge->Connects(node1, node2)) {
			return edge->distance;
		}
	}
	return -1;
}

bool Contains(vector<Node*>& nodes, Node* node) {
	const int size = nodes.size();
	for (int i = 0; i < size; ++i) {
		if (node == nodes.at(i)) {
			return true;
		}
	}
	return false;
}

void PrintShortestRouteTo(Node* destination) {
	Node* prev = destination;
	setlocale(LC_ALL, "rus");
	if (destination->distanceFromStart == 10000000) {
		cout << "путь не существует" << endl;
	}
	else {
		cout << "Дистанция от начала: "
			<< destination->distanceFromStart << endl;
		while (prev) {
			cout << prev->id;
			if (prev->previous != NULL) {
				cout << " <- ";
			}
			prev = prev->previous;
		}
		cout << endl;
	}
	system("pause");
}
