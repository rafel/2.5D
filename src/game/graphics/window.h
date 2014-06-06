#ifndef WINDOW_H
#define WINDOW_H

#include <string>

#include <glm/glm.hpp>

class Window
{
	private:
		int width;
		int height;
		void initialize(int, int) const;
		void releaseResources() const; // Ta bort och lägga allt i deconstructor?
		
		std::string title; 
	public:
		Window();
		~Window();
		void show();
		void update();
		bool windowVisible();
		int getWidth() const;
		int getHeight() const;
		glm::mat4 getProjecionMatrix();
		std::string getTitle() const; //ok, varför?
};

#endif