#include <common\Entity.h>
#include <common\Player.h>
#include <Windows.h>
#include <iostream>

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
	lives = numOfLives;
	switch (lives){
	case 1:
		setTexture(2,2,uvBuffer);
		break;
	case 2:
		setTexture(2,1,uvBuffer);
		break;
	default:
		setTexture(2,2,uvBuffer);
		break;
	}
}

int Player::getLives(){return lives;}

int Player::removeLife()
{
		if (lives > 0) 
		{
			return --lives;
		}

		return 0;
}

void Player::destroy(std::vector<glm::vec3> & vertexBuffer,std::vector<glm::vec2> & textureBuffer)
{
	cout << "Player destroy method called" << endl;
	setTexture(3,4,textureBuffer);
	removeLife();
	switch (lives){
	case 3:
		setTexture(2,0,textureBuffer);
		break;
	case 2:
		setTexture(2,1,textureBuffer);
		break;
	case 1:
		setTexture(2,2,textureBuffer);
		Sleep(2000);
		break;
	default:
		setTexture(3,4,textureBuffer);
		break;
	}

}