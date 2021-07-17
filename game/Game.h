#pragma once
#include"Common.h"
#include"Entity.h"
#include"EntityManager.h"

struct PlayerConfig { int SR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, OR, OG, OB, OT, VMIN, VMAX, L; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, OR, OB, OT, V, L; float s; };


class Game {
	sf::RenderWindow m_window;
	bool m_paused = false;
	bool m_running = true;
	EntityManager m_entities;
	//fonts

	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;
	int m_score = 0;
	int m_spawnInterval = 1000;
	int m_currentFrame = 0;
	sf::Clock m_clock;
	sf::Clock deltaClock;
	float dt;


	std::shared_ptr<Entity>m_player;
	//std::shared_ptr<Entity>m_enemy;
	//void init(const std::string &config);
	//void setPaused(bool paused);
	//std::map<std::string, EntityVec>m_entityMap;


	void updatedeltatime();
	void sMovement();
	void sLifespan();
	void sUserInput();
	void sRender(sf::Sprite sprite,sf::Text text);
	void sEnemySpawner();
	void sCollision(sf::Text text);

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity>entity);

public:
	Game(const std::string& configs);
	void init(const std::string& configs);
	void run();

};