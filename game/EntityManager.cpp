#include"EntityManager.h"
#include<memory>
#include "Entity.h"
#include<algorithm>
#include <iostream>
#include<vector>
#include<map>



EntityManager::EntityManager() {
}
void EntityManager::update() {

	   		removeDeadEntities(m_entities);
			      	
	}




void EntityManager:: removeDeadEntities(EntityVec & vec) {
	     
	auto ek = vec.begin();

	while (ek != vec.end()) {
		
		if (!(*ek)->isActive()) {
			std::cout <<"Total Entity Before:" <<vec.size() << std::endl;
			ek=vec.erase(ek);
			std::cout << "Total Entity After:" << vec.size() << std::endl;
		}
		else {
			++ek;
		}
		

	}
		  	 
			for (auto &kv : m_entityMap)
			{
	
		
				/*if (kv.second.empty())
					m_entityMap.erase(kv.first);*/
			
				auto ek = kv.second.begin();
				while (ek != kv.second.end()) {
					if (!(*ek)->isActive()) {
						ek = kv.second.erase(ek);
						std::cout << "Map:" <<kv.first << std::endl;
					}
					else {
						++ek;
					}
				}
			}

	}



std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {
	auto e = std::make_shared<Entity>(tag,m_totalEntities++);
	
	m_entities.push_back(e);
	m_entityMap[tag].push_back(e);
	return e;
}




EntityVec & EntityManager:: getEntities() {

	return m_entities;

};



EntityVec & EntityManager::getEntities(const std::string & tag) {
	
	
	return m_entityMap[tag];

}
