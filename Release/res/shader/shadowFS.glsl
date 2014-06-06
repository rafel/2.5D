#version 120
#define MATH_E 2.718281828459045
varying vec2 fragTextureCoord;
uniform sampler2D textureWallpaper;
uniform vec2 blurSize;
uniform vec3 lightSize;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform float Zpos;

void main(void)
{
	if(lightPosition.x != 0 || lightPosition.y != 0){
		// World
		float WCX = float(1366.0f/1920.0f);
		float WCY = float(768.0f/1080.0f);
		float zRatio = (100.0f/(Zpos));

		// Distance
		vec4 currentPosition = vec4(gl_FragCoord.x,gl_FragCoord.y,Zpos,1.0);
		float distanceToLight = distance(vec4(lightPosition,1.0),currentPosition)/(zRatio*WCX);


		float intensity = distanceToLight - lightSize.y; // Pythagorean Theorem - size
		if(intensity < 0.0){
			intensity = 0.0;
		}
		else {
			intensity /= lightSize.x;    // Divide the intensity by the spread
		}
		vec4 light = vec4(1.0-intensity, 1.0-intensity, 1.0-intensity, 1.0);
		vec4 finalPixelColor = texture2D(textureWallpaper,fragTextureCoord);
		
		gl_FragColor =  light * finalPixelColor;
	}
	else {
		gl_FragColor = texture2D(textureWallpaper,fragTextureCoord);
	}  
	     
}