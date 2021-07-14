#include "addcharactersdialog.h"
#include "ui_addcharactersdialog.h"

AddCharactersDialog::AddCharactersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCharactersDialog)
{
    ui->setupUi(this);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &AddCharactersDialog::onAccepted);
}

AddCharactersDialog::~AddCharactersDialog()
{
    delete ui;
}

void AddCharactersDialog::onAccepted()
{
    emit accepted(this);
}

QStringList AddCharactersDialog::getLines()
{
    QString textData = ui->textEdit->toPlainText();

    return textData.split("\n");
}
