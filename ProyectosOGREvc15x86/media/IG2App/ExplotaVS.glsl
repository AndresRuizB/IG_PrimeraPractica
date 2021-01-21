#version 330 core
// datos de la malla: indicar cómo está estructurada
in vec4 vertex;// layout (location = 0) in vec4 vertex;
in vec2 uv0;
in vec3 normal;

out vec2 v_TexCoord;
out vec3 v_Normal;

void main()
{
    v_TexCoord=uv0;
    v_Normal=normal;
    gl_Position=vertex;
}