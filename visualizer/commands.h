#ifndef COMMANDS_H
#define COMMANDS_H

#include "ui_commands.h"

/**
 * @brief The Commands class
 */
class Commands : public QDialog, private Ui::Commands
{
    Q_OBJECT

    public:
        /**
         * @brief Commands
         * @param parent
         */
        explicit Commands(QWidget *parent = 0);
};

#endif // COMMANDS_H
