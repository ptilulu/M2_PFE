#ifndef GL_POINT_H
#define GL_POINT_H

#include <iostream>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include "myglobject.h"

class gl_point : public myGlObject
{
public:
    gl_point(std::vector<std::vector<QVector3D>> pos, QVector3D color, double h, bool isDisplay);
    void setPositionPoint(QVector3D pos) override;
    void setDisplay(bool mode) override;


    void createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                                QVector3D coord, QVector3D couleur) override;
    void createGlObject() override;

    void display(QOpenGLShaderProgram &m_program) override;
    void tearGLObjects() override;


    QOpenGLBuffer m_vbo;
    QVector<GLfloat> vertData;
    bool displayIt = true;


    int type = GL_QUADS;
    int nbPointStructure = 4; //pour un triangle : 3 points necessaires
    int nbPointControl = 8; // 8 points dans un cube
    int division = 6; // 12 triangles dans un cube
    int nombreTotal = 0;

    std::vector<std::vector<QVector3D>> posInit;
    QVector3D colr {1.0, 1.0, 1.0};
    double hauteur = 0.02;
};

#endif // GL_POINT_H
