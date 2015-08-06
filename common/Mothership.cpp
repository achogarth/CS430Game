#include <common\Entity.h>
#include <common\Mothership.h>
#include <Windows.h>
#include <iostream>

using namespace std;
using namespace glm;


Mothership::Mothership(
	std::vector<glm::vec3> & vertexBuffer,
	std::vector<glm::vec2> & uvBuffer,
	std::vector<glm::vec3> & normalBuffer, //textureBuffer
	char * objPath, //path to .obj file
	glm::vec3 location, //location to place object
	int textureRow,
	int textureColumn,
	float speed,
	int hitpoints): Entity(
	vertexBuffer,
	uvBuffer,
	normalBuffer, //textureBuffer
	objPath, //path to .obj file
	location, //location to place object
	textureRow,
	textureColumn,
	speed,
	hitpoints)
{
	setTexture(textureRow,textureColumn, uvBuffer);
}

void Mothership::destroy(std::vector<glm::vec3> & vertexBuffer,std::vector<glm::vec2> & textureBuffer)
{
	

}

bool Mothership::collide(std::vector<glm::vec3> & vertexBuffer, std::vector<Entity*> & bullets, Entity * player, int &enemyCount, int level, std::vector<glm::vec2> & textureBuffer)
{
	//get center of this item
	glm::vec3 self = glm::vec3(1.0f);
	getLocation(vertexBuffer, self);

	glm::vec3 other = glm::vec3(1.0f);

	float dx, dy, distance;
	//check player collisions
	player->getLocation(vertexBuffer,other);

	dx = self.x - other.x;
	dy = self.y - other.y;

	distance = sqrt(dx * dx + dy * dy);

	if (distance < 19.5)
	{
		//collision
		return true;
	}
	return false;
}

void Mothership::setTexture(
	int row, 
	int col, 
	std::vector<glm::vec2> & textureBuffer)
{
	float x = float(col) / 8;
	float y = float(row) / 8;

	glm::vec2 topLeft = glm::vec2(0.625,0.875);
	glm::vec2 topRight = glm::vec2(1.0,0.875);
	glm::vec2 bottomLeft = glm::vec2(0.625,0.5);
	glm::vec2 bottomRight = glm::vec2(1.0,0.5);

	textureBuffer[getBufferPosition()+0] = topLeft;//top left
	textureBuffer[getBufferPosition()+1] = bottomLeft;//bottom left
	textureBuffer[getBufferPosition()+2] = topRight;//top right

	textureBuffer[getBufferPosition()+3] = topRight;//top right
	textureBuffer[getBufferPosition()+4] = bottomLeft;//bottom left
	textureBuffer[getBufferPosition()+5] = bottomRight;//bottom right
	
}