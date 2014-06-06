#include "Leg.h"


// Const. new images
Leg::Leg()
{
	legPartFirst= new Image("playerLeg.png");
	legPartFirst->width=200.0f;
	legPartFirst->height=200.0f;
	
	legPartSecond= new Image("playerLeg.png");
	legPartSecond->width=300.0f;
	legPartSecond->height=200.0f;

	debugPic= new Image("grendizer.png");
	debugPic->width=50.0f;
	debugPic->height=50.0f;
	
	debugPic->secondRotationRadius=0;
	legPartFirst->rotationAngle=M_PI;
	reorganizeLegParts();
	footPosition= getRealFootPosition();
	desiredPosition=footPosition;
	desiredPositionWay= LEG_GOTO_NOTHING;
	debugPic->position = footPosition;
	isStanding=false;
	currentGear=NULL;
	
}

// Delete images
Leg::~Leg()
{
	delete legPartFirst;
	delete legPartSecond;
	delete debugPic;
}

// Draw leg
void Leg::draw(glm::mat4 projMatrix, glm::vec3 cameraPosition, float delta)
{
	this->delta=delta;
	reorganizeLegParts();
	
	checkCollisionWithDesiredPosition();

	legPartFirst->draw(projMatrix,cameraPosition);
	legPartSecond->draw(projMatrix,cameraPosition);
	debugPic->draw(projMatrix,cameraPosition);

	/////////////////////////////////////////////
	if(glm::distance(legPartFirst->getRealPosition(),desiredPosition)<(legPartFirst->width+legPartSecond->width))
	{
		//close to reach
		




		if(isStanding)
		{
			//Standing, do the legs like this?

			if(currentGear!=NULL)
			{
				float mainPointAngle = atan2(currentGear->getPosition().y-legPartFirst->getRealPosition().y,currentGear->getPosition().x-legPartFirst->getRealPosition().x);
				float footPointAngle = atan2(currentGear->getPosition().y-footPosition.y,currentGear->getPosition().x-footPosition.x);

				if(this->legDirection==LEG_LEFT_DIR)
				{
					if(mainPointAngle<(footPointAngle+0.1f))
					{
						currentGearHillIndex--;
					}
					else if(getExpansionPercent()>0.95f)
					{
						currentGearHillIndex++;
					}
				}
				else
				{
				
				
					if(mainPointAngle>(footPointAngle-0.1f))
					{
						currentGearHillIndex++;
					}
					else if(getExpansionPercent()>0.95f)
					{
						currentGearHillIndex--;
					}
				}


			}


			


			
		}
		else
		{
			//Not Standing, moove to the destination
			moveTowardsDesiredPosition();
		}

	}
	else
	{
		//Too far to reach, do we have the right destination point?
		if(currentGear!=NULL)
		{
			if(checkCollisionWithGear(currentGear)==false)
			{
				currentGear=NULL;
				
			}
			else
			{
				//look here, do we need this?
			}
		}
		else
		{
			//nothing to do...., lets take in the leg	
			//TODO: LEFT LEG!
			

			float r = radius + (legPartFirst->width+legPartSecond->width)/3.0f;
			float xAdd = r*cos(rotationAngle);
			float yAdd = r*sin(rotationAngle);
			footPosition = glm::vec3(rotationCenterPoint.x+xAdd,rotationCenterPoint.y+yAdd,rotationCenterPoint.z);					


			

			//animation did not work
			//desiredPositionWay=LEG_GOTO_WAY_LINEAR;
			//desiredPosition = glm::vec3(rotationCenterPoint.x+xAdd,rotationCenterPoint.y+yAdd,rotationCenterPoint.z);
			//moveTowardsDesiredPosition();

		}
		

	}


	if(glfwGetKey('U')==GLFW_PRESS)
	{
		
		
		if(currentGear!=NULL)
		{
			
			float mainPointAngle = atan2(currentGear->getPosition().y-legPartFirst->getRealPosition().y,currentGear->getPosition().x-legPartFirst->getRealPosition().x);
			float footPointAngle = atan2(currentGear->getPosition().y-footPosition.y,currentGear->getPosition().x-footPosition.x);
			std::cout<<"main: " << mainPointAngle << " foot " << footPointAngle<<"\n";
		}
		
			
		
		/*
		float r = radius + (legPartFirst->width+legPartSecond->width)/3.0f;
		float xAdd = r*cos(rotationAngle);
		float yAdd = r*sin(rotationAngle);
		*/
		//footPosition.x 
		//std::cout<<"angle: " << legPartFirst->rotationAngle *(180/M_PI) << "\n";
		//legPartSecond->rotationAngle-=0.01f*delta;
	}

	/*
	if(glfwGetKey('J')==GLFW_PRESS)
		desiredPosition.x-=1.0f*delta;

	if(glfwGetKey('K')==GLFW_PRESS)
		desiredPosition.y+=1.0f*delta;

	if(glfwGetKey('L')==GLFW_PRESS)
		desiredPosition.x+=1.0f*delta;

	if(glfwGetKey('I')==GLFW_PRESS)
	{
		desiredPosition.y-=1.0f*delta;
	}

	if(glfwGetKey('G')==GLFW_PRESS)
	{
		goTo(desiredPosition,LEG_GOTO_WAY_LINEAR);
	}


	if(glfwGetKey('O')==GLFW_PRESS)
	{
		legPartFirst->rotationAngle=M_PI;
		footPosition= getRealFootPosition();
		desiredPosition=footPosition;
		
	}

	*/





	if(currentGear!=NULL)
			goTo(currentGear->getHillPositionFromIndex(currentGearHillIndex),LEG_GOTO_WAY_LINEAR);
	/*
	if(getExpansionPercent()>0.8&&isStanding)
	{
		
	
		if(this->legDirection==LEG_LEFT_DIR)
		{
			currentGearHillIndex++;
		}else
		{
			currentGearHillIndex--;
		}
		
		goTo(currentGear->getHillPositionFromIndex(currentGearHillIndex),LEG_GOTO_WAY_LINEAR);
	}*/

	/*if(getExpansionPercent()>0.8)
	{
	
		if(this->legDirection==LEG_LEFT_DIR)
		{
			currentGearHillIndex++;
		}
		else
		{
			currentGearHillIndex--;
		}
		goTo(currentGear->getHillPositionFromIndex(currentGearHillIndex),LEG_GOTO_WAY_LINEAR);
	}*/


}

