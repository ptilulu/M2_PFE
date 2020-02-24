#include "mytruc.h"

mytruc::mytruc(){
    this->width=1;
    this->height=1;

    this->displayMode=1;
    this->size=1.0f;
    this->type=2;
}

void mytruc::setAltitudes(std::vector<float> altitudes, uint width, uint height){
    this->altitudes=altitudes;
    this->width=width;
    this->height=height;
}

void mytruc::setShaderProgram(char * pathAndName){
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,   QString(pathAndName) + ".vsh");
    shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, QString(pathAndName) + ".fsh");
    if (! shaderProgram.link()) {                  // édition de lien des shaders dans le shader program
        qWarning("Failed to compile and link shader program:");
        qWarning() << shaderProgram.log();
    }
}

void mytruc::initializeGL(){
    setShaderProgram(":/shaders/simple");
}


void mytruc::makeGLObject(){
    float altitude5,x=-(width/2.0f) + 1,z=-(height/2.0f) + 1;
    QVector3D color1(1,0,0),color2(0,1,0),color3(0,0,1),color4(0.2f,0,1),color5(0,0,0);
    QVector3D pt1,pt2,pt3,pt4,pt5;
    QVector3D nr1,nr2;
    QVector<GLfloat> vertData;
    for(uint l=0;l<height-1;l++){
        for(uint w=0;w<width-1;w++){
            switch (type) {
            case 1:
                pt1=QVector3D(x-0.5f,altitudes[(l+0)*width+(w+0)],z-0.5f);
                pt2=QVector3D(x+0.5f,altitudes[(l+0)*width+(w+1)],z-0.5f);
                pt3=QVector3D(x-0.5f,altitudes[(l+1)*width+(w+0)],z+0.5f);
                pt4=QVector3D(x+0.5f,altitudes[(l+1)*width+(w+1)],z+0.5f);
                altitude5=(altitudes[l*width+w]+altitudes[l*width+(w+1)]+altitudes[(l+1)*width+w]+altitudes[(l+1)*width+(w+1)])/4;
                pt5=QVector3D(x,altitude5,z);

                vertData.append(x-0.5f);vertData.append(altitudes[(l+0)*width+(w+0)]);vertData.append(z-0.5f);
                vertData.append(x+0.5f);vertData.append(altitudes[(l+0)*width+(w+1)]);vertData.append(z-0.5f);
                vertData.append(x);vertData.append(altitude5);vertData.append(z);

                vertData.append(x+0.5f);vertData.append(altitudes[(l+0)*width+(w+1)]);vertData.append(z-0.5f);
                vertData.append(x+0.5f);vertData.append(altitudes[(l+1)*width+(w+1)]);vertData.append(z+0.5f);
                vertData.append(x);vertData.append(altitude5);vertData.append(z);

                vertData.append(x+0.5f);vertData.append(altitudes[(l+1)*width+(w+1)]);vertData.append(z+0.5f);
                vertData.append(x-0.5f);vertData.append(altitudes[(l+1)*width+(w+0)]);vertData.append(z+0.5f);
                vertData.append(x);vertData.append(altitude5);vertData.append(z);

                vertData.append(x-0.5f);vertData.append(altitudes[(l+1)*width+(w+0)]);vertData.append(z+0.5f);
                vertData.append(x-0.5f);vertData.append(altitudes[(l+0)*width+(w+0)]);vertData.append(z-0.5f);
                vertData.append(x);vertData.append(altitude5);vertData.append(z);

                vertData.append(x-0.5f);vertData.append(altitudes[(l+0)*width+(w+0)]);vertData.append(z-0.5f);
                vertData.append(x+0.5f);vertData.append(altitudes[(l+0)*width+(w+1)]);vertData.append(z-0.5f);
                vertData.append(x+0.5f);vertData.append(altitudes[(l+1)*width+(w+1)]);vertData.append(z+0.5f);
                vertData.append(x-0.5f);vertData.append(altitudes[(l+1)*width+(w+0)]);vertData.append(z+0.5f);
                vertData.append(x-0.5f);vertData.append(altitudes[(l+0)*width+(w+0)]);vertData.append(z-0.5f);
                vertData.append(x+0.5f);vertData.append(altitudes[(l+1)*width+(w+1)]);vertData.append(z+0.5f);
                vertData.append(x+0.5f);vertData.append(altitudes[(l+0)*width+(w+1)]);vertData.append(z-0.5f);
                vertData.append(x-0.5f);vertData.append(altitudes[(l+1)*width+(w+0)]);vertData.append(z+0.5f);
            break;
            case 2:
                pt1=QVector3D(x-0.5f,altitudes[(l+0)*width+(w+0)],z-0.5f);
                pt2=QVector3D(x+0.5f,altitudes[(l+0)*width+(w+1)],z-0.5f);
                pt3=QVector3D(x-0.5f,altitudes[(l+1)*width+(w+0)],z+0.5f);
                pt4=QVector3D(x+0.5f,altitudes[(l+1)*width+(w+1)],z+0.5f);

                nr1=QVector3D::normal(pt1-pt2,pt3-pt2);
                nr2=QVector3D::normal(pt3-pt2,pt4-pt2);

                vertData.append(pt1.x());vertData.append(pt1.y());vertData.append(pt1.z());
                vertData.append(nr1.x());vertData.append(nr1.y());vertData.append(nr1.z());
                vertData.append(pt2.x());vertData.append(pt2.y());vertData.append(pt2.z());
                vertData.append(nr1.x());vertData.append(nr1.y());vertData.append(nr1.z());
                vertData.append(pt3.x());vertData.append(pt3.y());vertData.append(pt3.z());
                vertData.append(nr1.x());vertData.append(nr1.y());vertData.append(nr1.z());

                vertData.append(pt2.x());vertData.append(pt2.y());vertData.append(pt2.z());
                vertData.append(nr2.x());vertData.append(nr2.y());vertData.append(nr2.z());
                vertData.append(pt3.x());vertData.append(pt3.y());vertData.append(pt3.z());
                vertData.append(nr2.x());vertData.append(nr2.y());vertData.append(nr2.z());
                vertData.append(pt4.x());vertData.append(pt4.y());vertData.append(pt4.z());
                vertData.append(nr2.x());vertData.append(nr2.y());vertData.append(nr2.z());
            break;
            }
            x++;
        }
        x=-(width/2.0f) + 1;
        z++;
    }

    vbo.create();
    vbo.bind();
    vbo.allocate(vertData.constData(), vertData.count() * int(sizeof(GLfloat)));
}

