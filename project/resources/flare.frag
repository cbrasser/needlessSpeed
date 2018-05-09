$B_SHADER_VERSION
#ifdef GL_ES
precision highp float;
#endif

//Was trying to fix the warning
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
uniform sampler2D NormalMap;
uniform sampler2D SpecularMap;
uniform vec3 ambientColor;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform float Ns;



uniform sampler2D DiffuseMap1;
uniform sampler2D DiffuseMap2;	
uniform sampler2D DiffuseMap3;	
uniform sampler2D DiffuseMap4;	
uniform sampler2D DiffuseMap5;	
uniform sampler2D DiffuseMap6;
uniform sampler2D DiffuseMap7;	


uniform float textureToUse;

varying lowp vec4 texCoordVarying;
varying float transparency;


void main()
{
	vec4 color = vec4(1,0,0,1);
    
	if (textureToUse == 1.0){
		color = texture2D(DiffuseMap1, texCoordVarying.xz);	
	}
	else if (textureToUse == 2.0){
		color = texture2D(DiffuseMap2, texCoordVarying.xz);
	}
	else if (textureToUse == 3.0){
		color = texture2D(DiffuseMap3, texCoordVarying.zy);
	}
	else if (textureToUse == 4.0){
		color = texture2D(DiffuseMap4, texCoordVarying.zx);
	}
	else if (textureToUse == 5.0){
		color = texture2D(DiffuseMap5, texCoordVarying.xz);
	}
	else if (textureToUse == 6.0){
		color = texture2D(DiffuseMap6, texCoordVarying.xz);
	}
    else if (textureToUse == 7.0){
		color = texture2D(DiffuseMap7, texCoordVarying.yx);
	}
	
	color.x *= transparency;
	color.y *= transparency;
	color.z *= transparency;
		
	gl_FragColor = color;

}
