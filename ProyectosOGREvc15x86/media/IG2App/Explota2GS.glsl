#version 330 core 
layout (triangles) in; // procesa un triángulo: recibe 1 triángulo y
layout (triangle_strip, max_vertices = 3) out; // emite 1 triángulo

uniform mat4 modelViewMat; // View*Model matrix
uniform mat4 modelViewProjMat; // para pasar a Clip-Space
uniform mat4 normalMat; // = transpose(inverse(modelView))
uniform float tiempo;
uniform float tiempo2pi;
const float VD = 10; // longitud del desplazamiento
const float SF = 0.5; // factor de escala

in vec2 v_TexCoord[];
in vec3 v_Normal[];

out vec2 vUv0; 
out vec3 vViewNormal; // coordenadas de la normal en View space
out vec3 vViewVertex; // coordenadas del vértice en View space

vec3 baricentroVec(vec3 vertex[3]) {
    return (vertex[0] + vertex[1] + vertex[2]) / 3.0;
}

void main() {
    vec3 vertices[3] = vec3[]( gl_in[0].gl_Position.xyz,
    gl_in[1].gl_Position.xyz,
    gl_in[2].gl_Position.xyz );

    mat4 yawMatrix = mat4(vec4(cos(tiempo2pi), 0, -sin(tiempo2pi), 0),
                    vec4(0, 1, 0, 0),
                    vec4(sin(tiempo2pi), 0, cos(tiempo2pi), 0),
                    vec4(0, 0, 0, 1));
    vec3 baricentro = baricentroVec(vertices);
    vec3 dir = normalize(baricentro);
    for (int i=0; i<3; ++i) { // para emitir 3 vértices
        vec3 scaleDir = normalize(vertices[i] - baricentro);

        vec3 posDes = vertices[i] + (dir * VD * tiempo) + (scaleDir * SF * tiempo);
        // se aplica la matriz de rotacion
        vec4 vPosDes = vec4(posDes,1.0) * yawMatrix;
        // outs para el vertice
        vUv0 = v_TexCoord[i];
        vViewVertex = vec3(modelViewMat * vec4(vertices[i],0));
        vViewNormal = normalize(vec3(normalMat * vec4(v_Normal[i],0)));

        // vértice desplazado (los 3 en la misma dirección)
        gl_Position = modelViewProjMat * vPosDes;
        // paso a Clip-Space
        EmitVertex();
    }
EndPrimitive();
}