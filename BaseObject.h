#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <SFML/Graphics.hpp>

class BaseObject
{
public:
	virtual bool shouldRemove();
	virtual std::string getName();
	void destroy();
protected:
	bool remove = false;
	std::string name{ "Baseobject" };
};

#endif