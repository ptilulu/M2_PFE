#include "gl_point.h"

gl_point::gl_point(std::vector<std::vector<QVector3D>> pos, QVector3D color, double h, bool isDisplay)
{
    posInit = pos;
    colr = color;
    hauteur = h;
    displayIt = isDisplay;
}

void gl_point::setPositionPoint(QVector3D pos){
    createGlObject();
}

void gl_point::setDisplay(bool mode){
    displayIt = mode;
}

/* OPENGL */

void gl_point::createPoint(std::vector<GLfloat> &vertices, std::vector<GLfloat> &colors,
                            QVector3D coord, QVector3D couleur){

    for(int i = 0; i < 3 ; i++)
        vertices.push_back(coord[i]);
    for(int i = 0; i < 3 ; i++)
        colors.push_back(couleur[i]);
}
void gl_point::createGlObject(){

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;

    QVector3D color = colr;
    double haut = 0;
    int aCote = 0;

    std::cout << "nombre de pos : " << posInit.size() << std::endl;

    for(int i = 0; i < posInit.size(); i++){
        for(int j = 0; j < posInit[i].size(); j++){

        color = colr;
        color[2] = posInit[i][j][1]/25;
        color[1] -= posInit[i][j][1]/25;
        QVector3D coord(0,0,0);

        if(j==0 || posInit[i][j][1] != posInit[i][j-1][1]){
        //face du bas
            if(j-1 < 0)
                aCote = j;
            else
                aCote = j-1;

            for(int k = 0; posInit[i][j][1] - 2*hauteur*k != posInit[i][aCote][1] && posInit[i][j][1] - 2*hauteur*k > 0; k++){
                haut = 2*hauteur * k;
                color = colr;
                color[2] = (posInit[i][j][1]- haut)/25;
                color[1] -= (posInit[i][j][1]- haut)/25;
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, colors, coord, color);
            }
         }


        if(j == posInit[i].size()-1 || posInit[i][j][1] != posInit[i][j+1][1]){
            //face du haut
            if(j+1 >= posInit[i].size())
                aCote = j;
            else
                aCote = j+1;

            for(int k = 0; posInit[i][j][1] - 2*hauteur*k != posInit[i][aCote][1] && posInit[i][j][1] - 2*hauteur*k > 0; k++){
                haut = 2*hauteur * k;
                color = colr;
                color[2] = (posInit[i][j][1]- haut)/25;
                color[1] -= (posInit[i][j][1]- haut)/25;
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, colors, coord, color);
            }
        }

        if(i == 0 || posInit[i][j][1] != posInit[i-1][j][1]){
            //face du gauche
            if(i-1 < 0)
                aCote = i;
            else
                aCote = i-1;

            for(int k = 0; posInit[i][j][1] - 2*hauteur*k != posInit[aCote][j][1] && posInit[i][j][1] - 2*hauteur*k > 0; k++){
                haut = 2*hauteur * k;
                color = colr;
                color[2] = (posInit[i][j][1]- haut)/25;
                color[1] -= (posInit[i][j][1]- haut)/25;
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur- haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur- haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, colors, coord, color);
            }
        }


        if(i == posInit.size()-1 || posInit[i][j][1] != posInit[i+1][j][1]){
            //face du droite

            if(i+1 >= posInit.size())
                aCote = i;
            else
                aCote = i+1;

            for(int k = 0; posInit[i][j][1] - 2*hauteur*k != posInit[aCote][j][1] && posInit[i][j][1] - 2*hauteur*k > 0; k++){
                haut = 2*hauteur * k;
                color = colr;
                color[2] = (posInit[i][j][1]- haut)/25;
                color[1] -= (posInit[i][j][1]- haut)/25;
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur - haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur - haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, colors, coord, color);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, colors, coord, color);
            }
        }

        color = colr;
        color[2] = (posInit[i][j][1])/25;
        color[1] -= (posInit[i][j][1])/25;

        //face du devant
        coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur, posInit[i][j][2] + hauteur);
        createPoint(vertices, colors, coord, color);
        coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur, posInit[i][j][2] - hauteur);
        createPoint(vertices, colors, coord, color);
        coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur, posInit[i][j][2] - hauteur);
        createPoint(vertices, colors, coord, color);
        coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur, posInit[i][j][2] + hauteur);
        createPoint(vertices, colors, coord, color);

       /* //face du derriere
        coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur, posInit[i][j][2] + hauteur);
        createPoint(vertices, colors, coord, color);
        coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur, posInit[i][j][2] + hauteur);
        createPoint(vertices, colors, coord, color);
        coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur, posInit[i][j][2] - hauteur);
        createPoint(vertices, colors, coord, color);
        coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur, posInit[i][j][2] - hauteur);
        createPoint(vertices, colors, coord, color);*/

        }}
    std::cout << "fini" << std::endl;
    vertData.clear();

    for (int i = 0; i < vertices.size()/3; ++i) {
        // coordonnées sommets
        for (int j = 0; j < 3; j++)
            vertData.append(vertices[i*3+j]);
        // couleurs sommets
        for (int j = 0; j < 3; j++)
            vertData.append(colors[i*3+j]);
    }
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

    nombreTotal = vertices.size()/3;
}


void gl_point::display(QOpenGLShaderProgram &m_program){

    m_vbo.bind();
    m_program.setAttributeBuffer("posAttr",
        GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));
    m_program.setAttributeBuffer("colAttr",
        GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));
    m_program.enableAttributeArray("posAttr");
    m_program.enableAttributeArray("colAttr");
    if(displayIt)
        glDrawArrays(type, 0, nombreTotal);

    m_program.disableAttributeArray("posAttr");
    m_program.disableAttributeArray("colAttr");
    m_vbo.release();
}


void gl_point::tearGLObjects()
{
    m_vbo.destroy();
}