void mytruc::display(QMatrix4x4 &projectionMatrix,QMatrix4x4 &viewMatrix){
    vbo.bind();
    shaderProgram.bind(); // active le shader program
    QMatrix3x3 normal_mat = viewMatrix.normalMatrix();

    shaderProgram.setUniformValue("projectionMatrix", projectionMatrix);
    shaderProgram.setUniformValue("viewMatrix", viewMatrix);
    shaderProgram.setUniformValue("norMatrix", normal_mat);
    shaderProgram.setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    shaderProgram.setAttributeBuffer("norAttr", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
    shaderProgram.enableAttributeArray("posAttr");
    shaderProgram.enableAttributeArray("norAttr");

    for(int i=0; i < static_cast<int>((width-1)*(height-1)) ;i++){
        modelMatrix.setToIdentity();
        modelMatrix.translate(position);
        modelMatrix.rotate(rotation.x(),1,0,0);
        modelMatrix.rotate(rotation.y(),0,1,0);
        modelMatrix.rotate(rotation.z(),0,0,1);
        shaderProgram.setUniformValue("size",size);
        shaderProgram.setUniformValue("modelMatrix", modelMatrix);

        switch (type) {
        case 1:
            switch (displayMode) {
            case 0 :
            //pas d'affichage
            break;
            case 1 :
            //affichage avec des faces triangle/quad
                for(int j=0;j<4;j++){
                    glDrawArrays(GL_TRIANGLES, 20*i+j*3,3);
                }
            break;
            case 2 :
            //affichage en maille
                glLineWidth(3);
                for(int j=0;j<4;j++){
                        glDrawArrays(GL_LINES, 20*i+j*3+0,2);
                        glDrawArrays(GL_LINES, 20*i+j*3+1,2);
                }
            break;
            case 3 :
            //affichage en sommet
                glPointSize(4);
                glDrawArrays(GL_POINTS, 20*i, 3*4);
            break;
            case 4 :
            //affichage avec des faces triangle/quad
                for(int j=0;j<4;j++){
                    glDrawArrays(GL_TRIANGLES, 20*i+j*3,3);
                }
                glLineWidth(3);
                for(int j=0;j<7;j++){
                    glDrawArrays(GL_LINES, 20*i+4*3+j,2);
                }
            break;
            default:;
            }
        break;
        case 2:
            switch (displayMode) {
            case 0 :
            //pas d'affichage
            break;
            case 1 :
            //affichage avec des faces triangle/quad
                glDrawArrays(GL_TRIANGLES, 6*i,6);
            break;
            case 2 :
            //affichage en maille
                glLineWidth(3);
                glDrawArrays(GL_LINES, 6*i+0,6);
                glDrawArrays(GL_LINES, 6*i+1,4);
            break;
            case 3 :
            //affichage en sommet
                glPointSize(4);
                glDrawArrays(GL_POINTS, 6*i, 6);
            break;
            default:;
            }
        break;
        }
    }

    shaderProgram.disableAttributeArray("in_position");
    shaderProgram.disableAttributeArray("colAttr");
    shaderProgram.release();
}
