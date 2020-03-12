#include <QDebug>
#include <QSurfaceFormat>
#include <QMatrix4x4>

#include "glarea.h"

/**
 * @brief GLArea::GLArea
 * @param parent
 */
GLArea::GLArea(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat sf;
    sf.setDepthBufferSize(24);
    sf.setSamples(16);
    this->setFormat(sf);

    this->setEnabled(true);
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
}

/**
 * @brief GLArea::~GLArea
 */
GLArea::~GLArea()
{
    this->makeCurrent();
    this->tearGLObjects();
    this->doneCurrent();
}

/**
 * @brief GLArea::initializeGL
 */
void GLArea::initializeGL()
{
    this->initializeOpenGLFunctions();
    this->glClearColor(this->skyBackground[0], this->skyBackground[1], this->skyBackground[2], this->skyBackground[3]);
    this->glEnable(GL_DEPTH_TEST);

    this->terrainDisplayer.initializeGL();

    this->shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/shaders/simpleColor.vsh");
    this->shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/simpleColor.fsh");
    if (!this->shaderProgram.link()){
        qWarning("Failed to compile and link shader program:");
        qWarning() << this->shaderProgram.log();
    }
}

/**
 * @brief GLArea::makeGLObjects
 */
void GLArea::makeGLObjects()
{
    QVector<GLfloat> vertData;

    if(displayMode == TERRAIN){

        this->terrainDisplayer.makeGLObject();

        vertData.append(0.0);
        vertData.append(0.0);
        vertData.append(std::max(dem->getHeight(),dem->getWidth()));

        vertData.append(255.0f/255);
        vertData.append(255.0f/255);
        vertData.append(0.0f/255);

        vertData.append(0.0);
        vertData.append(0.0);
        vertData.append(0.0);

        vertData.append(255.0f/255);
        vertData.append(255.0f/255);
        vertData.append(0.0f/255);

        this->vbo.create();
        this->vbo.bind();
        this->vbo.allocate(vertData.constData(), vertData.count() * int(sizeof(GLfloat)));

    } else if(displayMode == VOXEL){

        std::vector<std::vector<QVector3D>> pos(dem->getWidth(), std::vector<QVector3D>(dem->getHeight(), {0.0, 0.0, 0.0}));
        for(int i = 0; i < dem->getWidth(); i++){
            for(int j = 0; j < dem->getHeight(); j++){
                pos[i][j] = {i / 10.0f, dem->getNormalizedElevationAt(i,j) / 10.0f, j / 10.0f};
            }
        }
        voxels.push_back(new VoxelDisplayer(pos, 0.05, true));
        for(int i = 0; i < voxels.size(); i++) voxels.at(i)->createGlObject();

    }
}

/**
 * @brief GLArea::paintGL
 */
