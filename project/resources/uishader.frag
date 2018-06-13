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
    //float depthValue = texture(fbo_texture,texCoordVarying.xy).r;
    //gl_FragColor = vec4(vec3(depthValue), 1.0);
    //gl_FragColor = texture2D(fbo_texture, texCoordVarying.xy);

}
    
