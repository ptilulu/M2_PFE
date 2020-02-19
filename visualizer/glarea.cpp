// Basé sur :
// CC-BY Edouard.Thiel@univ-amu.fr - 22/01/2019

#include "glarea.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>



GLArea::GLArea(QWidget *parent) :
    QOpenGLWidget(parent)
{
    QSurfaceFormat sf;
    sf.setDepthBufferSize(24);
    sf.setSamples(16);
    setFormat(sf);

    setEnabled(true);                   // événements clavier et souris
    setFocusPolicy(Qt::StrongFocus);    // accepte focus
    setFocus();                         // donne le focus

    timer = new QTimer(this);
    timer->setInterval(20);           // msec
    connect (timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start();
    elapsedTimer.start();
}


GLArea::~GLArea()
{
    delete timer;

    // Contrairement aux méthodes virtuelles initializeGL, resizeGL et repaintGL,
    // dans le destructeur le contexte GL n'est pas automatiquement rendu courant.
    makeCurrent();
    tearGLObjects();
    doneCurrent();
}


void GLArea::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(bgr,bgg,bgb,bga);
    glEnable(GL_DEPTH_TEST);

    truc.initializeGL();
    makeGLObjects();
    /*
    program_skybox = new QOpenGLShaderProgram(this);
    program_skybox->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/skybox.vsh");
    program_skybox->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/skybox.fsh");
    if (! program_skybox->link()) {
        qWarning("Failed to compile and link shader program:");
        qWarning() << program_skybox->log();
    }
    program_skybox->setUniformValue("texture", 0);
    */
}


void GLArea::makeGLObjects()
{
    truc.makeGLObject();
    // Pour être sûr de ne pas couper le terrain
//    float skyboxBoundaries = std::max(std::max(int(dem->getWidth()), int(dem->getHeight())), int(dem->getMaxElevation()));
/*
    float skyboxVertices[] = {
        -skyboxBoundaries, skyboxBoundaries, -skyboxBoundaries,
        -skyboxBoundaries, -skyboxBoundaries, -skyboxBoundaries,
        skyboxBoundaries, -skyboxBoundaries, -skyboxBoundaries,
        skyboxBoundaries, -skyboxBoundaries, -skyboxBoundaries,
        skyboxBoundaries, skyboxBoundaries, -skyboxBoundaries,

        -skyboxBoundaries, -skyboxBoundaries, skyboxBoundaries,
        -skyboxBoundaries, -skyboxBoundaries, -skyboxBoundaries,
        -skyboxBoundaries, skyboxBoundaries, -skyboxBoundaries,
        -skyboxBoundaries, skyboxBoundaries, skyboxBoundaries,
        -skyboxBoundaries, -skyboxBoundaries, skyboxBoundaries,


    };
*/
/*
    QVector<GLfloat> vertData_skybox;
    for (int i = 0; i < 6; ++i) {
        // coordonnées sommets
        for (int j = 0; j < 3; j++)
            vertData_skybox.append(skyboxVertices[i*3+j]);
        // coordonnées texture
        for (int j = 0; j < 2; j++)
            vertData_skybox.append(texCoords_sol[i*2+j]);
    }
    vbo_skybox.create();
    vbo_skybox.bind();
    vbo_skybox.allocate(vertData_skybox.constData(), vertData_skybox.count() * int(sizeof(GLfloat)));

    QImage skybox_image(":/textures/skybox.png");
    if (skybox_image.isNull()) qDebug() << "load image skybox.png failed";
    texture_skybox = new QOpenGLTexture(skybox_image);
    */
}

