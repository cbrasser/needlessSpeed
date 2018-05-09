#version 300 es

#ifdef GL_ES
precision lowp float;
#endif

// The following uniforms must be passed to the shader through the code (AsteroidRenderer.cpp)
uniform lowp vec3 Ka;   // ambient material coefficient
uniform lowp vec3 Kd;   // diffuse material coefficient
uniform lowp vec3 Ks;   // specular material coefficient

uniform float Ns;   // specular material exponent (shininess)

uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;

uniform mediump vec3 ambientColor;  // the ambient color of the scene

// Incoming vertex position
in vec4 Position;

// Incoming normal of the vertex
in vec3 Normal;

// The 'flat' qualifier tells the shader to use the normal of the provoking vertex
// for the whole primitive instead of using interpolated normals
flat out mediump vec3 flatNormal;

// Thank to 'flat' the three light components computed at the provoking vertex are then used for the entire primitive
// The three light components are passed to the fragment shader
flat out vec4 ambientVarying;
flat out vec4 diffuseVarying;
flat out vec4 specularVarying;

// bRenderer uniforms
uniform vec4 lightPositionViewSpace_0;
uniform float lightIntensity_0;
uniform float lightAttenuation_0;
uniform float lightRadius_0;
uniform vec3 lightDiffuseColor_0;
uniform vec3 lightSpecularColor_0;
out vec3 lightVectorViewSpace_0;
out float intensityBasedOnDist_0;
uniform vec4 lightPositionViewSpace_1;
uniform float lightIntensity_1;
uniform float lightAttenuation_1;
uniform float lightRadius_1;
uniform vec3 lightDiffuseColor_1;
uniform vec3 lightSpecularColor_1;
out vec3 lightVectorViewSpace_1;
out float intensityBasedOnDist_1;
out vec3 normalVaryingViewSpace;
out vec3 surfaceToCameraViewSpace;

void main( void )
{
    
    vec4 pos = ModelViewMatrix * Position;  // vertex position in eye/camera coordinates (view space)
    
    float lightDistance = 0.0;
    flatNormal = mat3(ModelViewMatrix)*Normal;
    surfaceToCameraViewSpace = -pos.xyz;
    lightVectorViewSpace_0 = lightPositionViewSpace_0.xyz - pos.xyz;
    lightDistance = distance(pos, lightPositionViewSpace_0);
    intensityBasedOnDist_0 = 0.0;
    if (lightDistance <= lightRadius_0) {
        intensityBasedOnDist_0 = clamp(lightIntensity_0 / (lightAttenuation_0*lightDistance*lightDistance), 0.0, 1.0);
    }
    lightVectorViewSpace_1 = lightPositionViewSpace_1.xyz - pos.xyz;
    lightDistance = distance(pos, lightPositionViewSpace_1);
    intensityBasedOnDist_1 = 0.0;
    if (lightDistance <= lightRadius_1) {
        intensityBasedOnDist_1 = clamp(lightIntensity_1 / (lightAttenuation_1*lightDistance*lightDistance), 0.0, 1.0);
    }
    
    // Light computations
    
    vec4 ambient  = vec4(clamp(ambientColor*Ka, 0.0, 1.0), 0.0);
    vec4 diffuse = vec4(0.0,0.0,0.0,1.0);
    vec4 specular = vec4(0.0,0.0,0.0,0.0);
    float specularCoefficient = 0.0;
    
    vec3 surfaceToCamera = normalize(surfaceToCameraViewSpace);
    vec3 surfaceNormal = normalize(flatNormal);
    
    float intensity = 0.0;
    if (intensityBasedOnDist_0 > 0.0 && (intensity = max(dot(surfaceNormal, normalize(lightVectorViewSpace_0)), 0.0)) > 0.0)
    {
        intensity = clamp(intensity, 0.0, 1.0);
        diffuse += vec4(lightDiffuseColor_0 * (intensity * intensityBasedOnDist_0), 0.0);
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-normalize(lightVectorViewSpace_0), surfaceNormal))), Ns);
        specular += vec4(lightSpecularColor_0 * (specularCoefficient * intensity * intensityBasedOnDist_0), 0.0);
    }
    
    if (intensityBasedOnDist_1 > 0.0 && (intensity = max(dot(surfaceNormal, normalize(lightVectorViewSpace_1)), 0.0)) > 0.0)
    {
        intensity = clamp(intensity, 0.0, 1.0);
        diffuse += vec4(lightDiffuseColor_1 * (intensity * intensityBasedOnDist_1), 0.0);
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-normalize(lightVectorViewSpace_1), surfaceNormal))), Ns);
        specular += vec4(lightSpecularColor_1 * (specularCoefficient * intensity * intensityBasedOnDist_1), 0.0);
    }
    diffuse = diffuse * vec4(Kd,1.0);
    specular = specular  * vec4(Ks, 0.0);
    
    ambientVarying = ambient;
    diffuseVarying = diffuse;
    specularVarying = specular;
    
    gl_Position = ProjectionMatrix * pos;

}
