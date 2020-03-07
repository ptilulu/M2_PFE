#ifndef VOXELDISPLAYER_H
#define VOXELDISPLAYER_H

#include <iostream>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>

/**
 * @brief The VoxelDisplayer class
 */
class VoxelDisplayer
{
    public:
        /**
         * @brief VoxelDisplayer
         * @param pos
         * @param color
         * @param h
         * @param isDisplay
         */
        VoxelDisplayer(std::vector<std::vector<QVector3D>> pos, double h, bool isDisplay);

        /**
         * @brief setPositionPoint
         * @param pos
         */
        void setPositionPoint(QVector3D pos);

        /**
         * @brief setDisplay
         * @param mode
         */
        void setDisplay(bool mode);

        /**
         * @brief createPoint
         * @param vertices
         * @param colors
         * @param coord
         * @param couleur
         */
        void createPoint(std::vector<GLfloat> &vertices, QVector3D coord);

        /**
         * @brief createGlObject
         */
        void createGlObject();

        /**
         * @brief display
         * @param m_program
         */
        void display(QOpenGLShaderProgram &m_program);

        /**
         * @brief tearGLObjects
         */
        void tearGLObjects();

    private:
        /**
         * @brief m_vbo
         */
        QOpenGLBuffer m_vbo;

        /**
         * @brief vertData
         */
        QVector<GLfloat> vertData;

        /**
         * @brief displayIt
         */
        bool displayIt = true;

        /**
         * @brief type
         */
        int type = GL_QUADS;

        /**
         * @brief nbPointStructure
         */
        int nbPointStructure = 4; //pour un triangle : 3 points necessaires

        /**
         * @brief nbPointControl
         */
        int nbPointControl = 8; // 8 points dans un cube

        /**
         * @brief division
         */
        int division = 6; // 12 triangles dans un cube

        /**
         * @brief nombreTotal
         */
        int nombreTotal = 0;

        /**
         * @brief posInit
         */
        std::vector<std::vector<QVector3D>> posInit;

        /**
         * @brief hauteur
         */
        double hauteur = 0.02;
};

#endif // VOXELDISPLAYER_H
