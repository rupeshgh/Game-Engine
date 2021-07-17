#include "Vec2.h"

#include<math.h>

Vec2::Vec2() {


}

Vec2::Vec2(float xin, float yin) :x(xin), y(yin) {


}

 Vec2 Vec2::operator+(const Vec2& rhs) const {

	return Vec2(x+rhs.x, y + rhs.y);
}

 Vec2 Vec2::operator - (const Vec2& rhs) const {

	return Vec2(x - rhs.x, y - rhs.y);
}

 Vec2 Vec2::operator / (const float val) const {

	return Vec2(x/val, y/val);
}

 Vec2 Vec2::operator *(const float val) const {

	return Vec2(x*val, y*val);
}




bool Vec2::operator ==(const Vec2& rhs) const {
	if ((rhs.x == x) && (rhs.y == y)) {
		return true;
	}
	else {
		return false;
	}
}

bool Vec2::operator !=(const Vec2& rhs) const {

	//return Vec2(0, 0);
	return true;
}




void	Vec2::operator /=(const float val) const {

	
}


void	Vec2::operator *=(const float val) const {

	//return Vec2(0, 0);
}

void  Vec2::operator -=(const Vec2& rhs) const {

	//return Vec2(0, 0);
}
void Vec2::operator +=(const Vec2& rhs) const {
	
	
	
	
	
	
}


float Vec2::dist(const Vec2& rhs) const {

	return 0.f;


}