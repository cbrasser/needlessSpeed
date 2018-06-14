/**
$B_SHADER_VERSION
#ifdef GL_ES
precision highp float;
#endif
*/

#version 130

 uniform sampler2D fbo_texture;

 varying vec4 texCoordVarying;

void main() 
{
    //gl_FragColor = texture2D(fbo_texture, texCoordVarying.xy);
    gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}