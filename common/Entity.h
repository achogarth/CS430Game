#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>

class Entity
{
public:
	Entity(
		std::vector<glm::vec3> & vertexBuffer,
		std::vector<glm::vec2> & uvBuffer,
		std::vector<glm::vec3> & normalBuffer, //textureBuffer
		char * objPath, //path to .obj file
		glm::vec3 location, //location to place object
		int textureRow,
		int textureColumn
		);

	~Entity(void);

	bool loadObject(const char * path, 
		std::vector<glm::vec3> & out_vertices, 
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals);

	void collide();

	int getBufferPosition();

	int getLengthInBuffer();

	void moveX();

	void moveY();

	void setTexture(
		int row, 
		int col, 
		std::vector<glm::vec2> & textureBuffer
	);// integer between 0 and 7 for row, col to pick the

private:
	int position;
	int length;
	int hitpoints;
	int speed;
};

