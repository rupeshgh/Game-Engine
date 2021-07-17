#include"EntityManager.h"
#include "Entity.h"

Entity::Entity(const std::string &t,const size_t  &i  ) :
	m_id(i),m_tag(t) {


}
bool Entity::isActive() const {

	return m_active;
}

const std::string & Entity::tag()const {

	return m_tag;
}

 size_t Entity::id() const  {

	return m_id;
}

 void Entity::destroy() {
	 m_active = false;
 }