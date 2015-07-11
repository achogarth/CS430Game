#include "Entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <cstring>
#include <common/objloader.hpp>

using namespace std;
using namespace glm;

int position;
int length;
int hitpoints;
int speed;
int currentTextureRow, currentTextureCol;


Entity::Entity(){}

Entity::Entity(
	std::vector<glm::vec3> & vertexBuffer, 
	std::vector<glm::vec2> & uvBuffer,
	std::vector<glm::vec3> & normalBuffer,
	char * objPath, 
	glm::vec3 location,
	int textureRow,
	int textureColumn)
{
	//save index of first vertex
	position = int(vertexBuffer.size());
	//read object file

	loadOBJ(objPath, vertexBuffer, uvBuffer, normalBuffer);

	//save number of vertices added to buffer
	length = int(vertexBuffer.size()) - position;

	//set location

	//set hitpoints
	hitpoints = 1;

	//set speed
	speed = 1;

	//set texture
	currentTextureRow = textureRow;
	currentTextureCol = textureColumn;
	setTexture(currentTextureRow,currentTextureCol, uvBuffer);
}


Entity::~Entity(void)
{
}

//load the object from an object file
bool Entity::loadObject(const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals)
{	

	return loadOBJ(path, out_vertices, out_uvs, out_normals);
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

void Entity::setTexture(
	int row, 
	int col, 
	std::vector<glm::vec2> & textureBuffer)
{
	float x = float(col) / 8;
	float y = float(row) / 8;

	glm::vec2 topLeft = glm::vec2(x,y);
	glm::vec2 topRight = glm::vec2(x+0.125,y);
	glm::vec2 bottomLeft = glm::vec2(x,y+0.125);
	glm::vec2 bottomRight = glm::vec2(x+0.125,y+0.125);

	textureBuffer[position+0] = topLeft;//top left
	textureBuffer[position+1] = bottomLeft;//bottom left
	textureBuffer[position+2] = topRight;//top right

	textureBuffer[position+3] = topRight;//top right
	textureBuffer[position+4] = bottomLeft;//bottom left
	textureBuffer[position+5] = bottomRight;//bottom right
	
}
