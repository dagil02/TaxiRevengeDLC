#pragma once
#include "Container.h"
#include "Shop.h"

class ShopManager :	public Container {
	//hide copyBuilder and 	assignment operator
	ShopManager(ShopManager&) = delete;
	ShopManager & operator=(const ShopManager &) = delete;

	static unique_ptr<ShopManager> instance_; //ptr instance class

public:
	virtual ~ShopManager();
	void addShop(Shop *shop);

	//init singleton class
	inline static void initInstance() {
		if (instance_.get() == nullptr) {
			instance_.reset(new ShopManager());
		}
	}
	//get singleton class
	inline static ShopManager* getInstance() {
		//SDL_assert(instance_.get() != nullptr); //lanza una mensaje con la primera llamada a getInstance, porque devuelve null
		return instance_.get();
	}

	inline static void destroyInstance() {
		instance_.reset();
		instance_.release();
	}

private:
	ShopManager();

	vector<Shop*> shops_;
};

