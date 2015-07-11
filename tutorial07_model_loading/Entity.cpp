#include "Entity.h"


int position;
int length;
int hitpoints;
int speed;


Entity::Entity(void)
{
	position = 1;
	length = 1;
	hitpoints = 1;
	speed = 1;
}


Entity::~Entity(void)
{
}

//load the object from an object file
bool Entity::loadObject()
{
	return true;
}

void Entity::collide()
{
}

int Entity::getBufferPosition()
{
	return position;
}

int Entity::getLengthInBuffer()
{
	return length;
}

void Entity::moveX()
{
}

void Entity::moveY()
{
}
