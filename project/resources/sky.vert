$B_SHADER_VERSION
#ifdef GL_ES
precision lowp float;
#endif

uniform mat4 ModelViewMatrix;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

attribute vec4 Position;

varying mediump vec4 pos;
varying vec4 texCoordVarying;

void main()
{
    pos = ModelMatrix * Position;  // vertex position in world coordinates
    
    // The texture coordinates must correspond to the coordinates in world coord, not to the ones in eye coord
    // Therefore ModelViewMatrix cannot be used in this shader
    texCoordVarying = pos;
    
    // This is just to remove a not found uniform warning
    vec4 tmp = ModelViewMatrix * Position;

    gl_Position = ProjectionMatrix * ViewMatrix * pos;
}