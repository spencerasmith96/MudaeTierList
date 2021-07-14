#ifndef ADDCHARACTERSDIALOG_H
#define ADDCHARACTERSDIALOG_H

#include <QDialog>

namespace Ui {
class AddCharactersDialog;
}

class AddCharactersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCharactersDialog(QWidget *parent = nullptr);
    ~AddCharactersDialog();

    QStringList getLines();

public slots:
    void onAccepted();

signals:
    void accepted(AddCharactersDialog *acceptedDialog);


private:
    Ui::AddCharactersDialog *ui;
};

#endif // ADDCHARACTERSDIALOG_H
