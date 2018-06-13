#version 130

uniform mat4 LightViewMatrix;
uniform mat4 ModelMatrix;
uniform mat4 LightProjectionMatrix;

attribute vec4 Position;
attribute vec4 TexCoord;

varying vec4 texCoordVarying;


void main()
{
    texCoordVarying = TexCoord;
    mat4 lightSpaceMatrix  = LightProjectionMatrix * LightViewMatrix;
    //highp mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
    //gl_Position = ProjectionMatrix * ModelViewMatrix * Position;
    gl_Position =  lightSpaceMatrix* model * Position;
     
}