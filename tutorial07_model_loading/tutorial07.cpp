//Untitled Game
//By Alasdair Hogarth + David Wagner

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <common/Entity.h>
#include <common\Player.h>
#include <Windows.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm\gtx\string_cast.hpp>
using namespace glm;

#include <common/shader.hpp>
#include <common/texture.hpp>
#include <common/controls.hpp>
#include <common/objloader.hpp>



/*************************************************************
To Do: (! indicates done, % indicates partial completion)
-!	Add method definitions for creating player;
-%	Add method definitions for each type of enemy 
	(this will allow a simple method call to set speed, 
	movement, etc without having to manually set for 
	each of that enemy type);
-	Add second do loop for second level;
-	Remove superfluous tutorial 7 code
**************************************************************/



/*************************************************************
						global variables
**************************************************************/
std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;

std::vector<Entity*> bullets;

bool white = false;
int nextBullet;
///////////////////////////////////////////////////////////////





/*************************************************************
						helper methods
**************************************************************/
Entity* addPlayer (int numOfLives,
		std::vector<glm::vec3> & vertexBuffer,
		std::vector<glm::vec2> & uvBuffer,
		std::vector<glm::vec3> & normalBuffer) //textureBuffer
{
	Entity* player = new Player(
		4,							//number of lives
		vertexBuffer,				//vertex buffer
		uvBuffer,					//texture buffer
		normalBuffer,				//normal buffer
		"Player2.obj",				//object file
		glm::vec3(0.0f,4.0f,0.0f),	//location on screen
		2,							//texture row
		0,							//texture column
		20.0
		);
	return player;
};

Entity* addSpiral (
		std::vector<glm::vec3> & vertexBuffer,
		std::vector<glm::vec2> & uvBuffer,
		std::vector<glm::vec3> & normalBuffer,
		glm::vec3 location)
{
	Entity* spiral = new Entity(
		vertexBuffer,				//vertex buffer
		uvBuffer,					//texture buffer
		normalBuffer,				//normal buffer
		"Player2.obj",				//object file
		location,					//location on screen
		0,							//texture row
		0,
		1.5f);

	return spiral;
}

Entity* addEgg (
		std::vector<glm::vec3> & vertexBuffer,
		std::vector<glm::vec2> & uvBuffer,
		std::vector<glm::vec3> & normalBuffer,
		glm::vec3 location)
{
	Entity* egg = new Entity(
		vertexBuffer,				//vertex buffer
		uvBuffer,					//texture buffer
		normalBuffer,				//normal buffer
		"Player2.obj",				//object file
		location,					//location on screen
		0,							//texture row
		1,
		1.5f);

	return egg;
}

Entity* addBullet (
		std::vector<glm::vec3> & vertexBuffer,
		std::vector<glm::vec2> & uvBuffer,
		std::vector<glm::vec3> & normalBuffer,
		glm::vec3 location)
{
	Entity* bullet = new Entity(
		vertexBuffer,				//vertex buffer
		uvBuffer,					//texture buffer
		normalBuffer,				//normal buffer
		"Player2.obj",				//object file
		location,					//location on screen
		4,							//texture row
		2,
		30.0f);

	return bullet;
}

void setupBullets (int count)
{
	//add three bullets to bullet pool
	for (int i = 0; i < count; i++){
		bullets.push_back(addBullet(vertices,uvs,normals,glm::vec3(1.0f)));
	}
	for (int i = 0; i < bullets.size(); i ++)
	{
		//deactivate bullets
		bullets[i]->deactivate(vertices);	
	}
	nextBullet = 0;
}

///////////////////////////////////////////////////////////////




