attribute vec4 in_position;
varying vec3 col;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform float size;

void main() {
    vec4 pos = vec4(vec3(in_position) * size, 1.0);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * pos;
    if(in_position.y > 191){
        col=vec3(255/255.0f, 255/255.0f, 255/255.0f);
    }else if(in_position.y > 127){
        col=vec3(153/255.0f, 100/255.0f, 043/255.0f);
    }else if(in_position.y > 63){
        col=vec3(244/255.0f, 189/255.0f, 69/255.0f);
    }else if(in_position.y > 31){
        col=vec3(244/255.0f, 240/255.0f, 113/255.0f);
    }else if(in_position.y > 1){
        col=vec3(051/255.0f, 204/255.0f, 000/255.0f);
    }else {
        col=vec3(000/255.0f, 040/255.0f, 255/255.0f);
    }

}
