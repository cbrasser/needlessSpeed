/**
$B_SHADER_VERSION
#ifdef GL_ES
precision highp float;
#endif
*/

#version 130

uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ProjectionMatrix;

attribute vec4 Position;
attribute vec4 TexCoord;

varying vec4 texCoordVarying;


void main()
{
    texCoordVarying = TexCoord;
    highp mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
    gl_Position = ProjectionMatrix * ModelViewMatrix * Position;
     
}