#version 330 core // archivo ExplotaGS.glsl
layout (triangles) in; // procesa un triángulo: recibe 1 triángulo y
layout (triangle_strip, max_vertices = 3) out; // emite 1 triángulo

uniform mat4 modelViewMat; // View*Model matrix
uniform mat4 modelViewProjMat; // para pasar a Clip-Space
uniform mat4 normalMat; // = transpose(inverse(modelView))
uniform float tiempo;
const float VD = 5; // longitud del desplazamiento

in vec2 v_TexCoord[];
in vec3 v_Normal[];

out vec2 vUv0; 
out vec3 vViewNormal; // coordenadas de la normal en View space
out vec3 vViewVertex; // coordenadas del vértice en View space

vec3 normalVec(vec3 vertex[3]) {
    return normalize(cross(vertex[0]-vertex[1],vertex[1]-vertex[2]));
} // vector normal al triángulo

void main() {
    vec3 vertices[3] = vec3[]( gl_in[0].gl_Position.xyz,
    gl_in[1].gl_Position.xyz,
    gl_in[2].gl_Position.xyz );
    vec3 dir = normalVec(vertices); // para los 3 vértices
    for (int i=0; i<3; ++i) { // para emitir 3 vértices
        vec3 posDes = vertices[i] + dir * VD * tiempo;
        // outs para el vertice
        vUv0 = v_TexCoord[i];
        vViewVertex = vec3(modelViewMat * vec4(vertices[i],0));
        vViewNormal = normalize(vec3(normalMat * vec4(v_Normal[i],0)));

        // vértice desplazado (los 3 en la misma dirección)
        gl_Position = modelViewProjMat * vec4(posDes,1.0);
        // paso a Clip-Space
        EmitVertex();
    }
EndPrimitive();
}