#version 330 core // archivo ExplotaVS.glsl
in vec4 vertex;
in vec2 uv0; // coordenadas de textura 0
in vec3 normal;

out vec2 v_TexCoord;
out vec3 v_Normal;

void main() {
    v_TexCoord = uv0; // se pasan las coordenadas de textura
    v_Normal = normal;
    gl_Position = vertex; 
}