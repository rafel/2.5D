#include "Image.h"
#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GL/glfw.h>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/glm.hpp>
#include "utils.h"
#include <vector>
#include <iostream>
#include <string>
#include "Player.h"

#include "../../GameCore.h"

static const GLsizeiptr PositionSize = 6 * 2 * sizeof(GLfloat);
static const GLsizei VertexCount = 6; 


// Enable light for this image
void Image::enableLight(bool on){
	this->lightOn = on;
}

// Draw image
void Image::draw(glm::mat4 projMatrix,glm::vec3 cameraPosition)
{

	if(rotationAngle<0)rotationAngle+=M_2PI;
	if(rotationAngle>M_2PI)rotationAngle-=M_2PI;

	if(secondRotationAngle>M_2PI)secondRotationAngle-=M_2PI;
	if(secondRotationAngle<0)secondRotationAngle+=M_2PI;
	this->lightOn = lightOnGame;


	realPosition = position;
	
	if(secondRotationRadius!=0.0f)
	{

		//radians
		float xAdd = secondRotationRadius*cos(secondRotationAngle);
		float yAdd = secondRotationRadius*sin(secondRotationAngle);
		realPosition.x=position.x+xAdd;
		realPosition.y=position.y+yAdd;
		
	}

	
	float zRatio = (100.0f/(position.z));
	
	///Here we calulate the transformation and the translation matrices 
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f),glm::vec3((realPosition.x-cameraPosition.x)*WCX*zRatio,(realPosition.y-cameraPosition.y)*WCY*zRatio,0.0f));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),glm::vec3(width*WCX*zRatio,height*WCY*zRatio,0.0));
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f),rotationAngle+secondRotationAngle,glm::vec3(0.0f,0.0f,1.0f));
	///////////////////////////////////////////////////////////////////

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	shader->useProgram(true);


	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projMatrix));
	glUniformMatrix4fv(translateMatrixLocation, 1, GL_FALSE, glm::value_ptr(translateMatrix));
	glUniformMatrix4fv(scaleMatrixLocation, 1, GL_FALSE, glm::value_ptr(scaleMatrix));
	glUniformMatrix4fv(rotationMatrixLocation, 1, GL_FALSE, glm::value_ptr(rotationMatrix));

	glUniform3fv(cameraPositionLocation, 1, glm::value_ptr(cameraPosition));
	glUniform1f(zPosLocation, (GLfloat)position.z);




	glUniform1i(textureLocation, 0);
    
	// Set blur size
	glUniform2fv(blurSizeLocation,1, (GLfloat*)&blurSize);

	// If light on
	if(lightOn){
		// If lighting
		if(playerPosition.x != 0 || playerPosition.y != 0){
			glUniform3fv(lightPositionLocation,1, glm::value_ptr(playerPosition));
			glUniform3fv(lightSizeLocation,1, glm::value_ptr(playerLightSize));
		}
	}
	// No light
	else
	{
		playerPosition.x=0;
		playerPosition.y=0;
		glUniform3fv(lightPositionLocation,1, glm::value_ptr(playerPosition));
		glUniform3fv(lightSizeLocation,1, glm::value_ptr(playerLightSize));
	}


	
	// bind VBOs for vertex array and index array
	glBindBuffer(GL_ARRAY_BUFFER,vboId);         // for vertex coordinates

	
	glEnableVertexAttribArray(vertexAttribLocation);
	//Number of bytes per vertex information. This tells us how many bytes each step takes.
	GLuint stride = sizeof(vertexInfo);
	
	//The offset in each step. float = 4 bytes.
	GLuint offset = 0 * 4;
	glVertexAttribPointer(vertexAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid *)offset);
	glEnableVertexAttribArray(texCoordAttribLocation);
	offset = 2 * 4;
	glVertexAttribPointer(texCoordAttribLocation, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid *)offset);

	glDrawArrays(GL_TRIANGLES,0,VertexCount );
	glDisableVertexAttribArray(texCoordAttribLocation);
    glDisableVertexAttribArray(vertexAttribLocation);
	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	shader->useProgram(false);
	
}

// If image in screen
bool Image::inScreen(){
	glm::vec3 screensides = this->convertPixelPosToInGameCoord(glm::vec2((WINDOW_WIDTH/2),(WINDOW_HEIGHT/2)));
	if(this->position.x < screensides.x + (this->width) && this->position.x > (screensides.x + (this->width))*-1 && this->position.y < screensides.y + (this->height)&& this->position.y > (screensides.y + (this->height))*-1){
		return true;
	}
	return false;
}

