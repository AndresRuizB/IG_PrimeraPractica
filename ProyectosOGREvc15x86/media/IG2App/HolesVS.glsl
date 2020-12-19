#version 330 core
in vec4 vertex; // atributos de los vértices a procesar
in vec3 normal;
in vec2 uv0; // coordenadas de textura 0

uniform mat4 modelViewMat; // View*Model matrix
uniform mat4 modelViewProjMat; // Projection*View*Model matrix
uniform mat4 normalMat; // = transpose(inverse(modelView))

out vec2 vUv0; // out del vertex shader
out vec3 vViewNormal; // coordenadas de la normal en View space
out vec3 vViewVertex; // coordenadas del vértice en View space

void main() {
vUv0 = uv0; // se pasan las coordenadas de textura
vViewVertex = vec3(modelViewMat * vertex);
vViewNormal = normalize(vec3(normalMat * vec4(normal,0)));
gl_Position = modelViewProjMat * vertex; //obligatorio
// (Clipping coordinates)
}