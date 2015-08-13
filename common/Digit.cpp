#include "Digit.h"

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
#include <algorithm>
#include <stdlib.h>

#include <iostream>
#include <glm\gtx\string_cast.hpp>

int digitPosition;
int digitVertexCount;

Digit::Digit(
	std::vector<glm::vec3> & vertexBuffer,
	std::vector<glm::vec2> & uvBuffer,
	std::vector<glm::vec3> & normalBuffer,
	char * objPath, //path to .obj file
	glm::vec3 & location) //location to place object)
{
	//store location
	digitPosition = int(vertexBuffer.size());

	//read object file
	loadOBJ(objPath, vertexBuffer, uvBuffer, normalBuffer);
	
	//save number of vertices added to buffer
	digitVertexCount = int(vertexBuffer.size()) - digitPosition;

	glm::mat4 translate = glm::translate(glm::mat4(1.0f),location);
	for (int i = digitPosition; i < digitPosition + digitVertexCount; i++){
		glm::vec4 point = glm::vec4(vertexBuffer[i],1.0f);
		point = translate * point;
		vertexBuffer[i] = glm::vec3(point.x, point.y, point.z);
	}

	//save number of vertices added to buffer
	digitVertexCount = int(vertexBuffer.size()) - digitPosition;

	setDigit(uvBuffer,0);
}

void Digit::setDigit(
	std::vector<glm::vec2> & textureBuffer,
	int number)
{
	int row, col;

	switch (number)
	{
	case 0:
		row = 2; col = 6; break;
	case 1:
		row = 2; col = 7; break;
	case 2:
		row = 1; col = 0; break;
	case 3:
		row = 1; col = 1; break;
	case 4:
		row = 1; col = 2; break;
	case 5:
		row = 1; col = 3; break;
	case 6:
		row = 1; col = 4; break;
	case 7:
		row = 1; col = 5; break;
	case 8:
		row = 1; col = 6; break;
	case 9:
		row = 1; col = 7; break;
	default:
		return;
	}

	float x = float(col) / 8;
	float y = float(row) / 8;

	glm::vec2 topLeft = glm::vec2(x,y+0.125);
	glm::vec2 topRight = glm::vec2(x+0.125,y+0.125);
	glm::vec2 bottomLeft = glm::vec2(x,y);
	glm::vec2 bottomRight = glm::vec2(x+0.125,y);

	textureBuffer[digitPosition+0] = topLeft;//top left
	textureBuffer[digitPosition+1] = bottomLeft;//bottom left
	textureBuffer[digitPosition+2] = topRight;//top right

	textureBuffer[digitPosition+3] = topRight;//top right
	textureBuffer[digitPosition+4] = bottomLeft;//bottom left
	textureBuffer[digitPosition+5] = bottomRight;//bottom right

}

bool Digit::loadObject(const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals)
{	
	return loadOBJ(path, out_vertices, out_uvs, out_normals);
}