// Set image blursize
void Image::blur(glm::vec2 blurSize){
	this->blurSize.x = blurSize.x; 
	this->blurSize.y =  blurSize.y;
}

// Set light position
void Image::light(glm::vec2 lightSourcePosition){
	this->lightPosition.x = 1.0 / lightSourcePosition.x; 
	this->lightPosition.y = 1.0 / lightSourcePosition.y;
}


// Const. reset values. Bind 2dtexture 
Image::Image(std::string imagename)
{
	this->lightOn = true;
	this->rotationAngle = 0.0f;
	this->secondRotationAngle=0.0f;
	this->secondRotationRadius=0.0f;

	position=glm::vec3(0,0,0);
	realPosition= position;

	textureID = Utils::bind2DTexture(imagename);

	vertices.resize(6);

	vertices[0].vertex.x=-1.0f;
	vertices[0].vertex.y=-1.0f;

	vertices[0].textureCoord.x=0.0f;
	vertices[0].textureCoord.y=0.0f;

	vertices[1].vertex.x=1.0f;
	vertices[1].vertex.y=-1.0f;

	vertices[1].textureCoord.x=1.0f;
	vertices[1].textureCoord.y=0.0f;

	vertices[2].vertex.x=1.0f;
	vertices[2].vertex.y=1.0f;

	vertices[2].textureCoord.x=1.0f;
	vertices[2].textureCoord.y=1.0f;
	
	vertices[3].vertex.x=1.0f;
	vertices[3].vertex.y=1.0f;

	vertices[3].textureCoord.x=1.0f;
	vertices[3].textureCoord.y=1.0f;
	
	vertices[4].vertex.x=-1.0f;
	vertices[4].vertex.y=1.0f;

	vertices[4].textureCoord.x=0.0f;
	vertices[4].textureCoord.y=1.0f;

	vertices[5].vertex.x=-1.0f;
	vertices[5].vertex.y=-1.0f;
	
	vertices[5].textureCoord.x=0.0f;
	vertices[5].textureCoord.y=0.0f;


	vboId = 0;
	

	// generate a new VBO and get the associated ID
	glGenBuffers(1, &vboId);

	// bind VBO in order to use
	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	// upload data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexInfo) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	shader = new Shader("imageVS.glsl", "imageFS.glsl");
	shader->setupShaders();
	vertexAttribLocation = shader->getAttribLocation("vertex");
	texCoordAttribLocation = shader->getAttribLocation("textureCoord");
	projLocation = shader->getUniformLocation("projMatrix");
	textureLocation = shader->getUniformLocation("textureWallpaper");

	scaleMatrixLocation = shader->getUniformLocation("scaleMatrix");
	translateMatrixLocation = shader->getUniformLocation("translationMatrix");
	rotationMatrixLocation = shader->getUniformLocation("rotationMatrix");
	this->blurSizeLocation = shader->getUniformLocation("blurSize");
	this->lightPositionLocation = shader->getUniformLocation("lightPosition");
	
	this->lightSizeLocation = shader->getUniformLocation("lightSize");
	cameraPositionLocation = shader->getUniformLocation("cameraPosition");
	zPosLocation = shader->getUniformLocation("Zpos");

}

// Deconst. 
Image::~Image()
{
	glDeleteBuffers(1, &vboId);


	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	glDisableVertexAttribArray(vertexAttribLocation);
	glDisableVertexAttribArray(texCoordAttribLocation);
	
	delete shader;	// Delete shader 
}

// Return real position in world
glm::vec3 Image::getRealPosition()
{
	return realPosition;
}

// Return pixel position
glm::vec3 Image::getPixelPosition()
{
	float zRatio = (100.0f/(position.z));
	return glm::vec3(realPosition.x*WCX*zRatio,realPosition.y*WCY*zRatio,0.0f);
}

// Pixel to game coord
glm::vec3 Image::convertPixelPosToInGameCoord(glm::vec2 pixelPosition)
{
	float zRatio = (100.0f/(float(position.z)));
	return glm::vec3(pixelPosition.x/(WCX*zRatio),pixelPosition.y/(WCY*zRatio),position.z);
}

// Check collision for position with size
bool Image::checkCollisionSquare(glm::vec3 position,glm::vec2 size){
	float distance = glm::distance(position,this->position);
	if(distance < ((this->height+this->width)/2) + ((size.x+size.y)/2)){
		return true;
	}
	return false;
}

// get real rotation angle
float Image::getRealRotationAngle()
{
	return rotationAngle+secondRotationAngle;
}