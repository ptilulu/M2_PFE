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
    glClearColor(0.5f,0.5f,1.0f,1.0f);
    glEnable(GL_DEPTH_TEST);

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


void GLArea::paintGL()
{
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


void GLArea::keyPressEvent(QKeyEvent *ev)
{
    float da = 0.1f;

    switch(ev->key()) {
    case Qt::Key_A :
        xRot -= da;
        break;

    case Qt::Key_Q :
        xRot += da;
        break;

    case Qt::Key_Z :
        yRot -= da;
        break;

    case Qt::Key_S :
        yRot += da;
        break;

    case Qt::Key_E :
        zRot -= da;
        break;

    case Qt::Key_D :
        zRot += da;
        break;
        }
    update();
}


void GLArea::mousePressEvent(QMouseEvent *ev)
{
    lastPos = ev->pos();
}

void GLArea::mouseMoveEvent(QMouseEvent *ev)
{
    int dx = ev->x() - lastPos.x();
    int dy = ev->y() - lastPos.y();

    if (ev->buttons() & Qt::LeftButton) {
        xRot += dy;
        yRot += dx;
        update();
    } else if (ev->buttons() & Qt::RightButton) {
        xPos += dx/10.0f;
        yPos -= dy/10.0f;
        update();
    } else if (ev->buttons() & Qt::MidButton) {
        xPos += dx/10.0f;
        zPos += dy;
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
}


void GLArea::onTimeout()
{
    static qint64 old_chrono = elapsedTimer.elapsed(); // static : initialisation la première fois et conserve la dernière valeur
    qint64 chrono = elapsedTimer.elapsed();
    dt = (chrono - old_chrono) / 1000.0f;
    old_chrono = chrono;
    update();
}
