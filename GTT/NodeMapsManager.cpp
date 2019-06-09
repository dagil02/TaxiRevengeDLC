#include "NodeMapsManager.h"
#include <string>
#include <iostream>
#include <sstream>

unique_ptr<NodeMapsManager> NodeMapsManager::instance_ = nullptr;


void NodeMapsManager::addNodeMap(string key, NodeMap * nodemap)
{
	nodemaps_[key] = nodemap;
}

bool NodeMapsManager::NodeMapExists(string key)
{
	for (auto o : nodemaps_) {
		if (o.first == key) return true;
	}
	return false;
}

void NodeMapsManager::ReadNodeMapsInfo()
{
	nodemapsFile_.open("../TextFiles/Nodes.txt");
	if (nodemapsFile_.is_open()) {
		string line;
		string district;
		while (getline(nodemapsFile_, line)) {
			istringstream row(line);
			switch (line[0]) {
				case'D': {
					row >> district;
					break;
				}
				case 'N': {
					string bNode;
					string connection;
					row >> bNode;
					if (bNode == "Node50") {
						cout << "A";
					}
					while (row >> connection) {
						nodemaps_[district]->connectNodes(bNode, connection);
					}
					break;
				}
				case 'P': {
					string patrolId;
					row >> patrolId;
					string node;
					vector<Node*>patrol;

					while (row>>node) {
						patrol.push_back(nodemaps_[district]->getNodes()[node]);
					}
					nodemaps_[district]->addPatrol(patrol, patrolId);
					break;
				}
				default:
					break;
			}
			
		}
		nodemapsFile_.close();
	}
}

NodeMap * NodeMapsManager::getNodeMap(string key) {
	return nodemaps_[key];
}


NodeMapsManager::NodeMapsManager() {
}


NodeMapsManager::~NodeMapsManager() {
	for (std::map<string, NodeMap*>::iterator it = nodemaps_.begin(); it != nodemaps_.end(); it++) {
		delete it->second;
		it->second = nullptr;
	}
	nodemaps_.clear();
}
