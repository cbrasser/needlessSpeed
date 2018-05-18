#version 130

uniform vec4 lightPositionViewSpace_0;
uniform float lightIntensity_0;
uniform float lightAttenuation_0;
uniform float lightRadius_0;
uniform vec3 lightDiffuseColor_0;
uniform vec3 lightSpecularColor_0;
varying vec3 lightVectorViewSpace_0;
varying float intensityBasedOnDist_0;
uniform vec4 lightPositionViewSpace_1;
uniform float lightIntensity_1;
uniform float lightAttenuation_1;
uniform float lightRadius_1;
uniform vec3 lightDiffuseColor_1;
uniform vec3 lightSpecularColor_1;
varying vec3 lightVectorViewSpace_1;
varying float intensityBasedOnDist_1;
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