#version 330 core // archivo ExplotaVS.glsl
in vec4 vertex;
in vec2 uv0; // coordenadas de textura 0

out vec2 v_TexCoord;

void main() {
    v_TexCoord = uv0; // se pasan las coordenadas de textura
    gl_Position = vertex; // El GS tiene que transformar las coordenadas de gl_Position al espacio de corte
}