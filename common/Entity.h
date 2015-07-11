#pragma once
class Entity
{
public:
	Entity(void);
	~Entity(void);

	bool loadObject();
	void collide();
	int getBufferPosition();
	int getLengthInBuffer();
	void moveX();
	void moveY();

private:
	int position;
	int length;
	int hitpoints;
	int speed;
};

