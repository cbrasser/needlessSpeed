/**
$B_SHADER_VERSION
#ifdef GL_ES
precision highp float;
#endif
*/

#version 130
attribute vec4 Position;

uniform highp mat4 ViewMatrix;
uniform highp mat4 ModelMatrix;


void main()
{
    gl_Position = ViewMatrix * ModelMatrix * Position;
}  