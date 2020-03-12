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
#include "terraindisplayer.h"
#include "voxeldisplayer.h"

/**
 * @brief La classe GLArea permettant l'affichage 3D de nos terrains
 */
class GLArea : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    public:

        enum DisplayMode { TERRAIN, VOXEL };

        /**
         * @brief GLArea Constructeur
         * @param parent Parent de l'objet
         */
        explicit GLArea(QWidget *parent = nullptr);

        /**
         * @brief ~GLArea Destructeur
         */
        ~GLArea() override;

        /**
         * @brief getDem Renvoie le DEM courant associé à l'objet
         * @return Le DEM courant
         */
        DEM *getDem() const;

        /**
         * @brief setDem Modifie le DEM courant associé à l'objet
         * @param dem Le nouveau DEM
         */
        void setDem(DEM *dem);

        DisplayMode getDisplayMode() const;
        void setDisplayMode(const DisplayMode &value);

protected:
        /**
         * @brief initializeGL
         */
        void initializeGL() override;

        /**
         * @brief resizeGL
         * @param w
         * @param h
         */
        void resizeGL(int w, int h) override;

        /**
         * @brief paintGL
         */
        void paintGL() override;

        /**
         * @brief keyPressEvent
         * @param event
         */
        void keyPressEvent(QKeyEvent *event) override;

        /**
         * @brief mousePressEvent
         * @param event
         */
        void mousePressEvent(QMouseEvent *event) override;

        /**
         * @brief mouseMoveEvent
         * @param event
         */
        void mouseMoveEvent(QMouseEvent *event) override;

        /**
         * @brief wheelEvent
         * @param event
         */
        void wheelEvent(QWheelEvent *event) override;

    private:
        /**
         * @brief xRot Rotation sur l'axe x du terrain
         */
        float xRot = 0.0f;

        /**
         * @brief yRot Rotation sur l'axe y du terrain
         */
        float yRot = 0.0f;

        /**
         * @brief zRot Rotation sur l'axe z du terrain
         */
        float zRot = 0.0f;

        /**
         * @brief xRotLight Rotation sur l'axe x de la lumière
         */
        float xRotLight = 0.0f;

        /**
         * @brief yRotLight Rotation sur l'axe y de la lumière
         */
        float yRotLight = 0.0f;

        /**
         * @brief zRotLight Rotation sur l'axe z de la lumière
         */
        float zRotLight = 0.0f;

        /**
         * @brief xPos Position sur l'axe x du terrain
         */
        float xPos = 0.0f;

        /**
         * @brief yPos Position sur l'axe y du terrain
         */
        float yPos = 0.0f;

        /**
         * @brief zPos Position sur l'axe z du terrain
         */
        float zPos = 0.0f;

        /**
         * @brief skyBackground[] Sky RGBA colors
         */
        float skyBackground[4] = { 0.2f, 0.4f, 1.0f, 1.0f };

        /**
         * @brief deltaAngle
         */
        float deltaAngle = 90 / 64.0f;

        /**
         * @brief deltaZoom delta for movement
         */
        float deltaZoom = 1;

        /**
         * @brief windowRatio
         */
        float windowRatio = 1.0f;

        /**
         * @brief lastPos
         */
        QPoint lastPos;

        /**
         * @brief dem
         */
        DEM* dem = nullptr;

        /**
         * @brief terrainDisplayer
         */
        TerrainDisplayer terrainDisplayer;

        /**
         * @brief voxels
         */
        std::vector<VoxelDisplayer*> voxels;

        /**
         * @brief vbo
         */
        QOpenGLBuffer vbo;

        /**
         * @brief shaderProgram
         */
        QOpenGLShaderProgram shaderProgram;

        /**
         * @brief displayMode
         */
        DisplayMode displayMode;

        /**
         * @brief makeGLObjects
         */
        void makeGLObjects();

        /**
         * @brief tearGLObjects
         */
        void tearGLObjects();
};

#endif // GLAREA_H
