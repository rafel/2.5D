#include "ForegroundLayer.h"

// Const , new gears on button of screen
ForegroundLayer::ForegroundLayer(glm::mat4 projMatrix)
{
	this->projMatrix = projMatrix;

	/* NEW GEARS */
	for (int i=0; i<20; i++){
		gears.push_back(*new Gear(this->projMatrix));
	}

	// Set random property
	std::for_each(  gears.begin(),
                    gears.end(),
                    std::bind2nd(std::mem_fun_ref(&Gear::setRandomProperty),0)
                 );

	// Give random positions
	int counter = 0;
	for(Gear& gear : gears)
	{
		gear.setPosition(glm::vec3(((float(rand()) / float(RAND_MAX)) * (1900 - -1900)) + -1900 ,1150 + ((float(rand()) / float(RAND_MAX)) * (20 - -20)) + -20, ((float(rand()) / float(RAND_MAX)) * (200 - 150)) + 150));
		counter++;
	}
}

// Remove all gears
ForegroundLayer::~ForegroundLayer()
{
	gears.erase(gears.begin(),gears.end());
}

// Draws all gears
void ForegroundLayer::draw(glm::vec3 cameraPosition, float delta){

	// Draws the gears
	std::for_each( gears.begin(),
            gears.end(),
            PrintGear(this->cameraPosition,delta)
            );
}