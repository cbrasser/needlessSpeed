
uniform mediump mat4 ViewMatrix;
uniform mediump mat4 ModelMatrix;
uniform mediump mat4 ProjectionMatrix;

uniform mediump mat3 NormalMatrix;

uniform mediump vec4 LightPos;

varying mediump float DayNightPulseVarying; // Value for the Day and Night Cycle
varying mediump vec3 LightDirectionVarying; // Value for light direction

uniform sampler2D NormalMap;
uniform sampler2D DiffuseMap;
uniform sampler2D ColorLUT; // Lookup Texture

varying lowp vec4 texCoordVarying;

varying mediump vec4 posVarying;        // pos in world space
varying mediump vec3 normalVarying;     // normal in world space
varying mediump vec3 tangentVarying;    // tangent in world space

void main()
{ 
    mediump vec4 pos = posVarying;
    mediump vec3 n = normalize(normalVarying);   

    mediump vec3 l = normalize(LightDirectionVarying);
    
    lowp float intensity = dot(l, n);
    intensity = clamp(intensity, 0.05, 0.95); //limit with clamp, so there is not overflow when looking up the colors in the lut (avoids highlighting around the edges)
   
    lowp vec4 modelTexture = texture2D(DiffuseMap, texCoordVarying.st);

    lowp float timeOfDay = clamp(DayNightPulseVarying, 0.05, 0.95); //limit with clamp, so there is not overflow when looking up the colors in the lut (avoids highlighting around the edges)
    lowp float strength = 1.0; // Can be use to adjust the global amount of lightColor
    lowp vec4 lightColor = texture2D(ColorLUT, vec2(intensity, timeOfDay)) * vec4(strength, strength, strength, 1.0);

	//gl_FragColor = vec4(n, 1.0);
	gl_FragColor = lightColor * modelTexture;
	//gl_FragColor = modelTexture;
}
