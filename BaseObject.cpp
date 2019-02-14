#include "BaseObject.h"

bool BaseObject::shouldRemove()
{
	return remove;
}
std::string BaseObject::getName()
{
	return name;
}
void BaseObject::destroy()
{
	remove = true;
}