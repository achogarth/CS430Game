#pragma once

#include <common\Entity.h>

class Player: public Entity
{
private:
	int lives;

public:
	Player(int numOfLives,
		std::vector<glm::vec3> & vertexBuffer,
		std::vector<glm::vec2> & uvBuffer,
		std::vector<glm::vec3> & normalBuffer, //textureBuffer
		char * objPath, //path to .obj file
		glm::vec3 location, //location to place object
		int textureRow,
		int textureColumn,
		float speed,
		int hitpoints);

	~Player();

	int getLives();

	int removeLife(); // decrements current lives and returns remaining lives

	virtual void destroy(std::vector<glm::vec3> & vertexBuffer,std::vector<glm::vec2> & textureBuffer);
};