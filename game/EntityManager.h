#pragma once
#include<memory>
#include<string>
#include<vector>
#include<map>
#include"Entity.h"
typedef std::vector<std::shared_ptr<Entity>>EntityVec;
typedef std::map<std::string, EntityVec>m_entityMap; //added
class EntityManager {
	EntityVec m_entities;
	EntityVec m_toAdd;//to avoid iterator invalidation
	std::map<std::string, EntityVec>m_entityMap;
	size_t m_totalEntities = 0;
public:
	EntityManager();
	void update();//add m_toAdd
	std::shared_ptr<Entity>addEntity(const std::string &tag);
	EntityVec & getEntities();
	EntityVec & getEntities(const std::string & tag);
	void  removeDeadEntities(EntityVec& vec);
};
