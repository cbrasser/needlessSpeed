#version 130


uniform highp mat4 ViewMatrix;
uniform highp mat4 ModelMatrix;
uniform highp mat4 ProjectionMatrix;

uniform highp mat3 NormalMatrix;

uniform highp vec4 LightPos;

varying highp float DayNightPulseVarying; // Value for the Day and Night Cycle
varying highp vec3 LightDirectionVarying; // Value for light direction

uniform sampler2D NormalMap;
uniform sampler2D DiffuseMap;
uniform sampler2D ColorLUT; // Lookup Texture

varying highp vec4 texCoordVarying;

varying highp vec4 posVarying;        // pos in world space
varying highp vec3 normalVarying;     // normal in world space
varying highp vec3 tangentVarying;    // tangent in world space

void main()
{ 
    highp vec4 pos = posVarying;
    highp vec3 n = normalize(normalVarying);   

    highp vec3 l = normalize(LightDirectionVarying);
    
    highp float intensity = dot(l, n);
    intensity = clamp(intensity, 0.05, 0.95); //limit with clamp, so there is not overflow when looking up the colors in the lut (avoids highlighting around the edges)
   
    highp vec4 modelTexture = texture2D(DiffuseMap, texCoordVarying.st);

    highp float timeOfDay = clamp(DayNightPulseVarying, 0.05, 0.95); //limit with clamp, so there is not overflow when looking up the colors in the lut (avoids highlighting around the edges)
    highp float strength = 1.0; // Can be use to adjust the global amount of lightColor
    highp vec4 lightColor = texture2D(ColorLUT, vec2(intensity, timeOfDay)) * vec4(strength, strength, strength, 1.0);

	//gl_FragColor = vec4(n, 1.0);
	gl_FragColor = lightColor * modelTexture;
	//gl_FragColor = modelTexture;
}
