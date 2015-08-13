#pragma once

#include <common\Entity.h>

class Mothership: public Entity
{
private:

public:
	Mothership(
		std::vector<glm::vec3> & vertexBuffer,
		std::vector<glm::vec2> & uvBuffer,
		std::vector<glm::vec3> & normalBuffer, //textureBuffer
		char * objPath, //path to .obj file
		glm::vec3 location, //location to place object
		int textureRow,
		int textureColumn,
		float speed,
		int hitpoints);

	~Mothership();

	virtual void destroy(std::vector<glm::vec3> & vertexBuffer,std::vector<glm::vec2> & textureBuffer);

	virtual bool collide(std::vector<glm::vec3> & vertexBuffer, std::vector<Entity*> & bullets, Entity * player, int &enemyCount, int level, std::vector<glm::vec2> & textureBuffer);

	virtual void setTexture(int row, int col, std::vector<glm::vec2> & textureBuffer);

};