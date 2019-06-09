#include "EnemyManager.h"
#include "NodeMapsManager.h"

unique_ptr<EnemyManager> EnemyManager::instance_ = nullptr;

EnemyManager::EnemyManager() {
}


EnemyManager::~EnemyManager() {
	for (std::map<string, Enemy*>::iterator it = enemies_.begin(); it != enemies_.end(); it++) {
		delete it->second;
		it->second = nullptr;
	}
	enemies_.clear();
}

void EnemyManager::ReadEnemyInfo()
{
	enemyInfoFile_.open("../TextFiles/Enemies.txt");
	if (enemyInfoFile_.is_open()) {
		string line;
		string district;
		while (getline(enemyInfoFile_, line)) {
			istringstream row(line);
			switch (line[0]) {
			case'D': {
				row >> district;
				break;
			}
			case 'E': {
				string enemyid;
				string patrolid;
				string spawnid;
				string type;
				row >> enemyid >> patrolid >> spawnid >> type;
				Enemy* e;
				if (type == "Type1") {
					e = new Enemy(ENEMY1, NodeMapsManager::getInstance()->getNodeMap(district), NodeMapsManager::getInstance()->getNodeMap(district)->getPatrol(patrolid), spawns_[spawnid], ENEMYGUN);
					enemies_[enemyid] = e;
				}
				else if (type == "Type2") {
					e = new Enemy(ENEMY2, NodeMapsManager::getInstance()->getNodeMap(district), NodeMapsManager::getInstance()->getNodeMap(district)->getPatrol(patrolid), spawns_[spawnid],SHOTGUN);
					enemies_[enemyid] = e;
				}
				else if (type == "Type3") {
					e = new Enemy(ENEMY3, NodeMapsManager::getInstance()->getNodeMap(district), NodeMapsManager::getInstance()->getNodeMap(district)->getPatrol(patrolid), spawns_[spawnid], ENEMYGUN);
					enemies_[enemyid] = e;
				}
				else if (type == "Type4") {
					e = new Enemy(ENEMYTANK, NodeMapsManager::getInstance()->getNodeMap(district), NodeMapsManager::getInstance()->getNodeMap(district)->getPatrol(patrolid), spawns_[spawnid], SHOTGUN);
					enemies_[enemyid] = e;
				}
				break;
			}
			default:
				break;
			}
			
		}
		enemyInfoFile_.close();
	}
}

void EnemyManager::addSpawn(string id, Vector2D pos)
{
	spawns_[id] = pos;
}

void EnemyManager::deactivateIA()
{
	for (auto e : enemies_) {
		if(e.second!=nullptr)
			e.second->getIABehaviour()->Restart();
	}
}

bool EnemyManager::EnemyAtPos(Vector2D pos, GameObject* enemy)
{
	for (auto e : enemies_) {
		if (e.second != nullptr && e.second->isActive() && e.second!=enemy)
			if(e.second->getCenter().x<=pos.x+TILE_SIZE && e.second->getCenter().x >=pos.x- TILE_SIZE
				&& e.second->getCenter().y <= pos.y + TILE_SIZE && e.second->getCenter().y >= pos.y - TILE_SIZE)return true;
	}
	return false;
}

int EnemyManager::GetEnemyCount()
{
	return enemies_.size();
}

void EnemyManager::update(Uint32 deltaTime)
{
	for (auto e : enemies_) {
		if (e.second != nullptr) {
			e.second->update(deltaTime);
		}
	}
}

void EnemyManager::render(Uint32 deltaTime)
{
	for (auto e : enemies_) {
		if(e.second!=nullptr)
		e.second->render(deltaTime);
	}
}

