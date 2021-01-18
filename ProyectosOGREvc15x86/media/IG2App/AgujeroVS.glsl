#version 330 core
// datos de la malla: indicar cómo está estructurada
in vec4 vertex;// layout (location = 0) in vec4 vertex;
in vec3 normal;
in vec2 uv0;// layout (location = 2) in vec2 uv0;

uniform mat4 modelViewMat;// View*Model matrix
uniform mat4 modelViewProjMat;
uniform mat4 normalMat;// = transpose(inverse(modelView))

out vec2 vUv0;
out vec3 vViewNormal;
out vec3 vViewVertex;

void main()
{
    vUv0=uv0;
    vViewVertex=vec3(modelViewMat*vertex);
    vViewNormal=normalize(vec3(normalMat*vec4(normal,0)));
    gl_Position=modelViewProjMat*vertex;
}