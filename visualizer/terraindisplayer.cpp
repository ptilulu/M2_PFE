#include "terraindisplayer.h"

/**
 * @brief TerrainDisplayer::initializeGL
 */
TerrainDisplayer::TerrainDisplayer(TerrainDisplayer::Type type, TerrainDisplayer::DisplayMode displayMode)
{
    this->type = type;
    this->displayMode = displayMode;

    qDebug() << "TerrainDisplayer ready! Type:" << this->type << "DisplayMode:" << this->displayMode;
}

void TerrainDisplayer::initializeGL(){
    this->setShaderProgram(":/shaders/terrainDisplayer");
}

/**
 * @brief TerrainDisplayer::setShaderProgram
 * @param path
 */
void TerrainDisplayer::setShaderProgram(QString path){
    this->shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, QString(path + ".vsh"));
    this->shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, QString(path + ".fsh"));
    if(!this->shaderProgram.link()) {
        qWarning("Failed to compile and link shader program:");
        qWarning() << this->shaderProgram.log();
    }
}

/**
 * @brief TerrainDisplayer::makeGLObject
 */
void TerrainDisplayer::makeGLObject()
{
    this->rotation=QVector3D(90, 0, 0);

    float x = -(width/2.0f) + 0.5f;
    float z = -(height/2.0f) + 0.5f;

    QVector<GLfloat> vertData;

    std::vector<QVector3D> vertPos;
    std::vector<QVector3D> vertNorm;

    for(unsigned int h = 0; h < height; h++)
    {
        for(unsigned int w = 0; w < width; w++)
        {
            vertPos.push_back(QVector3D(x, altitudes[h * width + w] / 90.0f, z));
            x++;
        }
        x = -(width/2.0f) + 0.5f;
        z++;
    }

    QVector3D pt1, pt2, pt3, pt4, pt5, nor;

    for(unsigned int h = 0; h < height; h++)
    {
        for(unsigned int w = 0; w < width; w++)
        {
            if(w == 0)        { pt1 = vertPos[h * width + w]; } else { pt1 = vertPos[h * width + (w-1)]; }
            if(h == 0)        { pt2 = vertPos[h * width + w]; } else { pt2 = vertPos[(h-1) * width + w]; }
            if(w == width-1)  { pt3 = vertPos[h * width + w]; } else { pt3 = vertPos[h * width + (w+1)]; }
            if(h == height-1) { pt4 = vertPos[h * width + w]; } else { pt4 = vertPos[(h+1) * width + w]; }
            vertNorm.push_back(QVector3D::normal(pt4 - pt2, pt3 - pt1));
        }
    }

    if(type == QUAD_2_TRIANGES)
    {
        for(unsigned int h = 0; h < height-1; h++)
        {
            for(unsigned int w = 0; w < width-1; w++){

                std::vector<unsigned int> ids = {
                    (h+0) * width + (w+0),
                    (h+0) * width + (w+1),
                    (h+1) * width + (w+0),
                    (h+0) * width + (w+1),
                    (h+1) * width + (w+0),
                    (h+1) * width + (w+1)
                };

                for(unsigned int id : ids){
                    vertData.append(vertPos[id].x());
                    vertData.append(vertPos[id].y());
                    vertData.append(vertPos[id].z());
                    vertData.append(vertNorm[id].x());
                    vertData.append(vertNorm[id].y());
                    vertData.append(vertNorm[id].z());
                }
            }
        }
    }

    if(type == QUAD_4_TRIANGLES)
    {
        for(unsigned int h = 0; h < height-1; h++)
        {
            for(unsigned int w = 0; w < width-1; w++)
            {
                pt1 = vertPos[(h+0) * width + (w+0)];
                pt2 = vertPos[(h+0) * width + (w+1)];
                pt3 = vertPos[(h+1) * width + (w+0)];
                pt4 = vertPos[(h+1) * width + (w+1)];
                pt5 = (pt1 + pt2 + pt3 + pt4) / 4.0f;
                nor = QVector3D::normal(pt3 - pt2, pt4 - pt1);


                std::vector<unsigned int> ids = {
                    (h+0) * width + (w+0),
                    (h+0) * width + (w+1),
                    (h+0) * width + (w+1),
                    (h+1) * width + (w+1),
                    (h+1) * width + (w+1),
                    (h+1) * width + (w+0),
                    (h+1) * width + (w+0),
                    (h+0) * width + (w+0)
                };

                for(unsigned int i = 0; i < ids.size(); i++){
                    vertData.append(vertPos[ids[i]].x());
                    vertData.append(vertPos[ids[i]].y());
                    vertData.append(vertPos[ids[i]].z());
                    vertData.append(vertNorm[ids[i]].x());
                    vertData.append(vertNorm[ids[i]].y());
                    vertData.append(vertNorm[ids[i]].z());
                    if(i % 2 == 1){
                        vertData.append(pt5.x());
                        vertData.append(pt5.y());
                        vertData.append(pt5.z());
                        vertData.append(nor.x());
                        vertData.append(nor.y());
                        vertData.append(nor.z());
                    }
                }
            }
        }
    }

    this->vbo.create();
    this->vbo.bind();
    this->vbo.allocate(vertData.constData(), vertData.count() * int(sizeof(GLfloat)));

    qDebug() << __FUNCTION__ << "done!";
}

