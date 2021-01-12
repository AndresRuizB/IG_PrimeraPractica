#version 330 core // archivo ExplotaFS.glsl
uniform sampler2D texturaL; // tipo sampler2D para texturas 2D
uniform sampler2D texturaM; // ‐> unidades de textura (int)
uniform float Flipping;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;

in vec2 vUv0; // out del vertex shader
in vec3 vViewNormal; // coordenadas de la normal en View space
in vec3 vViewVertex; // coordenadas del vértice en View space

out vec4 fFragColor;

float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = lightPosition.xyz; // directional light ?
    if (lightPosition.w == 1) // positional light ?
    lightDir = lightPosition.xyz - cVertex;
    return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {
    vec3 colorL = vec3(texture(texturaL, vUv0)); 
    vec3 colorM = vec3(texture(texturaM, vUv0)); 
    bool frontFacing = (Flipping > -1) ? gl_FrontFacing : !gl_FrontFacing;

    vec3 colorTexture;
    vec3 diffuse;
   if (frontFacing){
        colorTexture = colorL;
        diffuse = diff(vViewVertex, vViewNormal) * lightDiffuse;
    } else{
        colorTexture = colorM;
        diffuse = diff(vViewVertex, -vViewNormal) * lightDiffuse;
    }  
    vec3 color = colorTexture * (diffuse + lightAmbient);

    fFragColor = vec4(color, 1.);
}