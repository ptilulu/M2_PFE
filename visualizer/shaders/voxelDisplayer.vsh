#version 130

attribute vec4 posAttr;
varying float height;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

void main() {
    vec4 pos = vec4(vec3(posAttr), 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * pos;
    height = posAttr.y;
}
