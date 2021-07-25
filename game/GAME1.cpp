#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include<fstream>
#include"Entity.h"
#include"Vec2.h"
#include"Game.h"
#include"Components.h"
#include<memory>
#include<iostream>
#include <SFML/Window.hpp>
#include<random>
#include <sstream>
#include<ctime>

 int score = 0;
 std::ostringstream scores;
Game::Game(const std::string& configs) {

	init(configs);


}

void Game::init(const std::string & configs)
{
	srand((unsigned int)time(NULL));
	m_window.create(sf::VideoMode(1280, 720), "My window");
	//std::ifstream fin(configs);	
	//m_window.setVerticalSyncEnabled(true);
	//m_window.setFramerateLimit(1200);
	
}




void Game::run() {
	spawnPlayer();
	spawnEnemy();
	int score = 0;
	
	sf::Texture t;
	t.loadFromFile("image/dark.jpeg");
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "failed loading a font";
	}

	//Score
	sf::Text text;
	text.setFont(font);
		scores << "Score: " << score;
	text.setString(scores.str());
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);


	m_window.draw(text);
	if (!t.loadFromFile("image/dark.jpeg"))
		std::cout << "notloaded";
	t.setRepeated(true);
	sf::Sprite sprite(t);
	
	sprite.setTextureRect(sf::IntRect(0, 0, 1380, 720));
	sprite.setTexture(t);
	
	


	
	

	srand(time(0));
	sf::Time currentTime;
	
	
	while (m_running) {
		text.setString(scores.str());

		this->updatedeltatime();
		
		sf::Event event;
		while (m_window.pollEvent(event))
		{
				// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) {
				m_window.close();
			}
		}

		m_currentFrame++;	
		m_entities.update();	
		sEnemySpawner();
		sRender(sprite,text);
		sCollision(text);
		sUserInput();
		sLifespan();
		sMovement();
					   	}


}