void GLArea::paintGL()
{
    glClearColor(bgr,bgg,bgb,bga);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Matrice de projection
    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(45.0f, windowRatio, 1.0f, 1000.0f);

    // Matrice de vue (caméra)
    QMatrix4x4 viewMatrix;
    viewMatrix.translate(xPos, yPos, zPos);
    viewMatrix.rotate(xRot, 1, 0, 0);
    viewMatrix.rotate(yRot, 0, 1, 0);
    viewMatrix.rotate(zRot, 0, 0, 1);

    truc.display(projectionMatrix,viewMatrix);
    /*
    vbo_skybox.bind();
    program_skybox->bind();

    QMatrix4x4 modelMatrixSkybox;
    modelMatrixSkybox.translate(0.0f, 0.0f, 0.0f);
    program_skybox->setUniformValue("projection", projectionMatrix);
    program_skybox->setUniformValue("view", viewMatrix);
    program_skybox->setUniformValue("model", modelMatrixSol);

    program_skybox->setAttributeBuffer("in_position", GL_FLOAT, 0, 3, 5 * sizeof(GLfloat));
    program_skybox->setAttributeBuffer("in_uv", GL_FLOAT, 3 * sizeof(GLfloat), 2, 5 * sizeof(GLfloat));
    program_skybox->enableAttributeArray("in_position");
    program_skybox->enableAttributeArray("in_uv");

    texture_skybox->bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    texture_skybox->release();

    program_skybox->disableAttributeArray("in_position");
    program_skybox->disableAttributeArray("colAttr");
    program_skybox->release();
    */
}


void GLArea::tearGLObjects()
{
    //vbo_skybox.destroy();
    //delete texture_skybox;
}

void GLArea::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    windowRatio = float(w) / h;
}

void GLArea::keyPressEvent(QKeyEvent *ev)
{

    switch(ev->key()) {
        case Qt::Key_A :
            xRot -= deltaAngle/9;
        break;

        case Qt::Key_Q :
            xRot += deltaAngle/9;
        break;

        case Qt::Key_Z :
            yRot -= deltaAngle/9;
        break;

        case Qt::Key_S :
            yRot += deltaAngle/9;
        break;

        case Qt::Key_E :
            zRot -= deltaAngle/9;
        break;

        case Qt::Key_D :
            zRot += deltaAngle/9;
        break;

        case Qt::Key_Plus :
            deltaAngle*=2;
            deltaZoom*=2;
            qDebug() << "deltaMouvment = " << deltaAngle;
        break;

        case Qt::Key_Minus :
            deltaAngle/=2;
            deltaZoom/=2;
            qDebug() << "deltaMouvment = " << deltaAngle;
        break;

        case Qt::Key_Return :
            xRot=90.0f, yRot=0.0f, zRot=0.0f;
            xPos=0.0f,  yPos=-6.0f, zPos=-980.0f;
        break;

        case Qt::Key_Escape:
            qDebug() <<"m_x" << xPos
                     <<"m_y" << yPos
                     <<"m_z" << zPos
                     <<"a_x" << xRot
                     <<"a_y" << yRot
                     <<"a_z" << zRot;
        break;
    }
    update();
}


void GLArea::mousePressEvent(QMouseEvent *ev)
{
    lastPos = ev->pos();
}

void GLArea::wheelEvent(QWheelEvent *ev){
    zPos += static_cast<float>(ev->delta() * deltaZoom/100);
    update();
}

void GLArea::mouseMoveEvent(QMouseEvent *ev)
{
    int dx = ev->x() - lastPos.x();
    int dy = ev->y() - lastPos.y();

    if (ev->buttons() & Qt::MidButton || (ev->buttons() & Qt::LeftButton && ev->buttons() & Qt::RightButton)) {
        xPos += dx/10.0f;
        zPos += dy;
        update();
    } else if (ev->buttons() & Qt::LeftButton) {
        xRot += dy;
        yRot += dx;
        update();
    } else if (ev->buttons() & Qt::RightButton) {
        xPos += dx/10.0f;
        yPos -= dy/10.0f;
        update();
    }

    lastPos = ev->pos();
}

DEM *GLArea::getDem() const
{
    return dem;
}

void GLArea::setDem(DEM *value)
{
    dem = value;
    truc.setAltitudes(dem->elevation_map,dem->getWidth(),dem->getHeight());
    makeGLObjects();
}


void GLArea::onTimeout()
{
    static qint64 old_chrono = elapsedTimer.elapsed(); // static : initialisation la première fois et conserve la dernière valeur
    qint64 chrono = elapsedTimer.elapsed();
    dt = (chrono - old_chrono) / 1000.0f;
    old_chrono = chrono;
    update();
}
