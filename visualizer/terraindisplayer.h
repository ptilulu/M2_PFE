#ifndef TERRAINDISPLAYER_H
#define TERRAINDISPLAYER_H

#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QString>


class TerrainDisplayer
{
    public:

        /**
         * @brief Affichage
         */
        enum Type { QUAD_2_TRIANGLES, QUAD_4_TRIANGLES };
        enum DisplayMode { NONE, FACE, MAILLE, SOMMET };

        /**
         * @brief TerrainDisplayer Constructeur
         */
        TerrainDisplayer(Type type = QUAD_4_TRIANGLES, DisplayMode displayMode = FACE);

        /**
         * @brief initializeGL
         */
        void initializeGL();

        /**
         * @brief setShaderProgram
         * @param path
         */
        void setShaderProgram(QString path);

        /**
         * @brief makeGLObject
         */
        void makeGLObject();

        /**
         * @brief display
         * @param projectionMatrix
         * @param viewMatrix
         * @param lightMatrix
         */
        void display(QMatrix4x4 &projectionMatrix, QMatrix4x4 &viewMatrix, QMatrix4x4 &lightMatrix);

        /**
         * @brief setAltitudes
         * @param altitudes
         * @param width
         * @param height
         */
        void setAltitudes(std::vector<float> altitudes, unsigned int width, unsigned int height);

    private:

        /**
         * @brief altitudes
         */
        std::vector<float> altitudes;

        /**
         * @brief width
         */
        unsigned int width = 0;

        /**
         * @brief height
         */
        unsigned int height = 0;

        /**
         * @brief displayMode
         */
        DisplayMode displayMode;

        /**
         * @brief type
         */
        Type type;

        /**
         * @brief size
         */
        float size = 1;

        /**
         * @brief position
         */
        QVector3D position;

        /**
         * @brief rotation
         */
        QVector3D rotation;

        /**
         * @brief modelMatrix
         */
        QMatrix4x4 modelMatrix;

        /**
         * @brief shaderProgram
         */
        QOpenGLShaderProgram shaderProgram;

        /**
         * @brief vbo
         */
        QOpenGLBuffer vbo;
};
#endif // TERRAINDISPLAYER_H
