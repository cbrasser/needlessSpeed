#version 130

uniform mediump mat4 ViewMatrix;
uniform mediump mat4 ModelMatrix;
uniform mediump mat4 ProjectionMatrix;

uniform mediump mat3 NormalMatrix;

varying lowp vec4 texCoordVarying;

varying mediump vec4 posVarying;        // pos in world space
varying mediump vec3 normalVarying;     // normal in world space
varying mediump vec3 tangentVarying;    // tangent in world space

void main()
{         
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	//gl_FragColor = lightColor * modelTexture;
	//gl_FragColor = modelTexture;
}
