#pragma once

#include <vector>
#include <string>
#include <glm/glm.hpp>


class Digit
{
public:

	Digit(
		std::vector<glm::vec3> & vertexBuffer,
		std::vector<glm::vec2> & uvBuffer,
		std::vector<glm::vec3> & normalBuffer,
		char * objPath, //path to .obj file
		glm::vec3 & location //location to place object
		);

	~Digit(void);

	void setDigit(
		std::vector<glm::vec2> & uvBuffer,
		int number
		);

	bool loadObject(
		const char * path, 
		std::vector<glm::vec3> & out_vertices, 
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals
		);
private: 
	int digitPosition;
	int digitVertexCount;
};