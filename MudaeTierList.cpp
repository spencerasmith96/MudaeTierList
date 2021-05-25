#include "mudaetierlist.h"
#include "ui_mudaetierlist.h"

MudaeTierList::MudaeTierList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MudaeTierList)
{
    ui->setupUi(this);
}

MudaeTierList::~MudaeTierList()
{
    delete ui;
}

