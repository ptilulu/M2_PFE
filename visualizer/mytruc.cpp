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
    if(width <2 || height < 2){
        return;
    }
    float x=-(width/2.0f) + 0.5f,z=-(height/2.0f) + 0.5f;
    QVector<GLfloat> vertData;
    std::vector<QVector3D> vertPos,vertNorm;
    for(uint h=0;h<height;h++){
        for(uint w=0;w<width;w++){
            vertPos.push_back(QVector3D(x,altitudes[h*width+w],z));
            x++;
        }
        x=-(width/2.0f) + 0.5f;
        z++;
    }

    QVector3D pt1,pt2,pt3,pt4,pt5,nor;
    for(uint h=0;h<height;h++){
        for(uint w=0;w<width;w++){
            if(w==0){       pt1=vertPos[h*width+w];}else{pt1=vertPos[h*width+(w-1)];}
            if(h==0){       pt2=vertPos[h*width+w];}else{pt2=vertPos[(h-1)*width+w];}
            if(w==width -1){pt3=vertPos[h*width+w];}else{pt3=vertPos[h*width+(w+1)];}
            if(h==height-1){pt4=vertPos[h*width+w];}else{pt4=vertPos[(h+1)*width+w];}
            vertNorm.push_back(QVector3D::normal(pt4-pt2,pt3-pt1));
        }
    }
    uint id;
    if(type==1){
        for(uint h=0;h<height-1;h++){
            for(uint w=0;w<width-1;w++){
                id=(h+0)*width+(w+0);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                id=(h+0)*width+(w+1);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                id=(h+1)*width+(w+0);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());

                id=(h+0)*width+(w+1);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                id=(h+1)*width+(w+0);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                id=(h+1)*width+(w+1);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
            }
        }
    }
    if(type==2){
        for(uint h=0;h<height-1;h++){
            for(uint w=0;w<width-1;w++){
                pt1=vertPos[(h+0)*width+(w+0)];
                pt2=vertPos[(h+0)*width+(w+1)];
                pt3=vertPos[(h+1)*width+(w+0)];
                pt4=vertPos[(h+1)*width+(w+1)];
                pt5=(pt1+pt2+pt3+pt4)/4.0f;
                nor=QVector3D::normal(pt3-pt2,pt4-pt1);

                id=(h+0)*width+(w+0);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                id=(h+0)*width+(w+1);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                vertData.append(pt5.x());vertData.append(pt5.y());vertData.append(pt5.z());
                vertData.append(nor.x());vertData.append(nor.y());vertData.append(nor.z());

                id=(h+0)*width+(w+1);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                id=(h+1)*width+(w+1);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                vertData.append(pt5.x());vertData.append(pt5.y());vertData.append(pt5.z());
                vertData.append(nor.x());vertData.append(nor.y());vertData.append(nor.z());

                id=(h+1)*width+(w+1);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                id=(h+1)*width+(w+0);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                vertData.append(pt5.x());vertData.append(pt5.y());vertData.append(pt5.z());
                vertData.append(nor.x());vertData.append(nor.y());vertData.append(nor.z());

                id=(h+1)*width+(w+0);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                id=(h+0)*width+(w+0);
                vertData.append(vertPos[id].x()) ;vertData.append(vertPos[id].y()) ;vertData.append(vertPos[id].z());
                vertData.append(vertNorm[id].x());vertData.append(vertNorm[id].y());vertData.append(vertNorm[id].z());
                vertData.append(pt5.x());vertData.append(pt5.y());vertData.append(pt5.z());
                vertData.append(nor.x());vertData.append(nor.y());vertData.append(nor.z());
            }
        }
    }

    vbo.create();
    vbo.bind();
    vbo.allocate(vertData.constData(), vertData.count() * int(sizeof(GLfloat)));
}

void mytruc::display(QMatrix4x4 &projectionMatrix,QMatrix4x4 &viewMatrix, QMatrix4x4 &lightMatrix){
    vbo.bind();
    shaderProgram.bind(); // active le shader program
    QMatrix3x3 normal_mat = lightMatrix.normalMatrix();

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
        if(type==1){
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
        }
        if(type==2){
            switch (displayMode) {
            case 0 :
            //pas d'affichage
            break;
            case 1 :
            //affichage avec des faces triangle/quad
                glDrawArrays(GL_TRIANGLES, 12*i,12);
            break;
            case 2 :
            //affichage en maille
                glLineWidth(3);
                glDrawArrays(GL_LINES, 12*i+0,12);
                glDrawArrays(GL_LINES, 12*i+1,11);
            break;
            case 3 :
            //affichage en sommet
                glPointSize(4);
                glDrawArrays(GL_POINTS, 12*i, 12);
            break;
            default:;
            }
        }
    }

    shaderProgram.disableAttributeArray("posAttr");
    shaderProgram.disableAttributeArray("norAttr");
    shaderProgram.release();
}
