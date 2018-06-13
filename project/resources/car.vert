/**
$B_SHADER_VERSION
#ifdef GL_ES
precision highp float;
#endif
*/

#version 130

uniform highp mat4 ViewMatrix;
uniform highp mat4 ModelMatrix;
uniform highp mat4 ProjectionMatrix;

uniform highp mat3 NormalMatrix;

uniform highp vec4 LightPos;
uniform highp vec4 EyePos;

uniform highp float DayNightPulse;
uniform highp vec3 LightDirection;

attribute vec4 Position;
attribute vec3 Normal;
attribute vec3 Tangent;
attribute vec4 TexCoord;

varying highp vec4 diffuseVarying;
varying highp vec4 texCoordVarying;

varying highp vec4 fragPosLightSpace;
varying highp vec4 posVarying;        // pos in world space
varying highp vec3 normalVarying;     // normal in world space
varying highp vec3 tangentVarying;    // tangent in world space

varying highp float DayNightPulseVarying; // Value for the day and night cycle
varying highp vec3 LightDirectionVarying; // Value for the direction light

void main()
{
    posVarying = ModelMatrix * Position;
    normalVarying = normalize(NormalMatrix * Normal);
    tangentVarying = normalize(NormalMatrix * Tangent);
    texCoordVarying = TexCoord;
	fragPosLightSpace = ViewMatrix * Position;
    DayNightPulseVarying = DayNightPulse;
    LightDirectionVarying = LightDirection;
    
    gl_Position = ProjectionMatrix * ViewMatrix * posVarying;
}
