$B_SHADER_VERSION
#ifdef GL_ES
precision lowp float;
#endif

uniform sampler2D fbo_original;
uniform sampler2D fbo_blurTexture;
uniform sampler2D lens_dirt;
uniform float dirtThresHold;

uniform float intensity;

varying vec4 texCoordVarying;

void main()
{

	vec4 col1 = texture2D(fbo_original, texCoordVarying.st);
	vec4 col2 = texture2D(fbo_blurTexture, texCoordVarying.st);
    vec4 col3 = texture2D(lens_dirt, texCoordVarying.st);
    
    vec4 col = col1 + (col2 * col2.w * col3 * 3.0) * intensity;
    
    gl_FragColor = vec4(col.x, col.y, col.z, 1);
    
}
