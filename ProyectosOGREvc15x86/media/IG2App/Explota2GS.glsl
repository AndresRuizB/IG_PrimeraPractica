#version 330 core// archivo ExplotaGS.glsl
layout(triangles)in;// procesa un triángulo: recibe 1 triángulo y
layout(triangle_strip,max_vertices=3)out;// emite 1 triángulo
// al no declarar ninguna variable in, estamos suponiendo que el VS no tiene out,
// los vértices no traen asociados atributos, solo las coordenadas
uniform mat4 modelViewProjMat;// para pasar a Clip-Space
uniform mat4 modelViewMat;
uniform mat4 normalMat;
const float VD=40;// longitud del desplazamiento
const float ScaleF=0.6;
uniform float tiempo;
uniform float tiempo2pi;

in vec2 v_TexCoord[];
in vec3 v_Normal[];

out vec2 vUv0;
out vec3 vViewNormal;
out vec3 vViewVertex;

vec3 vecBaricentro(vec3 vertex[3]){
    
    return normalize(vertex[0]+vertex[1]+vertex[2])/3.;
    
}

void main(){
    vec3 vertices[3]=vec3[](
        gl_in[0].gl_Position.xyz,
        gl_in[1].gl_Position.xyz,
    gl_in[2].gl_Position.xyz);
    
    mat4 yawMatrix=mat4(vec4(cos(tiempo2pi),0,-sin(tiempo2pi),0),
    vec4(0,1,0,0),
    vec4(sin(tiempo2pi),0,cos(tiempo2pi),0),
    vec4(0,0,0,1));

    vec3 barV=vecBaricentro(vertices);
    
    for(int i=0;i<3;++i){// para emitir 3 vértices
        vec3 scaleV=normalize(vertices[i]-barV);
        
        vec3 posDes=(vertices[i]*ScaleF*tiempo)+(barV*VD*tiempo);
        vec4 posDesV=vec4(posDes,1.)*yawMatrix;
        
        vUv0=v_TexCoord[i];
        vViewVertex=vec3(modelViewMat*vec4(vertices[i],0));
        vViewNormal=normalize(vec3(normalMat*vec4(v_Normal[i],0)));
        // vértice desplazado (los 3 en la misma dirección)
        gl_Position=modelViewProjMat*posDesV;
        // paso a Clip-Space
        EmitVertex();
    }
    EndPrimitive();
}