#include "commands.h"

/**
 * @brief Commands::Commands
 * @param parent
 */
Commands::Commands(QWidget *parent) : QDialog(parent)
{
    setupUi(this);
    this->setWindowTitle("Commandes");

    Ui::Commands::A->setPixmap((QPixmap(":/icons/A-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::Z->setPixmap((QPixmap(":/icons/Z-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::E->setPixmap((QPixmap(":/icons/E-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::Q->setPixmap((QPixmap(":/icons/Q-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::S->setPixmap((QPixmap(":/icons/S-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::D->setPixmap((QPixmap(":/icons/D-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::AQ_explanation->setText("Rotation du terrain sur l'axe x");
    Ui::Commands::SZ_explanation->setText("Rotation du terrain sur l'axe y");
    Ui::Commands::ED_explanation->setText("Rotation du terrain sur l'axe z");

    Ui::Commands::Key4->setPixmap((QPixmap(":/icons/4-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::Key5->setPixmap((QPixmap(":/icons/5-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::Key6->setPixmap((QPixmap(":/icons/6-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::Key7->setPixmap((QPixmap(":/icons/7-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::Key8->setPixmap((QPixmap(":/icons/8-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::Key9->setPixmap((QPixmap(":/icons/9-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::Key47_explanation->setText("Rotation de la lumière sur l'axe x");
    Ui::Commands::Key58_explanation->setText("Rotation de la lumière sur l'axe y");
    Ui::Commands::Key69_explanation->setText("Rotation de la lumière sur l'axe z");

    Ui::Commands::Minus->setPixmap((QPixmap(":/icons/minus-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::Plus->setPixmap((QPixmap(":/icons/plus-icon.png")).scaled(48, 48, Qt::KeepAspectRatio));
    Ui::Commands::MinusPlus_explanation->setText("Modifier la valeur d'ajustement");
}
