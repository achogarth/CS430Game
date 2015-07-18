#include "Entity.h"

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <cstring>
#include <common/objloader.hpp>

#include <iostream>
#include <glm\gtx\string_cast.hpp>
//using namespace glm;

int position;
int vertexCount;
int hitpoints;
int mySpeed;
int currentTextureRow, currentTextureCol;
double creationTime;

Entity::Entity(
	std::vector<glm::vec3> & vertexBuffer, 
	std::vector<glm::vec2> & uvBuffer,
	std::vector<glm::vec3> & normalBuffer,
	char * objPath, 
	glm::vec3 location,
	int textureRow,
	int textureColumn,
	float speed)
{
	//save references to buffers
	//save index of first vertex
	position = int(vertexBuffer.size());
	//read object file
	loadOBJ(objPath, vertexBuffer, uvBuffer, normalBuffer);

	//save number of vertices added to buffer
	vertexCount = int(vertexBuffer.size()) - position;

	//set location of object
	glm::mat4 translate = glm::translate(glm::mat4(1.0f),location);
	for (int i = position; i < position + vertexCount; i++){
		glm::vec4 point = glm::vec4(vertexBuffer[i],1.0f);
		point = translate * point;
		vertexBuffer[i] = glm::vec3(point.x, point.y, point.z);
	}

	//set hitpoints
	hitpoints = 1;

	//set speed
	mySpeed = speed;

	//set texture
	currentTextureRow = textureRow;
	currentTextureCol = textureColumn;
	setTexture(currentTextureRow,currentTextureCol, uvBuffer);

	//set creationtime
	creationTime = glfwGetTime();
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

bool Entity::collide()
{
	return false;
}

void Entity::move()
{
}

int Entity::getBufferPosition()
{
	return position;
}

int Entity::getLengthInBuffer()
{
	return vertexCount;
}

void Entity::moveX(std::vector<glm::vec3> & vertexBuffer, float time)
{
	glm::vec4 point;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f),glm::vec3((mySpeed*time),0.0f,0.0f));
	for (int i = position; i < (position + vertexCount); i++)
	{
		point = glm::vec4(vertexBuffer[i], 1.0f);
		point = trans * point;
		//std::cout<< "point "<<glm::to_string(point)<< std::endl;
		vertexBuffer[i] = glm::vec3(point.x,point.y,point.z);
		//std::cout<< "buffer " <<glm::to_string(vertexBuffer[i])<< std::endl;
	}
}

void Entity::moveY(std::vector<glm::vec3> & vertexBuffer, float time)
{
	glm::vec4 point;
	glm::mat4 trans = glm::translate(glm::mat4(1.0f),glm::vec3(0.0f,(mySpeed*time),0.0f));
	for (int i = position; i < (position + vertexCount); i++)
	{
		point = glm::vec4(vertexBuffer[i], 1.0f);
		point = trans * point;
		//std::cout<< "point "<<glm::to_string(point)<< std::endl;
		vertexBuffer[i] = glm::vec3(point.x,point.y,point.z);
		//std::cout<< "buffer " <<glm::to_string(vertexBuffer[i])<< std::endl;
	}

}

void Entity::setTexture(
	int row, 
	int col, 
	std::vector<glm::vec2> & textureBuffer)
{
	float x = float(col) / 8;
	float y = float(row) / 8;

	glm::vec2 topLeft = glm::vec2(x,y+0.125);
	glm::vec2 topRight = glm::vec2(x+0.125,y+0.125);
	glm::vec2 bottomLeft = glm::vec2(x,y);
	glm::vec2 bottomRight = glm::vec2(x+0.125,y);

	textureBuffer[position+0] = topLeft;//top left
	textureBuffer[position+1] = bottomLeft;//bottom left
	textureBuffer[position+2] = topRight;//top right

	textureBuffer[position+3] = topRight;//top right
	textureBuffer[position+4] = bottomLeft;//bottom left
	textureBuffer[position+5] = bottomRight;//bottom right
	
}

void Entity::getLocation(std::vector<glm::vec3> & vertexBuffer, glm::vec4 & point)
{
	//calculate center of entity and return the center point
	
	//calculate average x
	float x, minX, maxX;
	minX = maxX = vertexBuffer[position].x;

	//calculate average y
	float y, minY, maxY;
	minY = maxY = vertexBuffer[position].y;
	for (int i = position; i < (position + vertexCount); i++)
	{
		
		//x values
		float value = vertexBuffer[i].x;
		if (value < minX)
		{
			minX = value;
		}
		else if (value > maxX)
		{
			maxX = value;
		}
		x = (minX + maxX)/2;

		//y values
		value = vertexBuffer[i].y;
		if (value < minY)
		{
			minY = value;
		}
		else if (value > maxY)
		{
			maxY = value;
		}

		y = (minY + maxY)/2;
		

		
	}

	point.x = x;
	point.y = y;
	point.z = 0.0f;
	point.w = 1.0f;

}

double Entity::getLifeSpan(void)
{
	return glfwGetTime() - creationTime;
}
