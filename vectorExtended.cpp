#include <iomanip>
#define _USE_MATH_DEFINES
//#include <cmath>
#include <math.h>
#include <random>
#include "vectorExtended.h"

std::ostream& operator <<(std::ostream& os, const sf::Vector2f v)
{
	os << std::setw(6) << std::setprecision(2) << std::fixed << v.x << ", " << v.y;
	return os;
}
std::ostream& operator <<(std::ostream& os, const sf::Vector2i v)
{
	os << v.x << ", " << v.y;
	return os;
}
float dot(const sf::Vector2f& lv, const sf::Vector2f& rv)
{
	return lv.x * rv.x + lv.y * rv.y;
}
float length(const sf::Vector2f & v)
{
	return sqrt(dot(v, v));
}
sf::Vector2f normalize(sf::Vector2f v)
{
	float length = sqrt(dot(v, v));
	if (length != 0)
	{
		v /= length;
	}
	return v;
}
sf::Vector2f vectorRegulate(sf::Vector2f v, float const maxLength)
{
	sf::Vector2f temp;
	sf::Vector2f dir = normalize(v);
	if (length(v)>maxLength)
	{
		temp = dir*maxLength;
		return temp;
	}
	return v;
}
float vectorAngle(sf::Vector2f v)
{
	float angle;
	if (v.x<0)
	{
		angle = 180 + (atan(float(v.y) / float(v.x)) * 180) / M_PI;
	}
	else
	{
		angle = (atan(float(v.y) / float(v.x)) * 180) / M_PI;
	}
	if (angle<0)
	{
		angle += 360.0;
	}
	return angle;
}
sf::Vector2f vectorRotate(sf::Vector2f const & v, float const deg)
{
	sf::Vector2f temp;
	float l = length(v);
	float angle = vectorAngle(v);
	temp.x = l*cos(((angle + deg)*M_PI) / 180);
	temp.y = l*sin(((angle + deg)*M_PI) / 180);
	return temp;
}
float random_range(float const min, float const max)
{
	std::random_device r;
	std::uniform_real_distribution<> dis(min, max);
	return dis(r);
}