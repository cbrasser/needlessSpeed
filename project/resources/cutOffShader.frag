$B_SHADER_VERSION
#ifdef GL_ES
precision lowp float;
#endif

uniform sampler2D fbo_texture;
uniform float thresHold;

varying vec4 texCoordVarying;

void main()
{

	vec4 col = texture2D(fbo_texture, texCoordVarying.st);
	float brightness = (0.2126 *col.x + 0.7152 * col.y + 0.0722 * col.z);

    if (col == vec4(1,0,0,1)) {
        gl_FragColor = vec4(col.x, col.y, col.z, 1.0);
        
    } else if (col == vec4(0.2,0.2,1,1)) {
        gl_FragColor = vec4(col.x, col.y, col.z, 1.0);
        
    } else if (brightness > thresHold) {
        gl_FragColor = vec4(col.x, col.y, col.z, 0.1);
    
    } else {
		gl_FragColor = vec4(0, 0, 0, 0);
    }
}
