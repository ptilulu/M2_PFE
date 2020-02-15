#ifndef MYTRUC_H
#define MYTRUC_H
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>

#include <QString>


class mytruc
{
public:
    mytruc();

    void makeGLObject();
    void display(QMatrix4x4 &projectionMatrix, QMatrix4x4 &viewMatrix);
    void setShaderProgram(char * pathAndName);
    void initializeGL();
    void setAltitudes(std::vector<float> altitudes, uint width, uint length);

    std::vector<float> altitudes;

    uint width,length;
    int displayMode;
    float size;

    QVector3D position, rotation;

    QMatrix4x4 modelMatrix;
    QOpenGLShaderProgram shaderProgram;
    QOpenGLBuffer vbo;
};
#endif // MYTRUC_H
