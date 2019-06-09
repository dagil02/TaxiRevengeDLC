#pragma once
#include "NodeMap.h"
#include <map>
#include <fstream>

using namespace std;

class NodeMapsManager
{
	NodeMapsManager(NodeMapsManager &) = delete;
	NodeMapsManager & operator=(const NodeMapsManager &) = delete;

	static unique_ptr<NodeMapsManager> instance_; //ptr instance class
public:
	NodeMapsManager();
	virtual ~NodeMapsManager();

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new NodeMapsManager());
		}
	}
	//get singleton class
	inline static NodeMapsManager* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		return instance_.get();
	}

	inline static void destroyInstance() {
		instance_.reset();
		instance_.release();
	}

	void addNodeMap(string key, NodeMap* nodemap=new NodeMap());
	bool NodeMapExists(string key);
	void ReadNodeMapsInfo();
	NodeMap* getNodeMap(string key);

private:
	map<string, NodeMap*> nodemaps_;
	fstream nodemapsFile_;
};

