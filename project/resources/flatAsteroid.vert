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

uniform vec4 lightPositionViewSpace_2;
uniform float lightIntensity_2;
uniform float lightAttenuation_2;
uniform float lightRadius_2;
uniform vec3 lightDiffuseColor_2;
uniform vec3 lightSpecularColor_2;
out vec3 lightVectorViewSpace_2;
out float intensityBasedOnDist_2;

uniform vec4 lightPositionViewSpace_3;
uniform float lightIntensity_3;
uniform float lightAttenuation_3;
uniform float lightRadius_3;
uniform vec3 lightDiffuseColor_3;
uniform vec3 lightSpecularColor_3;
out vec3 lightVectorViewSpace_3;
out float intensityBasedOnDist_3;

uniform vec4 lightPositionViewSpace_4;
uniform float lightIntensity_4;
uniform float lightAttenuation_4;
uniform float lightRadius_4;
uniform vec3 lightDiffuseColor_4;
uniform vec3 lightSpecularColor_4;
out vec3 lightVectorViewSpace_4;
out float intensityBasedOnDist_4;

uniform vec4 lightPositionViewSpace_5;
uniform float lightIntensity_5;
uniform float lightAttenuation_5;
uniform float lightRadius_5;
uniform vec3 lightDiffuseColor_5;
uniform vec3 lightSpecularColor_5;
out vec3 lightVectorViewSpace_5;
out float intensityBasedOnDist_5;

uniform vec4 lightPositionViewSpace_6;
uniform float lightIntensity_6;
uniform float lightAttenuation_6;
uniform float lightRadius_6;
uniform vec3 lightDiffuseColor_6;
uniform vec3 lightSpecularColor_6;
out vec3 lightVectorViewSpace_6;
out float intensityBasedOnDist_6;

