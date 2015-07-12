#include <common\Entity.h>
#include <common\Player.h>

using namespace std;
using namespace glm;

int lives;

Player::Player(
	int numOfLives, 
	std::vector<glm::vec3> & vertexBuffer,
	std::vector<glm::vec2> & uvBuffer,
	std::vector<glm::vec3> & normalBuffer, //textureBuffer
	char * objPath, //path to .obj file
	glm::vec3 location, //location to place object
	int textureRow,
	int textureColumn): Entity(
	vertexBuffer,
	uvBuffer,
	normalBuffer, //textureBuffer
	objPath, //path to .obj file
	location, //location to place object
	textureRow,
	textureColumn)
{
	lives = numOfLives;
}

int Player::getLives(){return lives;}

int Player::removeLife(){
	if (lives > 0) 
	{
		return --lives;
	}
	return lives;
}