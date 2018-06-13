/**
$B_SHADER_VERSION
#ifdef GL_ES
precision highp float;
#endif
*/

#version 130

varying vec3 normalVaryingViewSpace;
varying vec3 surfaceToCameraViewSpace;
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
attribute vec4 Position;
attribute vec3 Normal;
attribute vec3 Tangent;
attribute vec3 Bitangent;
attribute vec4 TexCoord;

uniform mediump float DayNightPulse;

varying vec4 texCoordVarying;
varying mediump float DayNightPulseVarying; // Value for the day and night cycle


void main()
{
    DayNightPulseVarying = DayNightPulse;

    texCoordVarying = Position - vec4(-0.5,0,-0.5,1);
    
    gl_Position = ProjectionMatrix * ModelViewMatrix * Position;
}