/**
 * @brief TerrainDisplayer::display
 * @param projectionMatrix
 * @param viewMatrix
 * @param lightMatrix
 */
void TerrainDisplayer::display(QMatrix4x4 &projectionMatrix,QMatrix4x4 &viewMatrix, QMatrix4x4 &lightMatrix)
{
    this->vbo.bind();
    this->shaderProgram.bind();
    QMatrix3x3 normal_mat = lightMatrix.normalMatrix();

    this->shaderProgram.setUniformValue("projectionMatrix", projectionMatrix);
    this->shaderProgram.setUniformValue("viewMatrix", viewMatrix);
    this->shaderProgram.setUniformValue("norMatrix", normal_mat);
    this->shaderProgram.setAttributeBuffer("posAttr", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    this->shaderProgram.setAttributeBuffer("norAttr", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
    this->shaderProgram.enableAttributeArray("posAttr");
    this->shaderProgram.enableAttributeArray("norAttr");

    for(int i = 0; i < static_cast<int>((width-1) * (height-1)); i++)
    {
        modelMatrix.setToIdentity();
        modelMatrix.translate(this->position);
        modelMatrix.rotate(this->rotation.x(), 1, 0, 0);
        modelMatrix.rotate(this->rotation.y(), 0, 1, 0);
        modelMatrix.rotate(this->rotation.z(), 0, 0, 1);

        this->shaderProgram.setUniformValue("size", size);
        this->shaderProgram.setUniformValue("modelMatrix", modelMatrix);

        if(type == QUAD_2_TRIANGES)
        {
            switch (displayMode)
            {
                case FACE:
                    //affichage avec des faces triangle/quad
                    glDrawArrays(GL_TRIANGLES, 6 * i, 6);
                break;

                case MAILLE:
                    //affichage en maille
                    glLineWidth(3);
                    glDrawArrays(GL_LINES, 6 * i + 0, 6);
                    glDrawArrays(GL_LINES, 6 * i + 1, 4);
                break;

                case SOMMET:
                    //affichage en sommet
                    glPointSize(4);
                    glDrawArrays(GL_POINTS, 6 * i, 6);
                break;

                default:;
                case NONE:
                    //pas d'affichage
                break;
            }
        }

        if(type == QUAD_4_TRIANGLES)
        {
            switch (displayMode)
            {
                case FACE:
                    //affichage avec des faces triangle/quad
                    glDrawArrays(GL_TRIANGLES, 12 * i, 12);
                break;

                case MAILLE:
                    //affichage en maille
                    glLineWidth(3);
                    glDrawArrays(GL_LINES, 12 * i + 0, 12);
                    glDrawArrays(GL_LINES, 12 * i + 1, 11);
                break;

                case SOMMET:
                    //affichage en sommet
                    glPointSize(4);
                    glDrawArrays(GL_POINTS, 12 * i, 12);
                break;

                default:;
                case NONE:
                    //pas d'affichage
                break;
            }
        }
    }

    this->shaderProgram.disableAttributeArray("posAttr");
    this->shaderProgram.disableAttributeArray("norAttr");
    this->shaderProgram.release();
}

/**
 * @brief TerrainDisplayer::setAltitudes
 * @param altitudes
 * @param width
 * @param height
 */
void TerrainDisplayer::setAltitudes(std::vector<float> altitudes, unsigned int width, unsigned int height)
{
    this->altitudes = altitudes;
    this->width = width;
    this->height = height;

    qDebug() << __FUNCTION__ << "done!";
}
