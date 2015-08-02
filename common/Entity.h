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
		int textureColumn,
		float speed
		);

	~Entity(void);

	bool loadObject(const char * path, 
		std::vector<glm::vec3> & out_vertices, 
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals);

	virtual bool collide(std::vector<glm::vec3> & vertexBuffer, std::vector<Entity*> & bullets, Entity * player, int &enemyCount, int level, std::vector<glm::vec2> & textureBuffer); //virtual makes this abstract

	virtual void move(std::vector<glm::vec3> & vertexBuffer, glm::vec3 location);

	int getBufferPosition();

	int getLengthInBuffer();

	void moveX(std::vector<glm::vec3> & vertexBuffer, float time);

	void moveY(std::vector<glm::vec3> & vertexBuffer, float time);

	void setTexture(
		int row, 
		int col, 
		std::vector<glm::vec2> & textureBuffer
	);// integer between 0 and 7 for row, col to pick the

	void getLocation(std::vector<glm::vec3> & vertexBuffer, glm::vec3 & point);

	double getLifeSpan(void);

	void virtual destroy(std::vector<glm::vec3> & vertexBuffer, std::vector<glm::vec2> & textureBuffer);

	void scale(std::vector<glm::vec3> & vertexBuffer, glm::vec3 & scale);

	void activate();

	void deactivate(void);

	bool isActive(void);

private:
	int position;
	int length;
	int hitpoints;
	int mySpeed;
	double creationTime;
	bool active;
};

