#include "Image.h"
#include <GL/glew.h>
#include <GL/glfw.h>
#include <iostream>
static const GLsizeiptr PositionSize = 6 * 2 * sizeof(GLfloat);
static const GLfloat PositionData[] =
{
	200.0f,200.0f,
		300.0f,200.0f,
		300.0f, 300.0f,
		300.0f, 300.0f,
	200.0f, 300.0f,
	200.0f,200.0f,
};

static const GLsizeiptr ColorSize = 6 * 3 * sizeof(GLubyte);
static const GLubyte ColorData[] =
{
	255,   0,   0,
	255, 255,   0,
		0, 255,   0,
		0, 255,   0,
		0,   0, 255,
	255,   0,   0
};

static const int BufferSize = 2;
static GLuint BufferName[BufferSize];

static const GLsizei VertexCount = 6; 
GLuint vboId = 0;                   // ID of VBO for vertex arrays

enum
{
    POSITION_OBJECT = 0,
    COLOR_OBJECT = 1
};


void Image::draw()
{

	


	glColor3f(0.0f,0.0f,1.0f); //a orange triangle
    // bind VBOs for vertex array and index array
	glBindBuffer(GL_ARRAY_BUFFER, vboId);         // for vertex coordinates
	// do same as vertex array except pointer
	glEnableClientState(GL_VERTEX_ARRAY);             // activate vertex coords array
	glVertexPointer(2, GL_FLOAT, 0, 0);               // last param is offset, not ptr
	glDrawArrays(GL_TRIANGLES,0,VertexCount );
	glDisableClientState(GL_VERTEX_ARRAY);            // deactivate vertex array
	// bind with 0, so, switch back to normal pointer operation
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


Image::Image()
{

	// generate a new VBO and get the associated ID
	glGenBuffers(1, &vboId);

	// bind VBO in order to use
	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	// upload data to VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(PositionData), PositionData, GL_STATIC_DRAW_ARB);

}

Image::~Image()
{
	glDeleteBuffers(1, &vboId);
}



GLuint createVBO(const void* data, int dataSize, GLenum target, GLenum usage)
{
    GLuint id = 0;  // 0 is reserved, glGenBuffersARB() will return non-zero id if success

    glGenBuffersARB(1, &id);                        // create a vbo
    glBindBufferARB(target, id);                    // activate vbo id to use
    glBufferDataARB(target, dataSize, data, usage); // upload data to video card

    // check data size in VBO is same as input array, if not return 0 and delete VBO
    int bufferSize = 0;
    glGetBufferParameterivARB(target, GL_BUFFER_SIZE_ARB, &bufferSize);
    if(dataSize != bufferSize)
    {
        glDeleteBuffersARB(1, &id);
        id = 0;
        std::cout << "[createVBO()] Data size is mismatch with input array\n";
    }

    return id;      // return VBO id
}

void deleteVBO(const GLuint vboId)
{
    glDeleteBuffersARB(1, &vboId);
}