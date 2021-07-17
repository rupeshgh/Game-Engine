
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"


#include <iostream>
#include<memory>

#include"Game.h"

int main() {

	Game g("configs.txt");
	//Game g;
	g.run();


}






























//typedef std::vector<std::shared_ptr<Entity>>EntityVec;
//class EntityManager {
//	EntityVec m_entities;
//	EntityVec m_toAdd;//to avoid iterator invalidation
//	std::map<std::string, EntityVec>m_entityMap;
//	size_t m_totalEntities = 0;
//
//public:
//	EntityManager();
//	
//	void update();//add m_toAdd
//	std::shared_ptr<Entity>addEntity(const std::string &tag);
//	EntityVec &getEntities();
//	EntityVec & getEntities(const std::string & tag);
//	
//};
//std::shared_ptr<Entity>EntityManager::addEntity(tag) {
//	auto e = std::make_shared<Entity>(tag, m_totalEntities++);
//	m_entities.push_back(e);
//	m_entityMap[tag].push_back(e);
//	return e;
//}
//void EntityManager::update() {
//
//	for (auto e : m_toAdd) {
//
//		m_entities.push_back(e);
//		m_entityMap[e->tag()].push_back(e);
//	}
//	m_toAdd.clear();
//
//	//for(auto e:m_entities) //if e dies remove from m_entities
//	//if e dies remove it from m_entityMap[e->tag()]
//	//need to fix iterator invalidation here as well...higher version of c++ support remove_if
//
//
//	//need another for dead/alive
//}
//class Entity {
//
//	const size_t id = 0;
//	const std::string tag = "Default";
//	bool m_alive = true;
//public:
//	std::shared_ptr<CTransform>cTransform;
//	std::shared_ptr<CName>cName;
//	std::shared_ptr<CShape>cShape;
//	std::shared_ptr<CBBox>cBBox;
//
//	Entity(const std::string & tag, size_t id);
//
//};
//class Vec2 {
//
//public:
//	float x = 0;
//	float y = 0;
//	
//
//	
//};


//int main() {
//
//	EntityManager m_entities;
//
//
//
//	return 0;
//
//
//
//
//}










































//int main()
//{
//	const int wWidth = 640;
//	const int wHeight = 480;
//	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
//	window.setFramerateLimit(60);
//	
//	
//	sf::CircleShape circle(50,50); //2nd par 3= triangle,4= square and so on	
//	circle.setFillColor(sf::Color(255,255,255));
//	
//	circle.setPosition(300.f, 300.f);
//	float circleMoveSpeed = 2.13f;
////	sf::Font font;
////if (!font.loadFromFile("Demoness.ttf"))
////return EXIT_FAILURE;
////sf::Text text("helloworld",font, 55);
////
//////text.setPosition(0.f, 480.0- (float)text.getCharacterSize());
////text.setPosition(320.0f, 240.0f);
//
//	while (window.isOpen())
//	{
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//
//		if (event.type == sf::Event::KeyPressed) {
//
//			std::cout << "key pressed code=" << event.key.code << "\n";
//
//		}
//		if (event.key.code == sf::Keyboard::X) {
//
//			circleMoveSpeed *= -1.0f;
//		}
//		
//		circle.setPosition(circle.getPosition().x - circleMoveSpeed, circle.getPosition().y - circleMoveSpeed);
//
//		
//		window.draw(circle);window.clear();	window.display();
	
//		//window.draw(text);
//		
//
//	
//	}
//	
//	return 0;
//}