/*************************************************************
						Main method
**************************************************************/
int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 800, 600, "Game", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	if (white) {glClearColor(20.0f, 20.0f, 20.0f, 0.0f);}
	else {glClearColor(0.0f, 0.0f, 0.0f, 0.0f);}

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");
	
	

	/*************************************************************
						Start Screen Setup
	**************************************************************/

	GLuint Texture = loadBMP_custom("Images/Splash.bmp");

	
	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID  = glGetUniformLocation(programID, "myTextureSampler");
	
	loadOBJ("Splash.obj", vertices, uvs, normals);

	// Load it into a VBO

	/*GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	do
	{
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(glm::vec3), &vertices[0]) ;
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	while( glfwGetKey(window, GLFW_KEY_SPACE ) != GLFW_PRESS);

	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);*/

	/*************************************************************
						Level One Setup
	**************************************************************/

	

	vertices.clear();
	uvs.clear();
	normals.clear();

	// Load the texture
	Texture = loadBMP_custom("Images/WorkingTextures.bmp");
	
	// Get a handle for our "myTextureSampler" uniform
	TextureID  = glGetUniformLocation(programID, "myTextureSampler");

	//add earth and stretch out
	bool res;
	res = loadOBJ("earth.obj", vertices, uvs, normals);
	/*glm::mat4 stretch = glm::scale(glm::mat4(1.0f), glm::vec3(40.0f,3.0f,1.0f));
	for (int i = 0; i< vertices.size();i++){
		glm::vec4 point = glm::vec4(vertices[i],1.0f);
		point = stretch * point;
		vertices[i] = glm::vec3(point.x, point.y, point.z);
	}*/

	//add player model
	Entity* player = addPlayer(4, vertices, uvs, normals);
	glm::vec3 point1 = glm::vec3(1.0f);

	std::vector<Entity*> wave1;
	for (int i = 0; i < 15; i++)
	{
		
		wave1.push_back(addSpiral(vertices,uvs,normals,glm::vec3(-17.5+(2.5*(i)),20.0f,0.0f)));
		wave1.push_back(addEgg(vertices,uvs,normals,glm::vec3(-17.5+(2.5*(i)),22.5f,0.0f)));
		wave1.push_back(addSpiral(vertices,uvs,normals,glm::vec3(-17.5+(2.5*(i)),25.0f,0.0f)));
		wave1.push_back(addEgg(vertices,uvs,normals,glm::vec3(-17.5+(2.5*(i)),27.5f,0.0f)));
	}

	setupBullets(5);

	////////////////////////////////////////////////////////////////////////////////////////



	// Load it into a VBO

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);


	//////////////////////////////////Do Loop///////////////////////////

	do{
		// glfwGetTime is called only once, the first time this function is called
		static double lastTime = glfwGetTime();
		static double bulletTime = lastTime;

		// Compute time difference between current and last frame
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime) / 2;
	
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		//move enemy waves
		for (int i = 0; i < wave1.size(); i++)
		{
			Entity* current = wave1[i];
			if (current->isActive())
			{
				current->moveY(vertices, -deltaTime);
				int currentPos = current->getBufferPosition();
				int len = current->getLengthInBuffer();
			}
			//glBufferSubData(GL_ARRAY_BUFFER, currentPos*sizeof(glm::vec3), (len) *sizeof(glm::vec3), &vertices[0]) ;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS)
		{
			point1 = glm::vec3(1.0f);
			player->getLocation(vertices,point1);
			if (point1.x > -19.0f)
			{
				player->moveX(vertices, -deltaTime);
				int currentPos = player->getBufferPosition();
				int len = player->getLengthInBuffer();
			}
			//glBufferSubData(GL_ARRAY_BUFFER, currentPos*sizeof(glm::vec3), (len) *sizeof(glm::vec3), &vertices[0]) ;
		}

		if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS)
		{
			point1 = glm::vec3(1.0f);
			player->getLocation(vertices,point1);
			if (point1.x < 19.0f){
				player->moveX(vertices, deltaTime);
				int currentPos = player->getBufferPosition();
				int len = player->getLengthInBuffer();
			}
			//glBufferSubData(GL_ARRAY_BUFFER, currentPos*sizeof(glm::vec3), (len) *sizeof(glm::vec3), &vertices[0]) ;
		}

		//move and deactivate bullets
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i]->isActive()){
				bullets[i]->moveY(vertices,deltaTime);
				bullets[i]->getLocation(vertices,point1);
				if (point1.y > 29.0f)
				{
					bullets[i]->deactivate(vertices);
				}
			}
		}

		//
		if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS)
		{
			if (bullets[nextBullet]->isActive())
			{
				//bullet limit reached
				//do nothing
			}
			else
			{

				if ((currentTime - bulletTime) > 0.3){
					//put bullet above player
					point1 = glm::vec3(1.0f);
					player->getLocation(vertices, point1);
					bullets[nextBullet]->move(vertices, glm::vec3(point1.x,point1.y,point1.z));
					bullets[nextBullet]->activate();
					PlaySound("Sounds/pew.wav",NULL,SND_FILENAME|SND_ASYNC);
					nextBullet = (nextBullet + 1) % bullets.size();
					bulletTime = currentTime;
				}
			}
		}

		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs();
		glm::mat4 ProjectionMatrix = getProjectionMatrix();
		glm::mat4 ViewMatrix = getViewMatrix();
		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size()*sizeof(glm::vec3), &vertices[0]) ;
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		lastTime = currentTime;

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}