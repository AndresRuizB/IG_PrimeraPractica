#version 330 core

in vec2 vUv0;
uniform sampler2D RTT0; // textura con la escena
uniform float kernel[9];
out vec4 fFragColor;

void main() {
    ivec2 texSize = textureSize(RTT0, 0);
    float incS = 1. / float(texSize.s); // inc horizontal
    float incT = 1. / float(texSize.t); // inc vertical
    vec2 incUV[9] = vec2[] (
        vec2(-incS,incT),
        vec2(0,incT),
        vec2(incS,incT),
        vec2(-incS,0),
        vec2(0,0),
        vec2(incS,0),
        vec2(-incS,-incT),
        vec2(0,-incT),
        vec2(incS,-incT));

    vec3 color = vec3(0.0);

    for(int i = 0; i < 9; i++) {
        vec3 texelUV = vec3(texture(RTT0, vUv0 + incUV[i]));
        color +=  texelUV * kernel[i];
    }

    fFragColor = vec4(color, 1.0);

}