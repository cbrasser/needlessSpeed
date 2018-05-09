#version 130

// uniform mat4 ModelViewMatrix;
// uniform mat3 NormalMatrix;
// uniform mat4 ViewMatrix;
// uniform mat4 ProjectionMatrix;

// attribute vec4 Position;
// attribute vec3 Normal;
// attribute vec4 TexCoord;

// varying vec4 colorVarying;

uniform mediump mat4 ViewMatrix;
uniform mediump mat4 ModelMatrix;
uniform mediump mat4 ProjectionMatrix;

uniform mediump mat3 NormalMatrix;

uniform mediump vec4 LightPos;
uniform mediump vec4 EyePos;

uniform mediump float DayNightPulse;

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
    vec4 pos = ModelViewMatrix * Position;  // vertex position in eye coordinates
    vec3 normal = normalize(NormalMatrix * Normal.xyz);

    colorVarying = vec4(vec3(0.1) + normal * 0.5, 1.0);
    
    gl_Position = ProjectionMatrix * pos;
}
