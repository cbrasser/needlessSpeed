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
uniform sampler2D ColorLUT; // Lookup Texture
varying mediump float DayNightPulseVarying; // Value for the Day and Night Cycle

void main()
{
	lowp vec4 modelTexture = texture2D(DiffuseMapNew, texCoordVarying.xz);
	lowp float timeOfDay = clamp(DayNightPulseVarying, 0.05, 0.95); //limit with clamp, so there is not overflow when looking up the colors in the lut (avoids highlighting around the edges)
	lowp float intensity = 0.05;
	lowp vec4 lightColor = texture2D(ColorLUT, vec2(intensity, timeOfDay));

	//gl_FragColor = modelTexture;
	gl_FragColor = (lightColor * 2.0) * modelTexture;
    //gl_FragColor = texture2D(DiffuseMapNew, texCoordVarying.xz);
}