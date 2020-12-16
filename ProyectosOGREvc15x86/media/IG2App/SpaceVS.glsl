#version 330 core
// datos de la malla: indicar cómo está estructurada
in vec4 vertex; // layout (location = 0) in vec4 vertex;
in vec2 uv0; // layout (location = 2) in vec2 uv0;
in vec2 uv1; // layout (location = 2) in vec2 uv0;

uniform float ZF;
uniform float SinTiempo;
uniform mat4 modelViewProjMat;
out vec2 vUv0;
out vec2 vUv1;

void main()
{

    vUv0 = uv0;
    vUv1 = (uv0 -0.5) * (ZF +(0.5 + SinTiempo / 2)) + 0.5;
    gl_Position = modelViewProjMat * vertex;

}