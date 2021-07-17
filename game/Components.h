#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
#include "SFML\System.hpp"

#include "Common.h"
#include "Vec2.h"
class CTransform {

public:
	Vec2 pos = { 0.0,0.0 };
	Vec2 velocity = { 0.0,0.0 };
	float angle = 0;

	CTransform(const Vec2 &p, const Vec2& v, float a) 
		:pos(p), velocity(v), angle(a) {}




};

class CShape {

public:
	sf::CircleShape circle;
	float radius;

	CShape(float radius, int points, const sf::Color & fill, const sf::Color & outline,float thickness )
		:circle(radius, points) {

		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);

	}
				
};

class CCollision {


public:
	float radius = 0;
	CCollision(float r)
		:radius(r){}
};

class CScore {

public:
	int score = 0;
	CScore(int s)
		:score(s) {}
};

class CLifespan {
public:
	int lifespan = 0;
	int frameCreated = 0;
	CLifespan(int duration,int created)
		:lifespan(duration),frameCreated(created){}


};
class CInput {
public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;
	bool specialWeapon = false;
	
	CInput() {
		/*sf::RenderWindow m_window;
		sf::Event event;
		

			

			if (event.key.code == sf::Keyboard::W) {
				
				up = true;
				

					}*/
		
		


		
	}
};





