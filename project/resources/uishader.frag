#version 130

uniform sampler2D fbo_texture;

varying vec4 texCoordVarying;

void main()
{
    gl_FragColor = texture2D(fbo_texture, texCoordVarying.xy);
}
    
