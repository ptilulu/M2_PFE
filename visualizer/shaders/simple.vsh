#version 130

attribute vec4 posAttr;
attribute vec3 norAttr;
varying float height;
varying vec3 nor;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform highp mat3 norMatrix;
uniform float size;

void main() {
    vec4 pos = vec4(vec3(posAttr) * size, 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * pos;
    height=posAttr.y;
    nor = norMatrix * norAttr;
}
