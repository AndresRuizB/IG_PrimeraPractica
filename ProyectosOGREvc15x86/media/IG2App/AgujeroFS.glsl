#version 330 core

uniform sampler2D texturaL; // tipo sampler2D para texturas 2D
uniform sampler2D texturaM; // ‐> unidades de textura (int)

uniform vec4 InColor;
uniform vec4 OutColor;
uniform float Flipping;
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;

in vec2 vUv0; // out del vertex shader
in vec3 vViewNormal;
in vec3 vViewVertex;

out vec4 fFragColor; // out del fragment shader

float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = lightPosition.xyz;
    if(lightPosition.w == 1) lightDir = lightPosition.xyz - cVertex;
    return max(dot(cNormal, normalize(lightDir)), 0.0);

}


void main() {
    vec3 colorL = vec3(texture(texturaL, vUv0)); // acceso a téxel
    vec3 colorM = vec3(texture(texturaM, vUv0)); // configuración!
    vec3 color;
    vec3 diffuse;

    if(colorM.r > 0.5) discard;

    bool frontFacing = (Flipping > -1) ? gl_FrontFacing : !gl_FrontFacing;

    if(true){
        color = colorL;
        diffuse = diff(vViewVertex, vViewNormal) * lightDiffuse * vec3(OutColor);
        color = diffuse * color;
    }
    else {
        color = vec3(InColor);
        diffuse = diff(vViewVertex, -vViewNormal) * lightDiffuse * vec3(InColor);
        color = diffuse * color;

    }

    fFragColor = vec4(color, 1.0);

}