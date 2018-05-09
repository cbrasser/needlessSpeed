#version 300 es

#ifdef GL_ES
precision lowp float;
#endif

//flat in vec3 flatNormal;

// Incoming light components, which were computed in the vertex shader
flat in vec4 ambientVarying;
flat in vec4 diffuseVarying;
flat in vec4 specularVarying;

// Outcoming color of the fragment
out vec4 fragmentColor;

void main( void )
{
    
    //    // Color each fragment with the color normal for debug purposes
    //    fragmentColor = vec4((normalize(flatNormal) + vec3(1.0, 1.0, 1.0)) / 2.0, 1.0);
    
    fragmentColor = clamp(ambientVarying+diffuseVarying+specularVarying, 0.0, 1.0);
    
}
