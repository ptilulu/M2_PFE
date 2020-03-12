#ifndef GLAREA_H
#define GLAREA_H

#include <QKeyEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>
#include <QtMath>

#include "gl_point.h"
#include "dem.h"

class GLArea : public QOpenGLWidget,
               protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLArea(QWidget *parent = 0);
    ~GLArea() override;

    DEM *getDem() const;
    void setDem(DEM *value);
    double degreeToRadian(double angle);

    std::vector <myGlObject*> MyObjects;
    DEM* dem = nullptr;



public slots:
    void setRadius(double radius);

signals:  // On ne les implémente pas, elles seront générées par MOC ;
          // les paramètres seront passés aux slots connectés.
    void radiusChanged(double newRadius);

protected slots:
    void onTimeout();

protected:
    void initializeGL() override;
    void doProjection();
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *ev) override;
    void keyReleaseEvent(QKeyEvent *ev) override;
    void mousePressEvent(QMouseEvent *ev) override;
    void wheelEvent(QWheelEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;


private:
    double m_angleX = 0;
    double m_angleY = 0;
    double m_angleZ = 0;

    double m_posX = 0;
    double m_posY = 0;
    double m_posZ = 0;
    QPoint lastPos;

    QTimer *m_timer = nullptr;
    double m_radius = 0.5;
    double m_ratio = 1;
    double m_anim = 0;
    QVector<GLfloat> vertData;

    QOpenGLShaderProgram *m_program;

    void makeGLObjects();
    void tearGLObjects();
};

#endif // GLAREA_H