void GLArea::paintGL()
{
    this->glClearColor(this->skyBackground[0], this->skyBackground[1], this->skyBackground[2], this->skyBackground[3]);
    this->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(this->dem != nullptr) {

        // Matrice de projection
        QMatrix4x4 projectionMatrix;
        projectionMatrix.perspective(45.0f, this->windowRatio, 1.0f, 1000000.0f);

        // Matrice de vue (caméra)
        QMatrix4x4 viewMatrix;

        viewMatrix.translate(0, 0, this->zPos-std::max(this->dem->getWidth(), this->dem->getHeight()));
        viewMatrix.rotate(this->xRot, 1, 0, 0);
        viewMatrix.rotate(this->yRot, 0, 1, 0);
        viewMatrix.rotate(this->zRot, 0, 0, 1);
        viewMatrix.translate(this->xPos, this->yPos, 0);

        QMatrix4x4 lightMatrix;
        lightMatrix.rotate(this->xRotLight, 1, 0, 0);
        lightMatrix.rotate(this->yRotLight, 0, 1, 0);
        lightMatrix.rotate(this->zRotLight, 0, 0, 1);
        lightMatrix.rotate(90, 1, 0, 0);

        if(displayMode == TERRAIN) this->terrainDisplayer.display(projectionMatrix, viewMatrix, lightMatrix);
        else if(displayMode == VOXEL)
        {
            for(int i = 0; i < voxels.size(); i++) voxels.at(i)->display(projectionMatrix, viewMatrix);
        }
        QMatrix4x4 modelMatrix;
        modelMatrix.rotate(this->zRotLight, 0, 0, -1);
        modelMatrix.rotate(this->yRotLight, 0, -1, 0);
        modelMatrix.rotate(this->xRotLight, -1, 0, 0);

        if(displayMode == TERRAIN) this->vbo.bind();
        this->shaderProgram.bind();

        this->shaderProgram.setUniformValue("projectionMatrix", projectionMatrix);
        this->shaderProgram.setUniformValue("viewMatrix", viewMatrix);
        this->shaderProgram.setUniformValue("size", 1.0f);
        this->shaderProgram.setUniformValue("modelMatrix", modelMatrix);
        this->shaderProgram.setAttributeBuffer("in_position", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
        this->shaderProgram.setAttributeBuffer("colAttr", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
        this->shaderProgram.enableAttributeArray("in_position");
        this->shaderProgram.enableAttributeArray("colAttr");

        if(displayMode == TERRAIN){
            glPointSize(10);
            this->glDrawArrays(GL_POINTS, 0, 1);
            glLineWidth(1);
            this->glDrawArrays(GL_LINES, 0, 2);

        }
        this->shaderProgram.disableAttributeArray("in_position");
        this->shaderProgram.disableAttributeArray("colAttr");
        this->shaderProgram.release();
    }
}

/**
 * @brief GLArea::tearGLObjects
 */
void GLArea::tearGLObjects()
{
    if(displayMode == TERRAIN) this->vbo.destroy();
    else if(displayMode == VOXEL) for(auto voxel : voxels) voxel->tearGLObjects();
}

/**
 * @brief GLArea::resizeGL
 * @param w
 * @param h
 */
void GLArea::resizeGL(int w, int h)
{
    this->glViewport(0, 0, w, h);
    this->windowRatio = float(w) / h;
}

/**
 * @brief GLArea::keyPressEvent
 * @param ev
 */
void GLArea::keyPressEvent(QKeyEvent *ev)
{

    switch(ev->key()) {
        case Qt::Key_A :
            this->xRot -= this->deltaAngle;
        break;

        case Qt::Key_Q :
            this->xRot += this->deltaAngle;
        break;

        case Qt::Key_Z :
            this->yRot -= this->deltaAngle;
        break;

        case Qt::Key_S :
            this->yRot += this->deltaAngle;
        break;

        case Qt::Key_E :
            this->zRot -= this->deltaAngle;
        break;

        case Qt::Key_D :
            this->zRot += this->deltaAngle;
        break;

        case Qt::Key_7 :
            this->xRotLight -= this->deltaAngle;
        break;

        case Qt::Key_4 :
            this->xRotLight += this->deltaAngle;
        break;

        case Qt::Key_8 :
            this->yRotLight -= this->deltaAngle;
        break;

        case Qt::Key_5 :
            this->yRotLight += this->deltaAngle;
        break;

        case Qt::Key_9 :
            this->zRotLight -= this->deltaAngle;
        break;

        case Qt::Key_6 :
            this->zRotLight += this->deltaAngle;
        break;

        case Qt::Key_Plus :
            this->deltaAngle *= 2;
            this->deltaZoom *= 2;
        break;

        case Qt::Key_Minus :
            this->deltaAngle /= 2;
            this->deltaZoom /= 2;
        break;

        case Qt::Key_Return :
            this->xRot = 0.0f;
            this->yRot = 0.0f;
            this->zRot = 0.0f;
            this->xPos = 0.0f;
            this->yPos = 0.0f;
            this->zPos = 0.0f;
        break;

        case Qt::Key_Backspace :
            this->xRotLight = 0.0f;
            this->yRotLight = 0.0f;
            this->zRotLight = 0.0f;
        break;

        case Qt::Key_Space :
            this->xRotLight = this->xRot;
            this->yRotLight = this->yRot;
            this->zRotLight = this->zRot;
        break;

        case Qt::Key_Escape:
            qDebug() << "m_x" << xPos << "m_y" << yPos << "m_z" << zPos
                     << "a_x" << xRot << "a_y" << yRot << "a_z" << zRot
                     << "al_x" << xRotLight << "al_y" << yRotLight << "al_z" << zRotLight;
        break;
    }
    this->update();
}

/**
 * @brief GLArea::mousePressEvent
 * @param ev
 */
void GLArea::mousePressEvent(QMouseEvent *ev)
{
    lastPos = ev->pos();
}

/**
 * @brief GLArea::wheelEvent
 * @param ev
 */
void GLArea::wheelEvent(QWheelEvent *ev){
    this->zPos += static_cast<float>(ev->delta() * this->deltaZoom / 100);
    this->update();
}

/**
 * @brief GLArea::getDisplayMode
 * @return
 */
GLArea::DisplayMode GLArea::getDisplayMode() const
{
    return displayMode;
}

/**
 * @brief GLArea::setDisplayMode
 * @param value
 */
void GLArea::setDisplayMode(const GLArea::DisplayMode &value)
{
    displayMode = value;
}

/**
 * @brief GLArea::mouseMoveEvent
 * @param ev
 */
void GLArea::mouseMoveEvent(QMouseEvent *ev)
{
    int dx = ev->x() - this->lastPos.x();
    int dy = ev->y() - this->lastPos.y();

    if (ev->buttons() & Qt::MidButton) {
        this->xPos += dx / 10.0f;
        this->zPos += dy;
        this->update();
    } else if (ev->buttons() & Qt::LeftButton && ev->buttons() & Qt::RightButton){
        this->xRotLight -= dy / 3.6f;
        this->yRotLight -= dx / 3.6f;
        this->update();
    } else if (ev->buttons() & Qt::LeftButton) {
        this->xRot += dy / 3.6f;
        this->yRot += dx / 3.6f;
        this->update();
    } else if (ev->buttons() & Qt::RightButton) {
        this->xPos += dx / 10.0f;
        this->yPos -= dy / 10.0f;
        this->update();
    } else if (ev->buttons() & Qt::BackButton) {
        this->zRot += dx / 3.6f;
        this->zRot += dy / 3.6f;
        this->update();
    }

    this->lastPos = ev->pos();
}

/**
 * @brief GLArea::getDem
 * @return
 */
DEM *GLArea::getDem() const
{
    return dem;
}

/**
 * @brief GLArea::setDem
 * @param dem
 */
void GLArea::setDem(DEM *dem)
{
    this->dem = dem;
    terrainDisplayer.setAltitudes(this->dem->getElevationMap(), this->dem->getWidth(), this->dem->getHeight());
    this->makeGLObjects();
}
