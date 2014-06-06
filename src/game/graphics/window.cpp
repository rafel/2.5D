#include "Window.h"
#include <iostream>
#include "graphicssettings.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;

bool windowVisibleBool;

// If window closed
int windowCloseCallback(){
	windowVisibleBool=false;
	return windowVisibleBool;
}

// Const , windows prop.
Window::Window() :
	width(WINDOW_WIDTH), height(WINDOW_HEIGHT), title("2.5D with headtracking") {windowVisibleBool=true;}

// Deconst. remove all new objects
Window::~Window()
{
	releaseResources();
}

// Open new window
void Window::initialize(int glMajorVersion, int glMinorVersion) const
{
	if(glfwInit() == GL_FALSE)
		cerr<< "GLFW initialization failed!" <<endl;

	if(glfwOpenWindow(width, height, 0, 0, 0, 8, 24, 8, WINDOW_MODE) == GL_FALSE)
	{
		cerr<< "Creating window failed!" <<endl;
		glfwTerminate();
	}

	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, glMajorVersion);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, glMinorVersion);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//0 = disabled V-sync. 1 = enabled V-sync.
	//Works on Nvidia cards, but ATI cards doesn't care about this...
	glfwSwapInterval(0);
	const char * titleConstString = title.c_str();
	glfwSetWindowTitle(titleConstString);


#ifdef HIDE_MOUSE
	glfwDisable(GLFW_MOUSE_CURSOR);
#endif
	glfwSetWindowCloseCallback(windowCloseCallback);
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		std::cerr<< "Initialize glew failed!  " << glewGetErrorString(err) <<std::endl;
		throw "Initialize glew failed!\n";
	}


}

// Show window
void Window::show()
{
	initialize(OPENGL_MAJOR_VERSION, OPENGL_MINOR_VERSION);
}

// Update window (SwapBuffers)
void Window::update()
{
        glfwSwapBuffers();
}

// Close & terminate window
void Window::releaseResources() const
{
	
	glfwCloseWindow();
	glfwTerminate();
}

// If window visible
bool Window::windowVisible()
{
	return windowVisibleBool;
}

// Get window width
int Window::getWidth() const
{
	return width;
}

// Get window height
int Window::getHeight() const
{
	return height;
}

// Get window title
string Window::getTitle() const 
{
	return title;
}

// Get projection matrix
glm::mat4 Window::getProjecionMatrix()
{
	return  glm::ortho(float(WINDOW_WIDTH)/(-2), float(WINDOW_WIDTH)/(2), float(WINDOW_HEIGHT)/(2), float(WINDOW_HEIGHT)/(-2), -1000.0f, 1000.0f);
}