#version 330 core
// datos de la malla: indicar cómo está estructurada
in vec4 vertex;// layout (location = 0) in vec4 vertex;
in vec2 uv0;

out vec2 v_TexCoord;

void main()
{
    v_TexCoord=uv0;
    gl_Position=vertex;
}