#version 130

varying float height;
varying vec3 nor;

void main() {
    vec4 col;
    if(height > 191) {
        col = vec4(255/255.0f, 255/255.0f, 255/255.0f, 1.0f);
    } else if(height > 127) {
        col = vec4(153/255.0f, 100/255.0f, 43/255.0f, 1.0f);
    } else if(height > 63) {
        col = vec4(244/255.0f, 189/255.0f, 69/255.0f, 1.0f);
    } else if(height > 31) {
        col = vec4(244/255.0f, 240/255.0f, 113/255.0f, 1.0f);
    } else if(height > 0) {
        col = vec4(51/255.0f, 204/255.0f, 0/255.0f, 1.0f);
    } else {
        col = vec4(0/255.0f, 40/255.0f, 255/255.0f, 1.0f);
    }

    vec3 light = normalize(vec3(0.0, 0.0, 10.0));
    vec3 nor3 = normalize(nor);
    float cosTheta = clamp((dot(nor,light )), 0.3, 1.0);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    gl_FragColor = vec4(lightColor * cosTheta, 1.0f) * col;
}
