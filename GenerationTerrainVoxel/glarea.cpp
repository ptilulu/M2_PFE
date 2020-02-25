#include "glarea.h"
#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>

static const QString vertexShaderFile   = ":/basic.vsh";
static const QString fragmentShaderFile = ":/basic.fsh";


GLArea::GLArea(QWidget *parent) :
    QOpenGLWidget(parent)
{
    qDebug() << "init GLArea" ;

    QSurfaceFormat sf;
    sf.setDepthBufferSize(24);
    sf.setSamples(16);  // nb de sample par pixels : suréchantillonnage por l'antialiasing, en décalant à chaque fois le sommet
                        // cf https://www.khronos.org/opengl/wiki/Multisampling et https://stackoverflow.com/a/14474260
    setFormat(sf);
    qDebug() << "Depth is"<< format().depthBufferSize();

    setEnabled(true);  // événements clavier et souris
    setFocusPolicy(Qt::StrongFocus); // accepte focus
    setFocus();                      // donne le focus

    m_timer = new QTimer(this);
    m_timer->setInterval(50);  // msec
    connect (m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    connect (this, SIGNAL(radiusChanged(double)), this, SLOT(setRadius(double)));
    m_timer->start();
}

GLArea::~GLArea()
{
    qDebug() << "destroy GLArea";

    delete m_timer;

    // Contrairement aux méthodes virtuelles initializeGL, resizeGL et repaintGL,
    // dans le destructeur le contexte GL n'est pas automatiquement rendu courant.
    makeCurrent();
    tearGLObjects();
    doneCurrent();
}


/* ALGOS & FONCTIONS BASIQUES */

double GLArea::degreeToRadian(double angle){
    return angle*M_PI/180;
}

DEM *GLArea::getDem() const
{
    return dem;
}

void GLArea::setDem(DEM *value)
{
    dem = value;
    //truc.setAltitudes(dem->elevation_map,600,600);
    makeGLObjects();
}

/* OPENGL AREA */

void GLArea::initializeGL()
{
    qDebug() << __FUNCTION__ ;
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);

    //makeGLObjects();

    // shaders
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderFile);  // compile
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderFile);
    if (! m_program->link()) {  // édition de lien des shaders dans le shader program
        qWarning("Failed to compile and link shader program:");
        qWarning() << m_program->log();
    }

    // récupère identifiants de "variables" dans les shaders
    //m_posAttr = m_program->attributeLocation("posAttr");
    //m_colAttr = m_program->attributeLocation("colAttr");
    //m_matrixUniform = m_program->uniformLocation("matrix");
}


void GLArea::makeGLObjects()
{
    //les objets - Point segment
    //MyObjects.push_back(new gl_point({0.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, 0.1, true));

    std::vector<QVector3D> pos;

    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 500; j++){
            float elev = int(dem->getNormalizedElevationAt(i,j));
            pos.push_back({i/10.0f, elev/10.0f, j/10.0f});
           /*if(elev > 0){
                for(float k = elev; k > 0; k--){
                    pos.push_back({i/10.0f, k/10.0f, j/10.0f});
                }
            }*/
        }
    }
    MyObjects.push_back(new gl_point(pos, {1.0, 1.0, 0.0}, 0.05, true));


    //création des objets GL
    for(int i = 0; i < MyObjects.size(); i++)
        MyObjects.at(i)->createGlObject();
}


void GLArea::tearGLObjects()
{
    for(auto object : MyObjects)
        object->tearGLObjects();
}


void GLArea::resizeGL(int w, int h)
{
    qDebug() << __FUNCTION__ << w << h;

    // C'est fait par défaut
    glViewport(0, 0, w, h);

    m_ratio = (double) w / h;
    // doProjection();
}

void GLArea::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind(); // active le shader program

    QMatrix4x4 matrix;

    GLfloat hr = m_radius, wr = hr * m_ratio;
    matrix.frustum(-wr, wr, -hr, hr, 1.0, 50.0);

    matrix.translate(0, 0, -3.0);

    //mouvement dans la scène avec la souris
    matrix.translate(m_posX, m_posY, m_posZ);

    // Rotation de la scène pour l'animation avec ZQSD AE
    matrix.rotate(m_angleX, 1, 0, 0);
    matrix.rotate(m_angleY, 0, 1, 0);
    matrix.rotate(m_angleZ, 0, 0, 1);

    m_program->setUniformValue("matrix", matrix);

    //méthode d'affichage (ligne, triangle etc)
    for(int i = 0; i < MyObjects.size(); i++)
        MyObjects.at(i)->display(*m_program);

    m_program->release();
}

void GLArea::keyPressEvent(QKeyEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->text();

    switch(ev->key()) {
        case Qt::Key_Space :
            if (m_timer->isActive())
                m_timer->stop();
            else m_timer->start();
            break;
        //en avant sur X
        case Qt::Key_Z :
            m_posZ += 1;
            break;
        //en arrière sur X
        case Qt::Key_S :
            m_posZ -= 1;
            break;

        //en avant sur Y
        case Qt::Key_D :
            m_posX -= 1;
            break;
        //en arrière sur Y
        case Qt::Key_Q :
            m_posX += 1;
            break;

        //en avant sur Z
        case Qt::Key_E :
            m_angleZ += 1;
            if (m_angleZ >= 360) m_angleZ -= 360;
            break;
        //en arrière sur Z
        case Qt::Key_A :
             m_angleZ -= 1;
             if (m_angleZ <= 360) m_angleZ += 360;
             break;

        case Qt::Key_R :
            if (ev->text() == "r")
                 setRadius(m_radius-0.05);
            else setRadius(m_radius+0.05);
            break;
    }
    update();
}


void GLArea::onTimeout()
{
    if (m_anim >= 1) m_anim = 0;
    m_anim += 0.01;
    update();
}

void GLArea::setRadius(double radius)
{
    if (radius != m_radius && radius > 0.01 && radius <= 10) {
        m_radius = radius;
        qDebug() << "  emit radiusChanged()";
        emit radiusChanged(radius);
    }
    update();
}

void GLArea::keyReleaseEvent(QKeyEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->text();
    update();
}


void GLArea::mousePressEvent(QMouseEvent *ev)
{
    lastPos = ev->pos();
    update();
}

void GLArea::wheelEvent(QWheelEvent *ev){
    m_posZ += static_cast<float>(ev->delta() * 1.0/100.0);
    update();
}

void GLArea::mouseReleaseEvent(QMouseEvent *ev)
{
    qDebug() << __FUNCTION__ << ev->x() << ev->y() << ev->button();
    update();
}


void GLArea::mouseMoveEvent(QMouseEvent *ev)
{
    int dx = ev->x() - lastPos.x();
    int dy = ev->y() - lastPos.y();

    if (ev->buttons() & Qt::LeftButton) {
        m_angleX += dy;
        m_angleY += dx;
    } else if (ev->buttons() & Qt::RightButton) {
        m_posX += dx/10.0f;
        m_posY -= dy/10.0f;
    } else if (ev->buttons() & Qt::MidButton) {
        m_posX += dx/10.0f;
        m_posY += dy;
    }

    lastPos = ev->pos();
    update();
}



