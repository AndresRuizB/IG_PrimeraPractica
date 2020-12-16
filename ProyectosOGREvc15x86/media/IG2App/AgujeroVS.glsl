#version 330 core
// datos de la malla: indicar cómo está estructurada
in vec4 vertex; // layout (location = 0) in vec4 vertex;
in vec3 normal; 
in vec2 uv0; // layout (location = 2) in vec2 uv0;

uniform float ZF;
uniform mat4 modelViewMat; // View*Model matrix
uniform mat4 modelViewProjMat;
uniform mat4 normalMat; // = transpose(inverse(modelView))
out vec2 vUv0;
out vec2 vUv1;
out vec3 vFrontColor;
out vec3 vBackColor;

void main()
{
    vUv0 = uv0;
    vUv1 = uv0;
    gl_Position = modelViewProjMat * vertex;
    vFrontColor = (1.0,0.5,0.5,1.0);
    vBackColor = (0.5,0.5,1.0,1.0);
}