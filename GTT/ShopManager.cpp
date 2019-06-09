#include "ShopManager.h"

unique_ptr<ShopManager> ShopManager::instance_ = nullptr;

void ShopManager::addShop(Shop * shop) {
	shops_.push_back(shop);
}

ShopManager::ShopManager() {
}


ShopManager::~ShopManager() {
	while (!shops_.empty()) {
		delete shops_.back();
		shops_.pop_back();
	}
}