glm::vec3 Leg::getRealFootPosition()
{
	
	glm::vec3 rcPoint = legPartSecond->getRealPosition();
	float r = legPartSecond->width;


	float angle = M_PI + legPartSecond->rotationAngle + legPartSecond->secondRotationAngle;
	float xAdd = r*cos(angle);
	float yAdd = r*sin(angle);
	
	return  glm::vec3(rcPoint.x+xAdd,rcPoint.y+yAdd,rotationCenterPoint.z);
	
	
	/*
	footPosition.x=rcPoint.x+xAdd;
	footPosition.y=rcPoint.y+yAdd;
	footPosition.z= rotationCenterPoint.z;
	*/
}

void Leg::reorganizeLegParts()
{
	debugPic->position.z=legPartSecond->position.z;
	realPosition=legPartFirst->getRealPosition();


	float distanceFootCenterRotation =float(glm::distance(footPosition,legPartFirst->getRealPosition()));
	if(distanceFootCenterRotation <legPartFirst->width+legPartSecond->width)
	{
			
		float legPartFirstLegthPow2 = pow( legPartFirst->width,2);
		float legPartSecondLegthPow2 = pow( legPartSecond->width,2);
		float distanceFootCenterRotationPow2 = pow( distanceFootCenterRotation,2);
		float triangleAlphaAngle =0;
		if(legDirection==LEG_RIGHT_DIR)
		{
			triangleAlphaAngle = -acos((legPartFirstLegthPow2+distanceFootCenterRotationPow2-legPartSecondLegthPow2)/(2.0f*distanceFootCenterRotation*legPartFirst->width));
		}
		else
		{
			triangleAlphaAngle = acos((legPartFirstLegthPow2+distanceFootCenterRotationPow2-legPartSecondLegthPow2)/(2.0f*distanceFootCenterRotation*legPartFirst->width));
		}
		float legPartFirstAngle = 

			atan2(footPosition.y-legPartFirst->getRealPosition().y,footPosition.x-legPartFirst->getRealPosition().x)
			-legPartFirst->secondRotationAngle
			+ M_PI
			+ triangleAlphaAngle
			;
		float legPartSecondAngle = 
			atan2(footPosition.y-legPartSecond->getRealPosition().y,footPosition.x-legPartSecond->getRealPosition().x)
			-legPartSecond->secondRotationAngle
			+ M_PI
			;

		
		legPartFirst->rotationAngle=legPartFirstAngle;
		legPartSecond->rotationAngle=legPartSecondAngle;


	}
	
	legPartFirst->position=rotationCenterPoint;
	legPartFirst->secondRotationRadius = radius;
	legPartFirst->secondRotationAngle= rotationAngle;
	legPartSecond->position = legPartFirst->getRealPosition();
	legPartSecond->secondRotationAngle = M_PI + (legPartFirst->rotationAngle + legPartFirst->secondRotationAngle);
	legPartSecond->secondRotationRadius = legPartFirst->width;
	//debugPic->position=footPosition;

;
	

}

