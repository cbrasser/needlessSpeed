/**
$B_SHADER_VERSION
#ifdef GL_ES
precision highp float;
#endif
*/

#version 130


varying vec3 normalVaryingViewSpace;
varying vec3 surfaceToCameraViewSpace;
uniform sampler2D NormalMap;
uniform sampler2D SpecularMap;
uniform vec3 ambientColor;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ns;

varying lowp vec4 texCoordVarying;
uniform sampler2D DiffuseMapNew;


void main()
{
	lowp vec4 modelTexture = texture2D(DiffuseMapNew, texCoordVarying.xz);
	
	gl_FragColor = modelTexture;
    //gl_FragColor = texture2D(DiffuseMapNew, texCoordVarying.xz);
}