#version 120

uniform mat4 projMatrix;
uniform mat4 scaleMatrix;
uniform mat4 translationMatrix;
uniform mat4 rotationMatrix;
uniform float zPosShadow;

attribute vec2 vertex;
attribute vec2 textureCoord;



varying vec2 fragTextureCoord;


void main(void)
{
    fragTextureCoord = textureCoord;
	vec4 newvertex = translationMatrix*rotationMatrix*scaleMatrix * vec4(vertex, 0.0, 1.0);
    gl_Position = projMatrix * newvertex;
}