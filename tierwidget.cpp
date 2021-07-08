#include "tierwidget.h"
#include "ui_tierwidget.h"

TierWidget::TierWidget(QString labelText, QString backgroundColor, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TierWidget)
{
    ui->setupUi(this);
    QString styleSheet = "background: " + backgroundColor;
    ui->tierLabel->setStyleSheet(styleSheet);
    ui->tierLabel->setText(labelText);
}

TierWidget::~TierWidget()
{
    delete ui;
}
