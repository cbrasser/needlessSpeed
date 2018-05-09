$B_SHADER_VERSION
#ifdef GL_ES
precision lowp float;
#endif

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
uniform mat4 ModelViewMatrix;
uniform mat4 ProjectionMatrix;
attribute vec4 Position;
attribute vec3 Normal;
attribute vec3 Tangent;
attribute vec3 Bitangent;
attribute vec4 TexCoord;
void main() {
vec4 posViewSpace = ModelViewMatrix*Position;
float lightDistance = 0.0;
normalVaryingViewSpace = mat3(ModelViewMatrix)*Normal;
surfaceToCameraViewSpace = -posViewSpace.xyz;
lightVectorViewSpace_0 = lightPositionViewSpace_0.xyz - posViewSpace.xyz;
lightDistance = distance(posViewSpace, lightPositionViewSpace_0);
intensityBasedOnDist_0 = 0.0;
if (lightDistance <= lightRadius_0) {
intensityBasedOnDist_0 = clamp(lightIntensity_0 / (lightAttenuation_0*lightDistance*lightDistance), 0.0, 1.0);
}
lightVectorViewSpace_1 = lightPositionViewSpace_1.xyz - posViewSpace.xyz;
lightDistance = distance(posViewSpace, lightPositionViewSpace_1);
intensityBasedOnDist_1 = 0.0;
if (lightDistance <= lightRadius_1) {
intensityBasedOnDist_1 = clamp(lightIntensity_1 / (lightAttenuation_1*lightDistance*lightDistance), 0.0, 1.0);
}
gl_Position = ProjectionMatrix*posViewSpace;
}