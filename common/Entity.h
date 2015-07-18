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

	virtual bool collide(); //virtual makes this abstract

	virtual void move();

	int getBufferPosition();

	int getLengthInBuffer();

	void moveX();

	void moveY(std::vector<glm::vec3> & vertexBuffer, float distance);

	void setTexture(
		int row, 
		int col, 
		std::vector<glm::vec2> & textureBuffer
	);// integer between 0 and 7 for row, col to pick the

	//this method has problems passing the vec4
	void getLocation(std::vector<glm::vec3> & vertexBuffer, glm::vec4 & point);

private:
	int position;
	int length;
	int hitpoints;
	int speed;
};

