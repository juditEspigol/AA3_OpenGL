#version 440 core

uniform vec2 windowSize;
uniform sampler2D textureSampler;

uniform vec3 sourceLight;

uniform vec3 frontCamera; 
uniform vec3 positionCamera; 

uniform vec3 colorA;
uniform vec3 colorB;
uniform float t; 

in vec2 uvsFragmentShader;
in vec4 normalsFragmentShader;
in vec4 primitivePosition;

out vec4 fragColor;

vec4 color;
vec3 ambientColor; 

void main() {
       
        vec2 adjustedTexCoord = vec2(uvsFragmentShader.x, 1.0 - uvsFragmentShader.y);
        vec4 baseColor = texture(textureSampler, adjustedTexCoord);  

        vec3 lineToLight = normalize(sourceLight - primitivePosition.xyz); 
        float sourceLightAngle = dot(lineToLight, normalsFragmentShader.xyz); 

        if(sourceLightAngle < 0.15)
            sourceLightAngle = 0.15; 

        float lightPower = 5; 

        float spotLight =  sourceLightAngle * lightPower; 

        float flashLight = 1; 

        ambientColor = mix(colorA, colorB, t); 

        color =  vec4((baseColor.rgb * ambientColor) * spotLight * flashLight, 1.0); 
        
        fragColor = color;

}