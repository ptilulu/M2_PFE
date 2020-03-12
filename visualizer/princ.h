#ifndef PRINC_H
#define PRINC_H

#include "dem.h"
#include "commands.h"
#include "ui_princ.h"

/**
 * @brief La classe Princ représentant la fenêtre principale de l'interface
 */
class Princ : public QMainWindow, private Ui::Princ
{
    Q_OBJECT

    public:
        /**
         * @brief Princ
         * @param parent
         */
        explicit Princ(QWidget *parent = nullptr);

        /**
         * @brief openFile
         */
        void openFile();

    private slots:
        /**
         * @brief on_actionQuitter_triggered Appellée lors du déclenchement de Fichier => Quitter
         */
        void on_actionQuitter_triggered();

        /**
         * @brief on_exportOBJAction_triggered Appellée lors du déclenchement de Fichier => Exporter l'OBJ
         */
        void on_exportOBJAction_triggered();

        void on_actionCommandes_triggered();

        void on_actionVoxel_triggered();

        void on_actionTerrain_triggered();

private:
        /**
        * @brief dem Le dernier DEM ouvert dans l'interface
        */
        DEM* dem = nullptr;

        /**
         * @brief commands
         */
        Commands* commands = nullptr;
};

#endif // PRINC_H
