#pragma once
#include<iostream>
#include<memory>
#include<string>
#include "Components.h"
class Entity {

	const size_t m_id = 0;
	const std::string m_tag = "default";
	bool m_active = true;
public:
	std::shared_ptr<CTransform>cTransform;
	std::shared_ptr<CScore>cScore;
	std::shared_ptr<CShape>cShape;
	std::shared_ptr<CCollision>cCollision;
	std::shared_ptr<CInput>cInput;
	std::shared_ptr<CLifespan>cLifespan;
	
	Entity(const std::string & tag,const size_t &id);

	
	bool isActive() const;
	const std::string & tag() const;
	size_t id() const;
	void destroy();

};
