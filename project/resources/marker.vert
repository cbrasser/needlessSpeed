/**
$B_SHADER_VERSION
#ifdef GL_ES
precision highp float;
#endif
*/

#version 130

uniform mediump mat4 ViewMatrix;
uniform mediump mat4 ModelMatrix;
uniform mediump mat4 ProjectionMatrix;

uniform mediump vec4 EyePos;

attribute vec4 Position;
attribute vec3 Normal;
attribute vec3 Tangent;
attribute vec4 TexCoord;

varying lowp vec4 diffuseVarying;
varying lowp vec4 texCoordVarying;

varying mediump vec4 posVarying;        // pos in world space
varying mediump vec3 normalVarying;     // normal in world space
varying mediump vec3 tangentVarying;    // tangent in world space

void main()
{
    posVarying = ModelMatrix * Position;
    texCoordVarying = TexCoord;
    
    gl_Position = ProjectionMatrix * ViewMatrix * posVarying;
}
