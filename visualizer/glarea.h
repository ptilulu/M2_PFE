// Basé sur :
// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#ifndef GLAREA_H
#define GLAREA_H

#include <QKeyEvent>
#include <QTimer>
#include <QElapsedTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QVector3D>

#include <algorithm>
#include "dem.h"
#include "mytruc.h"

class GLArea : public QOpenGLWidget,
               protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLArea(QWidget *parent = nullptr);
    ~GLArea() override;

    DEM *getDem() const;
    void setDem(DEM *value);

protected slots:
    void onTimeout();

protected:
    void initializeGL() override;
    void doProjection();
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;


private:
    float xRot=90.0f, yRot=0.0f, zRot=0.0f;
    float xRotLight=90.0f, yRotLight=0.0f, zRotLight=0.0f;
    float xPos=0.0f,  yPos=0.0f, zPos=-1000.0f;
    float bgr=0.2f, bgg=0.4f, bgb=1.0f, bga=1.0f;   //background rgba
    float deltaAngle=90/64.0f, deltaZoom=1;                //delta for mouvement
    QTimer *timer = nullptr;
    QElapsedTimer elapsedTimer;
    float dt = 0;
    float windowRatio = 1.0f;
    QPoint lastPos;

    DEM* dem = nullptr;
    mytruc truc;
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram shaderProgram;
    /*
    QOpenGLShaderProgram *program_skybox;
    QOpenGLBuffer vbo_skybox;
    QVector3D skybox_boundaries = QVector3D(9000, 8000, 8000);
    QOpenGLTexture texture_skybox;
    */

    void makeGLObjects();
    void tearGLObjects();
};

#endif // GLAREA_H