uniform vec4 lightPositionViewSpace_7;
uniform float lightIntensity_7;
uniform float lightAttenuation_7;
uniform float lightRadius_7;
uniform vec3 lightDiffuseColor_7;
uniform vec3 lightSpecularColor_7;
out vec3 lightVectorViewSpace_7;
out float intensityBasedOnDist_7;

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
    
    lightVectorViewSpace_2 = lightPositionViewSpace_2.xyz - pos.xyz;
    lightDistance = distance(pos, lightPositionViewSpace_2);
    intensityBasedOnDist_2 = 0.0;
    if (lightDistance <= lightRadius_2) {
        intensityBasedOnDist_2 = clamp(lightIntensity_2 / (lightAttenuation_2*lightDistance*lightDistance), 0.0, 1.0);
    }
    
    lightVectorViewSpace_3 = lightPositionViewSpace_3.xyz - pos.xyz;
    lightDistance = distance(pos, lightPositionViewSpace_3);
    intensityBasedOnDist_3 = 0.0;
    if (lightDistance <= lightRadius_3) {
        intensityBasedOnDist_3 = clamp(lightIntensity_3 / (lightAttenuation_3*lightDistance*lightDistance), 0.0, 1.0);
    }
    
    lightVectorViewSpace_4 = lightPositionViewSpace_4.xyz - pos.xyz;
    lightDistance = distance(pos, lightPositionViewSpace_4);
    intensityBasedOnDist_4 = 0.0;
    if (lightDistance <= lightRadius_4) {
        intensityBasedOnDist_4 = clamp(lightIntensity_4 / (lightAttenuation_4*lightDistance*lightDistance), 0.0, 1.0);
    }
    
    lightVectorViewSpace_5 = lightPositionViewSpace_5.xyz - pos.xyz;
    lightDistance = distance(pos, lightPositionViewSpace_5);
    intensityBasedOnDist_5 = 0.0;
    if (lightDistance <= lightRadius_5) {
        intensityBasedOnDist_5 = clamp(lightIntensity_5 / (lightAttenuation_5*lightDistance*lightDistance), 0.0, 1.0);
    }
    
    lightVectorViewSpace_6 = lightPositionViewSpace_6.xyz - pos.xyz;
    lightDistance = distance(pos, lightPositionViewSpace_6);
    intensityBasedOnDist_6 = 0.0;
    if (lightDistance <= lightRadius_6) {
        intensityBasedOnDist_6 = clamp(lightIntensity_6 / (lightAttenuation_6*lightDistance*lightDistance), 0.0, 1.0);
    }
    
    lightVectorViewSpace_7 = lightPositionViewSpace_7.xyz - pos.xyz;
    lightDistance = distance(pos, lightPositionViewSpace_7);
    intensityBasedOnDist_7 = 0.0;
    if (lightDistance <= lightRadius_7) {
        intensityBasedOnDist_7 = clamp(lightIntensity_7 / (lightAttenuation_7*lightDistance*lightDistance), 0.0, 1.0);
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
    
    if (intensityBasedOnDist_2 > 0.0 && (intensity = max(dot(surfaceNormal, normalize(lightVectorViewSpace_2)), 0.0)) > 0.0)
    {
        intensity = clamp(intensity, 0.0, 1.0);
        diffuse += vec4(lightDiffuseColor_2 * (intensity * intensityBasedOnDist_2), 0.0);
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-normalize(lightVectorViewSpace_2), surfaceNormal))), Ns);
        specular += vec4(lightSpecularColor_2 * (specularCoefficient * intensity * intensityBasedOnDist_2), 0.0);
    }
    
    if (intensityBasedOnDist_3 > 0.0 && (intensity = max(dot(surfaceNormal, normalize(lightVectorViewSpace_3)), 0.0)) > 0.0)
    {
        intensity = clamp(intensity, 0.0, 1.0);
        diffuse += vec4(lightDiffuseColor_3 * (intensity * intensityBasedOnDist_3), 0.0);
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-normalize(lightVectorViewSpace_3), surfaceNormal))), Ns);
        specular += vec4(lightSpecularColor_3 * (specularCoefficient * intensity * intensityBasedOnDist_3), 0.0);
    }
    
    if (intensityBasedOnDist_4 > 0.0 && (intensity = max(dot(surfaceNormal, normalize(lightVectorViewSpace_4)), 0.0)) > 0.0)
    {
        intensity = clamp(intensity, 0.0, 1.0);
        diffuse += vec4(lightDiffuseColor_4 * (intensity * intensityBasedOnDist_4), 0.0);
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-normalize(lightVectorViewSpace_4), surfaceNormal))), Ns);
        specular += vec4(lightSpecularColor_4 * (specularCoefficient * intensity * intensityBasedOnDist_4), 0.0);
    }
    
    if (intensityBasedOnDist_5 > 0.0 && (intensity = max(dot(surfaceNormal, normalize(lightVectorViewSpace_5)), 0.0)) > 0.0)
    {
        intensity = clamp(intensity, 0.0, 1.0);
        diffuse += vec4(lightDiffuseColor_5 * (intensity * intensityBasedOnDist_5), 0.0);
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-normalize(lightVectorViewSpace_5), surfaceNormal))), Ns);
        specular += vec4(lightSpecularColor_5 * (specularCoefficient * intensity * intensityBasedOnDist_5), 0.0);
    }
    
    if (intensityBasedOnDist_6 > 0.0 && (intensity = max(dot(surfaceNormal, normalize(lightVectorViewSpace_6)), 0.0)) > 0.0)
    {
        intensity = clamp(intensity, 0.0, 1.0);
        diffuse += vec4(lightDiffuseColor_6 * (intensity * intensityBasedOnDist_6), 0.0);
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-normalize(lightVectorViewSpace_6), surfaceNormal))), Ns);
        specular += vec4(lightSpecularColor_6 * (specularCoefficient * intensity * intensityBasedOnDist_6), 0.0);
    }
    
    if (intensityBasedOnDist_7 > 0.0 && (intensity = max(dot(surfaceNormal, normalize(lightVectorViewSpace_7)), 0.0)) > 0.0)
    {
        intensity = clamp(intensity, 0.0, 1.0);
        diffuse += vec4(lightDiffuseColor_7 * (intensity * intensityBasedOnDist_7), 0.0);
        specularCoefficient = pow(max(0.0, dot(surfaceToCamera, reflect(-normalize(lightVectorViewSpace_7), surfaceNormal))), Ns);
        specular += vec4(lightSpecularColor_7 * (specularCoefficient * intensity * intensityBasedOnDist_7), 0.0);
    }
    
    diffuse = diffuse * vec4(Kd,1.0);
    specular = specular  * vec4(Ks, 0.0);
    ambientVarying = ambient;
    diffuseVarying = diffuse;
    specularVarying = specular;
    gl_Position = ProjectionMatrix * pos;
    
}