void Game::updatedeltatime() {
	this->dt = this->deltaClock.restart().asSeconds();

}


	 
void Game::spawnPlayer() {
	srand((unsigned int)time(NULL));
	auto entity = m_entities.addEntity("entity");
	entity->cTransform = std::make_shared<CTransform>(Vec2(628.0f, 351.0f), Vec2(0.02f, 0.02f), 0.5f); //positon,velocity,angle
	entity->cShape = std::make_shared<CShape>(12.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 5.0f);	
	entity->cTransform->angle += 0.40f;
	entity->cShape->circle.setRotation(entity->cTransform->angle);
	//add input compnent
	entity->cInput = std::make_shared<CInput>();
	m_player = entity;
		}




	void Game::spawnEnemy() {
				
			for (int i = 1; i <= 18; i++) {
			auto enemy = m_entities.addEntity("enemy");
			float x =  rand() %1200  ;
			float y =  rand() % 700 ;
			int j = rand() % 6+3;				
		   	enemy->cTransform = std::make_shared<CTransform>(Vec2(x, y), Vec2(0.15f, 0.15f), 5.55f); //positon,velocity,angle
			enemy->cShape = std::make_shared<CShape>(12.0f,j, sf::Color(rand() % 250, rand() % 250, rand() % 250), sf::Color(rand() % 250, rand() % 250, rand() % 250), 5.0f);
			std::cout << " " << j << std::endl;
			std::cout << "x:" << x << "y: " << y << std::endl;
		}
	}



	void Game::spawnSmallEnemies(std::shared_ptr<Entity> entity) {

		float angle = 360.0 / entity->cShape->circle.getPointCount();
		float rad = angle * 0.0174533;
		auto c = entity->cShape->circle.getPointCount();
		
		for ( unsigned int i = 0; i < c; i++) {
			auto ang = rad * i;
			auto se = m_entities.addEntity("smallenemy");
			se->cLifespan = std::make_shared<CLifespan>(1000, m_currentFrame);
			se->cTransform = std::make_shared<CTransform>(Vec2(entity->cTransform->pos.x, entity->cTransform->pos.y), Vec2(0.05f, 0.05f), 0.05f);
			se->cShape = std::make_shared<CShape>(entity->cShape->circle.getRadius()/c, entity->cShape->circle.getPointCount(), entity->cShape->circle.getFillColor(), entity->cShape->circle.getOutlineColor(), entity->cShape->circle.getOutlineThickness());
			se->cTransform->angle += 1.50f;
			se->cTransform = std::make_shared<CTransform>(Vec2(se->cTransform->pos.x, se->cTransform->pos.y), Vec2(0.15*cos(ang), 0.15f*sin(ang)), 0.05f);
		}
	}




	void Game::spawnBullet(std::shared_ptr<Entity> bullet, const Vec2& mousePos) {
			bullet->cLifespan = std::make_shared<CLifespan>(2000, m_currentFrame);
			bullet->cTransform = std::make_shared<CTransform>(Vec2(m_player->cTransform->pos.x, m_player->cTransform->pos.y), Vec2(.05f, .05f), 1.5f);
			bullet->cShape = std::make_shared<CShape>(5.0f, 10, sf::Color(10, 10, 10), sf::Color(255, 255, 255), 4.0f);
			bullet->cTransform->angle += 2.50f;
			

			float	d1 = mousePos.x - bullet->cTransform->pos.x;
			float	d2	= mousePos.y- bullet->cTransform->pos.y;

			//float l = sqrt(d1*d1 + d2 * d2);
			float d = atan2f(d2, d1);
			bullet->cTransform = std::make_shared<CTransform>(Vec2(bullet->cTransform->pos.x, bullet->cTransform->pos.y), Vec2((float)0.5*cos(d),(float) 0.5*sin(d)),0.5f);
	
	}




	void Game::spawnSpecialWeapon(std::shared_ptr<Entity>entity) {
	
	};



	void Game::sMovement() {
		
		for (auto bullet : m_entities.getEntities("bullet")) {

			bullet->cShape->circle.setPosition(bullet->cTransform->pos.x, bullet->cTransform->pos.y);
			bullet->cTransform->pos.x += bullet->cTransform->velocity.x;
			bullet->cTransform->pos.y += bullet->cTransform->velocity.y;
		}

		
		
		for (auto e : m_entities.getEntities("enemy")) {

			if (e->cTransform->pos.x<0||e->cTransform->pos.y<0) {
					e->cTransform->velocity.x = abs(e->cTransform->velocity.x);
				

				if(e->cTransform->pos.y < 0)
					e->cTransform->velocity.y = abs(e->cTransform->velocity.y);

				if (e->cTransform->pos.y > m_window.getSize().y )
					e->cTransform->velocity.y = -e->cTransform->velocity.y;

				
			}
			
			if (e->cTransform->pos.x > m_window.getSize().x|| e->cTransform->pos.y > m_window.getSize().y) {
				e->cTransform->velocity.x = -e->cTransform->velocity.x;

				if (e->cTransform->pos.y > m_window.getSize().y )
					e->cTransform->velocity.y = -e->cTransform->velocity.y;


				if (e->cTransform->pos.y <0)
					e->cTransform->velocity.y = abs(e->cTransform->velocity.y);

				
			}
			

		
				e->cTransform->pos.x += e->cTransform->velocity.x;
				e->cTransform->pos.y += e->cTransform->velocity.y;
			
			
			
					
		}

		//if(m_entities.getEntities("smallenemy").size()!=0){
			for (auto e : m_entities.getEntities("smallenemy")) {
				e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
				e->cTransform->pos.x += e->cTransform->velocity.x;
				e->cTransform->pos.y += e->cTransform->velocity.y;

			//}
		}

			   		
		if (m_player->cInput->up == true) {
			

			if ( m_player->cTransform->pos.y  <= 25) {
				m_player->cInput->up = false;

			}
			else {
					m_player->cTransform->pos.y += -350 * dt;
								
			}


		}
	

		if (m_player->cInput->down == true) {


			if (m_player->cTransform->pos.y >= m_window.getSize().y-25) {
				m_player->cInput->down = false;

			}
			else {
				m_player->cTransform->pos.y += 350.0f * dt;
				
			}
		
			
		}


		if (m_player->cInput->left == true) {

			if ( m_player->cTransform->pos.x <= 25) {
				m_player->cInput->left = false;

			}
			else {
					m_player->cTransform->pos.x += -350.0f * dt;
				
							}

			
		}



		if (m_player->cInput->right == true) {

			if (m_player->cTransform->pos.x >= m_window.getSize().x-25) {
				m_player->cInput->right = false;

			}
			else {
				m_player->cTransform->pos.x += 350.0f * dt;

						}


		}

	}

	

	void Game::sLifespan() {


		for (auto e : m_entities.getEntities()) {


			if (e->cLifespan) {
				int remaining = e->cLifespan->lifespan - (m_currentFrame - e->cLifespan->frameCreated);
				if (remaining <= 0) {
					e->destroy();
					
				}
				
			}
		}

		

	}





	void Game::sCollision(sf::Text text) {
		
		for (auto b : m_entities.getEntities("bullet")) {
		
			for (auto e : m_entities.getEntities("enemy")) {
				
				if ((abs(e->cTransform->pos.x -b->cTransform->pos.x)<10.0) && (abs(e->cTransform->pos.y - b->cTransform->pos.y)<10.0)) {
					spawnSmallEnemies(e);
					
					++score;
					//std::cout << "Score: " << score;
					scores.str("");
					scores << "Score: " << score;
					text.setString(scores.str());
					
					e->destroy();
					b->destroy();
					
					
				}
			}
		}



	}



	void Game::sEnemySpawner() {

		auto e_count = m_entities.getEntities("enemy");
		if (e_count.size() < 10) {
			spawnEnemy();
		}
			 
	}





	void Game::sRender(sf::Sprite sprite,sf::Text text) {
		m_window.clear();
		m_window.draw(sprite);
		m_window.draw(text);


		
		
		for (auto e : m_entities.getEntities()) {
			
			e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
			e->cTransform->angle += 0.10f;
			e->cShape->circle.setRotation(e->cTransform->angle);
			m_window.draw(e->cShape->circle);
					
		}
		
				m_window.display();
		
		
	}




	void Game::sUserInput() {

			sf::Event event;
			while (m_window.pollEvent(event)) {


				if (event.type == sf::Event::MouseButtonPressed) {


					
					if (event.mouseButton.button == sf::Mouse::Left) {
						
						m_player->cInput->shoot = true;
									float x =(float) event.mouseButton.x;
									float y =(float) event.mouseButton.y;
									auto  bullet =   m_entities.addEntity("bullet");
									spawnBullet(bullet, Vec2(x, y));
					}


					if (event.mouseButton.button == sf::Mouse::Right) {

						std::cout << "Right " << event.mouseButton.x << "," << event.mouseButton.y << "\n";

					}



				}

				




				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					m_player->cInput->up = true;
				

				}
				else {
					m_player->cInput->up = false;
				
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					m_player->cInput->left = true;
				}
				else m_player->cInput->left = false;


				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					m_player->cInput->right = true;
				}

				else m_player->cInput->right = false;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					m_player->cInput->down = true;
				}
				else m_player->cInput->down = false;



				if (event.type == sf::Event::Closed) {

					m_running = false;
				}
				
			




			}

			

		
	

	}	

	