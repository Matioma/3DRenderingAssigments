#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ShaderUtil.h"



/**
 * Basic demo of rendering a triangle in OpenGL through the new programmable pipeline.
 * In a real life example, this code should include error checking and refactor into classes/functions.
 * In addition VAO's are missing.
 */

int main () {
    //Open SFML Window == Valid OpenGL Context
    sf::Window window(
        sf::VideoMode (800, 600),       //800 x 600 x 32 bits pp
        "OpenGL Window",                //title
        sf::Style::Default,             //Default, Fullscreen, Titlebar, etc
        sf::ContextSettings (
            24,                         //24 bits depth buffer, important for 3D!
            0,                          //no stencil buffer
            0,                          //no anti aliasing
            3,                          //requested major OpenGL version
            3                           //requested minor OpenGL version
        )
    );

	window.setVerticalSyncEnabled(true);

    //initialize glew to load all available opengl functions/extensions
    GLenum glewResult = glewInit();
    if (glewResult != GLEW_OK) {
        std::cout << "Could not initialize GLEW, byeeee!" << std::endl;
        return -1;
    }

	//Create the shader program
	GLuint programID = ShaderUtil::createProgram("vertexshader.vs", "fragmentshader.fs");

	//declare the data to upload
	const GLfloat vertices[] = {
		//1 triangle, 3 vertices per triangle, 3 floats per vertex = 9 floats in total
		-0.5f, -0.5f, 0,
		0.5f,  -0.5f, 0,
		-0.5f,  0.5f, 0,
		0.5f,  -0.5f, 0,
		0.5f,   0.5f, 0,
		-0.5f,  0.5f, 0
	};

	//create a handle to the buffer
	GLuint vertexBufferId;
	glGenBuffers(1, &vertexBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex position data will be created
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	//stream all our data to the array buffer endpoint to which our vertexPositionsBufferId is connected
	//note that vertexPositionsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    const GLfloat colors[] {
        //1 triangle, 3 vertices per triangle, 1 color per vertex, 3 "floats" per color RGB = 9 floats in total
        1,0,0,
        0,1,0,
        0,0,1,
		1,0,0,
		0,1,0,
		0,0,1
    };


	

	//create a handle to the buffer
	GLuint colorBufferId;
	glGenBuffers(1, &colorBufferId);
	//bind our buffer to the GL_ARRAY_BUFFER endpoint, since none was bound yet,
	//a new array buffer for vertex color data will be created
	glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
	//stream all our data to the array buffer endpoint to which our vertexColorsBufferId is connected
	//note that vertexColorsBufferId is not mentioned, instead the ARRAY_BUFFER is set as the data "sink"
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	//disconnect the funnel
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	const GLfloat uvs[]{
		0,0,
		1,0,
		0,1,
		1,0,
		1,1,
		0,1
	};


	//Create uv buffer
	GLuint uvBufferId;
	glGenBuffers(1, &uvBufferId);
	
	glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);

	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	sf::Clock clock;


	float rotation = 0;
	float scale = 1;

	float rotationSpeed = 0.1;
	float rotationAcceleration = 1;

	float scaleFactor = 1;

	int patternCols = 10;
	int patternRows = 10;


	float LastTime = clock.getElapsedTime().asSeconds();
	float deltaTime = 0;


    glClearColor(0, 0, 0, 1);
    while (window.isOpen()) {
		float currentTime = clock.getElapsedTime().asSeconds();
		deltaTime = currentTime - LastTime;



		float elapsedTime = clock.getElapsedTime().asSeconds();

		//std::cout << deltaTime << std::endl;


		//empty the event queue
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::Resized) glViewport(0, 0, event.size.width, event.size.height);
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					rotationSpeed += rotationAcceleration * deltaTime;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

					rotationSpeed -= rotationAcceleration * deltaTime;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					
					scale += scaleFactor * deltaTime;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

					scale -= scaleFactor * deltaTime;
				}
			}
		}

		glClear( GL_COLOR_BUFFER_BIT );

        //tell the GPU to use this program
        glUseProgram (programID);

		//offset
		
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2i invertedMousePosition;
		invertedMousePosition.x = mousePosition.x;
		invertedMousePosition.y = window.getSize().y - mousePosition.y;

		std::cout << (float)invertedMousePosition.x << "; " << (float)invertedMousePosition.y << std::endl;


		glUniform2f(glGetUniformLocation(programID, "offset"), 0.5f*cos(elapsedTime), 0.5f*sin(elapsedTime));
		rotation += rotationSpeed * deltaTime;
		glUniform1f(glGetUniformLocation(programID, "rotation"), rotation);
		glUniform1f(glGetUniformLocation(programID, "scale"), scale);



		
		glUniform2f(glGetUniformLocation(programID, "mousePos"), invertedMousePosition.x, invertedMousePosition.y);

		
		glUniform2i(glGetUniformLocation(programID, "colsRows"), patternCols, patternRows);




        //get index for the attributes in the shader
        GLint vertexIndex = glGetAttribLocation(programID, "vertex");
		GLint colorIndex = glGetAttribLocation(programID, "color");
		GLint uvIndex = glGetAttribLocation(programID, "uv");

		//tell OpenGL that the data for the vertexIndex/colorIndex is coming in from an array
		glEnableVertexAttribArray(vertexIndex);
		glEnableVertexAttribArray(colorIndex);
		glEnableVertexAttribArray(uvIndex);

		//bind the buffer with data.
		//the moment this buffer is bound instead of 0, the last param of glVertexAttribPointer
		//is interpreted as an offset and not a pointer
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
		//send the data for this index to OpenGL, specifying it's format and structure
		//vertexIndex // 3 bytes per element // floats // don't normalize // the data itself
		glVertexAttribPointer(vertexIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//send the data for this index to OpenGL, specifying it's format and structure
		//colorIndex // 3 bytes per element // floats // don't normalize // the data itself
		glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
		glVertexAttribPointer(colorIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


		glBindBuffer(GL_ARRAY_BUFFER, uvBufferId);
		glVertexAttribPointer(uvIndex, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//Draws elements from each enabled array using the specified mode (which is default for Unity etc as well)
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glDisableVertexAttribArray (vertexIndex);
        glDisableVertexAttribArray (colorIndex);

        //display it
        window.display();

		
		LastTime = currentTime;
    }

    return 0;
}


