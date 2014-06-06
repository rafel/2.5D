#include "Shadow.h"
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

static const GLsizeiptr PositionSize = 6 * 2 * sizeof(GLfloat);
static const GLsizei VertexCount = 6; 

void Shadow::draw(float zPosShadow,glm::mat4 projMatrix,glm::vec3 cameraPosition)
{
	setUpShadow();
	//glm::vec3 newPosition = parent->position;
	glm::vec3 newPosition = position;
	secondRotationAngle=parent->secondRotationAngle;
	secondRotationRadius=parent->secondRotationRadius;
	width=parent->width;
	height=parent->height;




	if(secondRotationRadius!=0.0f)
	{
		//degrees
		//float xAdd = secondRotationRadius*cos(secondRotationAngle * M_PI / 180.0f);
		//float yAdd = secondRotationRadius*sin(secondRotationAngle * M_PI / 180.0f);

		//radians
		float xAdd = secondRotationRadius*cos(secondRotationAngle);
		float yAdd = secondRotationRadius*sin(secondRotationAngle);
		newPosition.x=position.x+xAdd;
		newPosition.y=position.y+yAdd;
		
	}
	realPosition= glm::vec3(newPosition.x,newPosition.y,newPosition.z);

	
	float zRatio = (100.0f/(position.z));
	
	///Here we calulate the transformation and the translation matrices 
	glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f),glm::vec3((newPosition.x-cameraPosition.x)*WCX*zRatio,(newPosition.y-cameraPosition.y)*WCY*zRatio,0.0f));
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
	glUniform1f(zPosShadowLocation, (GLfloat)zPosShadow);




	glUniform1i(textureLocation, 0);
    
	// If blur
	if(this->blurSize.x != 0 || this->blurSize.y != 0){
		glUniform2fv(blurSizeLocation,1, (GLfloat*)&blurSize);
	}

		
	// If lighting
	if(playerPosition.x != 0 || playerPosition.y != 0){
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


void Shadow::blur(glm::vec2 blurSize){
	this->blurSize.x = 1.0 / blurSize.x; 
	this->blurSize.y = 1.0 / blurSize.y;
}

void Shadow::light(glm::vec2 lightSourcePosition){
	this->lightPosition.x = 1.0 / lightSourcePosition.x; 
	this->lightPosition.y = 1.0 / lightSourcePosition.y;
}



Shadow::Shadow(Image* image,GLint textureID)
{
	this->parent = image;
	this->rotationAngle = 0.0f;
	this->secondRotationAngle=0.0f;
	this->secondRotationRadius=0.0f;
	position=glm::vec3(0,0,0);
	realPosition= position;

	this->textureID = textureID;

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

	shader = new Shader("shadowVS.glsl", "shadowFS.glsl");
	shader->setupShaders();
	vertexAttribLocation = shader->getAttribLocation("vertex");
	texCoordAttribLocation = shader->getAttribLocation("textureCoord");
	projLocation = shader->getUniformLocation("projMatrix");
	textureLocation = shader->getUniformLocation("textureWallpaper");

	scaleMatrixLocation = shader->getUniformLocation("scaleMatrix");
	translateMatrixLocation = shader->getUniformLocation("translationMatrix");
	rotationMatrixLocation = shader->getUniformLocation("rotationMatrix");
	this->lightPositionLocation = shader->getUniformLocation("lightPosition");

	this->blurSizeLocation = shader->getUniformLocation("blurSize");
	
	
	this->zPosShadowLocation = shader->getUniformLocation("zPosShadow");
	cameraPositionLocation = shader->getUniformLocation("cameraPosition");
	zPosLocation = shader->getUniformLocation("Zpos");

}

void Shadow::setUpShadow(){
	this->height = parent->height;
	this->width = parent->width;
	this->position = parent->position;
	this->position.x -= 100;
	this->position.y -= 100;
	this->rotationAngle = parent->rotationAngle;
}

Shadow::~Shadow()
{
	glDeleteBuffers(1, &vboId);


	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	
	glDisableVertexAttribArray(vertexAttribLocation);
	glDisableVertexAttribArray(texCoordAttribLocation);
	
	//glDeleteTextures(1, &textureID);
	delete shader;
	//shader->releaseResources();


}


glm::vec3 Shadow::getRealPosition()
{
	return realPosition;
}

glm::vec3 Shadow::getPixelPosition()
{
	float zRatio = (100.0f/(position.z));
	return glm::vec3(realPosition.x*WCX*zRatio,realPosition.y*WCY*zRatio,0.0f);
}


glm::vec3 Shadow::convertPixelPosToInGameCoord(glm::vec2 pixelPosition)
{
	float zRatio = (100.0f/(float(position.z)));
	return glm::vec3(pixelPosition.x/(WCX*zRatio),pixelPosition.y/(WCY*zRatio),position.z);
}

bool Shadow::checkCollisionSquare(glm::vec3 position,glm::vec2 size){
	float distance = glm::distance(position,this->position);
	if(distance < ((this->height+this->width)/2) + ((size.x+size.y)/2)){
		return true;
	}
	return false;
}