bool Leg::goTo(glm::vec3 desiredFootPosition, int way)
{
	
	if(float(glm::distance(desiredFootPosition,legPartFirst->getRealPosition())) < (legPartFirst->width+legPartSecond->width))
	{
		this->desiredPosition = desiredFootPosition;
		this->desiredPositionWay= way;
		//isStanding=false;
		return true;
	}
	return false;
}

void Leg::moveTowardsDesiredPosition()
{
	float linearSpeed = 60.0f*delta;
	switch(desiredPositionWay)
	{
	case LEG_GOTO_WAY_LINEAR:
		

		if(footPosition.x<desiredPosition.x)
			footPosition.x+=linearSpeed;
		else
			footPosition.x-=linearSpeed;

		if(footPosition.y<desiredPosition.y)
			footPosition.y+=linearSpeed;
		else
			footPosition.y-=linearSpeed;

		if(footPosition.z<desiredPosition.z)
			footPosition.z+=linearSpeed;
		else
			footPosition.z-=linearSpeed;
		break;
	default:
		break;
	}
}

void Leg::checkCollisionWithDesiredPosition()
{
	if(desiredPositionWay!=LEG_GOTO_NOTHING)
	{
		if(float(glm::distance(desiredPosition,footPosition))<10.0f)
		{
			//desiredPositionWay=LEG_GOTO_NOTHING;
			footPosition=desiredPosition;
			isStanding=true;
		
			
		
		}
		else
		{
			
			isStanding=false;
		}
	}
	else
	{

	}

}
float Leg::getLength()
{
	return legPartFirst->width+legPartSecond->width;
}
glm::vec3 Leg::getRealPosition()
{
	return realPosition;
}

Gear* Leg::getGearStandingOn()
{
	return currentGear;
}

bool  Leg::checkCollisionWithGear(Gear* gearToTest)
{
	if(gearToTest==NULL) return false;
	int index = gearToTest->getClosestHillIndex(legPartFirst->getRealPosition());
	glm::vec3 hillPosition = gearToTest->getHillPositionFromIndex(index);

	
	if(goTo(hillPosition,LEG_GOTO_WAY_LINEAR))
	{
		currentGear=gearToTest;
		currentGearHillIndex=index;
		return true;
	}
	return false;
}


float Leg::getExpansionPercent()
{
	return glm::distance(footPosition,legPartFirst->getRealPosition())/(legPartFirst->width+legPartSecond->width);
}