#version 130

varying float height;
varying vec3 nor;

void main() {
    vec4 col;
    if(height > 7500/90.0f){
        col=vec4(230/255.0f, 200/255.0f, 230/255.0f, 1.0f);
    }else if(height > 6000/90.0f){
        col=vec4(215/255.0f, 162/255.0f, 214/255.0f, 1.0f);
    }else if(height > 4500/90.0f){
        col=vec4(186/255.0f, 109/255.0f, 170/255.0f, 1.0f);
    }else if(height > 3000/90.0f){
        col=vec4(157/255.0f,  56/255.0f, 125/255.0f, 1.0f);
    }else if(height > 2250/90.0f){
        col=vec4(203/255.0f,  95/255.0f,  62/255.0f, 1.0f);
    }else if(height > 1500/90.0f){
        col=vec4(249/255.0f, 134/255.0f,   0/255.0f, 1.0f);
    }else if(height > 1000/90.0f){
        col=vec4(249/255.0f, 168/255.0f,  14/255.0f, 1.0f);
    }else if(height > 600/90.0f){
        col=vec4(249/255.0f, 201/255.0f,  29/255.0f, 1.0f);
    }else if(height > 450/90.0f){
        col=vec4(246/255.0f, 219/255.0f,  30/255.0f, 1.0f);
    }else if(height > 300/90.0f){
        col=vec4(244/255.0f, 237/255.0f,  30/255.0f, 1.0f);
    }else if(height > 225/90.0f){
        col=vec4(213/255.0f, 230/255.0f,  53/255.0f, 1.0f);
    }else if(height > 150/90.0f){
        col=vec4(182/255.0f, 223/255.0f,  77/255.0f, 1.0f);
    }else if(height > 75/90.0f){
        col=vec4(124/255.0f, 208/255.0f,  68/255.0f, 1.0f);
    }else if(height > 12.0f/90.0f){
        col=vec4( 65/255.0f, 194/255.0f,  60/255.0f, 1.0f);
    }else {
        col=vec4( 12/255.0f,  35/255.0f, 255/255.0f, 1.0f);
    }

    vec3 light = normalize(vec3(0.0, 0.0, 10.0));
    vec3 nor3 = normalize(nor);
    float cosTheta = clamp( (dot(nor,light )), 0.3 , 1.0 );
    vec3 lightColor = vec3 (1.0, 1.0, 1.0);

    gl_FragColor = vec4(lightColor * cosTheta, 1.0f) * col;
}
