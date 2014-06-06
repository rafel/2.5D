#include <vector>
#include <fstream>
#include <iostream>
#include "../graphicssettings.h"

#include "glm/glm.hpp"
#include <IL/il.h>
#include "utils.h"


//Bind a 2D texture to OpenGL.
GLuint Utils::bind2DTexture(std::string filename)
{
	ILuint ilTextureID;
	ILboolean success;
	GLuint glTextureID;

	if(ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
		return -1;

	ilInit();
	ilGenImages(1, &ilTextureID);
	ilBindImage(ilTextureID);
	success = ilLoadImage((const ILstring)(std::string(TEXTURE_FILE_PATH) + filename).c_str());

	if(success)
	{
		glGenTextures(1, &glTextureID);
		glBindTexture(GL_TEXTURE_2D, glTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), 
			ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
		glGenerateMipmap(GL_TEXTURE_2D);
		ilDeleteImages(1, &ilTextureID);
	}
	else
		return -1;

	return glTextureID;
}
