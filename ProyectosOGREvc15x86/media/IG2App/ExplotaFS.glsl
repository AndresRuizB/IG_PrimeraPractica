#version 330 core // archivo ExplotaFS.glsl
uniform sampler2D texturaL; // tipo sampler2D para texturas 2D
uniform sampler2D texturaM; // ‐> unidades de textura (int)
uniform float Flipping;

in vec2 vUv0; // out del vertex shader

out vec4 fFragColor;

void main() {
    vec3 colorL = vec3(texture(texturaL, vUv0)); // acceso a téxel
    vec3 colorM = vec3(texture(texturaM, vUv0)); // configuración!
    bool frontFacing = (Flipping > -1) ? gl_FrontFacing : !gl_FrontFacing;

    vec3 color;
   if (frontFacing){
    color = colorL;
    } else{
    color = colorM;
    }   

    fFragColor = vec4(color, 1.);
}