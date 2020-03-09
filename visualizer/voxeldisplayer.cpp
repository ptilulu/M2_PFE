#include "voxeldisplayer.h"

VoxelDisplayer::VoxelDisplayer(std::vector<std::vector<QVector3D>> pos, double h, bool isDisplay)
{
    posInit = pos;
    hauteur = h;
    displayIt = isDisplay;
}

void VoxelDisplayer::setPositionPoint(QVector3D pos){
    createGlObject();
}

void VoxelDisplayer::setDisplay(bool mode){
    displayIt = mode;
}

/* OPENGL */

void VoxelDisplayer::createPoint(std::vector<GLfloat> &vertices, QVector3D coord){
    for(int i = 0; i < 3 ; i++) vertices.push_back(coord[i]);
}
void VoxelDisplayer::createGlObject(){

    std::vector<GLfloat> vertices;

    double haut = 0;
    int aCote = 0;

    std::cout << "nombre de pos : " << posInit.size() << std::endl;

    for(int i = 0; i < posInit.size(); i++){
        for(int j = 0; j < posInit[i].size(); j++){

        QVector3D coord(0,0,0);

        if(j==0 || posInit[i][j][1] != posInit[i][j-1][1]){
        //face du bas
            if(j-1 < 0)
                aCote = j;
            else
                aCote = j-1;

            for(int k = 0; posInit[i][j][1] - 2*hauteur*k != posInit[i][aCote][1] && posInit[i][j][1] - 2*hauteur*k > 0; k++){
                haut = 2*hauteur * k;
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, coord);
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
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, coord);
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
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur- haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur- haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur- haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, coord);
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
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur - haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur - haut, posInit[i][j][2] - hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, coord);
                coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur - haut, posInit[i][j][2] + hauteur);
                createPoint(vertices, coord);
            }
        }

        //face du devant
        coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur, posInit[i][j][2] + hauteur);
        createPoint(vertices, coord);
        coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] + hauteur, posInit[i][j][2] - hauteur);
        createPoint(vertices, coord);
        coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur, posInit[i][j][2] - hauteur);
        createPoint(vertices, coord);
        coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] + hauteur, posInit[i][j][2] + hauteur);
        createPoint(vertices, coord);

        //face du derriere
        /*
        coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur, posInit[i][j][2] + hauteur);
        createPoint(vertices, colors, coord, color);
        coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur, posInit[i][j][2] + hauteur);
        createPoint(vertices, colors, coord, color);
        coord = QVector3D(posInit[i][j][0] + hauteur, posInit[i][j][1] - hauteur, posInit[i][j][2] - hauteur);
        createPoint(vertices, colors, coord, color);
        coord = QVector3D(posInit[i][j][0] - hauteur, posInit[i][j][1] - hauteur, posInit[i][j][2] - hauteur);
        createPoint(vertices, colors, coord, color);
        */

        }
    }
    std::cout << "fini" << std::endl;
    vertData.clear();

    for (int i = 0; i < vertices.size()/3; ++i) {
        // coordonnées sommets
        for (int j = 0; j < 3; j++)
            vertData.append(vertices[i*3+j]);
    }
    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(vertData.constData(), vertData.count() * sizeof(GLfloat));

    nombreTotal = vertices.size()/3;
}


void VoxelDisplayer::display(QOpenGLShaderProgram &m_program){

    m_vbo.bind();

    if(displayIt) glDrawArrays(type, 0, nombreTotal);

    m_vbo.release();
}


void VoxelDisplayer::tearGLObjects()
{
    m_vbo.destroy();
}
