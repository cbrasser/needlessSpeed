#version 130

uniform mediump mat4 ViewMatrix;
uniform mediump mat4 ModelMatrix;
uniform mediump mat4 ProjectionMatrix;

uniform mediump mat3 NormalMatrix;

uniform mediump vec4 EyePos;

uniform mediump float DayNightPulse;
uniform mediump vec3 LightDirection;
uniform mediump float TreeAnimation;

attribute vec4 Position;
attribute vec3 Normal;
attribute vec3 Tangent;
attribute vec4 TexCoord;

varying lowp vec4 diffuseVarying;
varying lowp vec4 texCoordVarying;

varying mediump vec4 posVarying;        // pos in world space
varying mediump vec3 normalVarying;     // normal in world space
varying mediump vec3 tangentVarying;    // tangent in world space

varying mediump float DayNightPulseVarying; // Value for the day and night cycle
varying mediump vec3 LightDirectionVarying; // Value for the direction light

void main()
{
    posVarying = ModelMatrix * Position;
    normalVarying = normalize(NormalMatrix * Normal);
    tangentVarying = normalize(NormalMatrix * Tangent);
    texCoordVarying = TexCoord * TreeAnimation;

    DayNightPulseVarying = DayNightPulse;
    LightDirectionVarying = LightDirection;
    
    
    gl_Position = ProjectionMatrix * ViewMatrix * posVarying;
}
