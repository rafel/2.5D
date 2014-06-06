#ifndef SHADOW_H
#define SHADOW_H


#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <vector>
#include "shader.h"
#include "Image.h"

class Image;

class Shadow
{
public:
	Image* parent;
	Shadow(Image* image,GLint textureID);
	void setUpShadow();
	~Shadow();
	void draw(float zPos, glm::mat4 projMatrix,glm::vec3 cameraPosition);
	glm::vec3 position;
	float secondRotationRadius;
	float width, height;
	float rotationAngle, secondRotationAngle;
	void blur(glm::vec2);
	void light(glm::vec2);
	glm::vec3 getRealPosition();
	glm::vec3 getPixelPosition();
	glm::vec3 convertPixelPosToInGameCoord(glm::vec2 pixelPosition);
	bool checkCollisionSquare(glm::vec3 position,glm::vec2 size);
private:

	struct vertexInfo
	{
		glm::vec2 vertex;
		glm::vec2 textureCoord;
	};
		glm::vec2 blurSize;
	glm::vec2 lightPosition;
	std::vector<vertexInfo> vertices;
	GLuint vboId;
	GLint vertexAttribLocation;
	GLint texCoordAttribLocation;
	GLint textureID;
	GLint textureLocation;
	GLint blurSizeLocation;

	GLint lightPositionLocation;
	GLint lightSizeLocation;
	GLint zPosShadowLocation;
	GLint cameraPositionLocation;
	GLint projLocation;
	GLint zPosLocation;
	GLint scaleMatrixLocation;
	GLint translateMatrixLocation;
	GLint rotationMatrixLocation;

	glm::vec3 realPosition;

	Shader* shader;
};

#endif