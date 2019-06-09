#pragma once
#include "Vector2D.h"
#include <vector>
#include <map>

enum Connections {
	NORTH,
	SOUTH,
	EAST,
	WEST
};
class Node {
public:
	Node(Vector2D pos, string id) {
		position_ = pos;
		id_ = id;
		for (int i = 0; i < 4; i++) {
			connections_[i] = nullptr;
		}
	}
	Vector2D position_;
	Node* connections_[4];
	string id_;
	bool isDeadEnd() {
		int count = 0;
		for (int i = 0; i < 4; i++) {
			if (connections_[i] != nullptr) {
				count++;
				if (count > 1) return false;
			}
		}
		return true;
	}
	bool isConnected(Node* n) {
		for (int i = 0; i < 4; i++) {
			if (connections_[i] == n) return true;
		}
		return false;
	}
	bool hasConnection(Vector2D direction, Connections& dir) {
		double x= abs(direction.x);
		double y = abs(direction.y);
		
		Connections dirr=NORTH;
		dir = dirr;
		if (abs(direction.x - direction.y) < 0.4) return false;
		if (x > y) {
			if (direction.x > 0) dirr = EAST;
			else dirr = WEST;
		}
		else {
			if (direction.y > 0) dirr = SOUTH;
			else dirr = NORTH;
		}
		dir = dirr;
		return connections_[dirr] != nullptr;

	}
};
class NodeMap
{
public:
	NodeMap();
	void addNode(Node* n, string id);
	void addPatrol(vector<Node*> patrol, string id);
	void connectNodes(string id1, string id2);
	bool nodeExists(string id);
	bool nodeExists(Node* n);
	Node* getNearestNode(Vector2D position, vector<Node*> unwantednodes= vector<Node*>());
	Node* getNearestConnectedNode(Vector2D position);
	void getBetweenNodes(Node*& a, Node*& b, Vector2D position);
	bool FindRoute(Node* current, Node* destiny, vector<Node*>& route, vector<Node*>&currentroute, int distance, int& minDistance);
	map<string, Node*> getNodes();
	vector<Node*> getPatrol(string id);
	void InBetweenNodes(Vector2D position, Node*& a, Node*& b);
	virtual ~NodeMap();
private:
	map<string, Node*>nodes;//contiene todos los nodos del distrito con un identificador
	map<string, vector<Node*>> patrols;//diccionario de patrullas posibles del distrito
	bool hasNode(vector<Node*>&v, Node* n);
	int getDistance(Node* a, Node* b);
};

