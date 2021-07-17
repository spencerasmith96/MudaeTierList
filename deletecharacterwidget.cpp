#include "deletecharacterwidget.h"
#include "ui_deletecharacterwidget.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <iostream>

DeleteCharacterWidget::DeleteCharacterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeleteCharacterWidget)
{
    ui->setupUi(this);
}

DeleteCharacterWidget::~DeleteCharacterWidget()
{
    delete ui;
}

void DeleteCharacterWidget::dragEnterEvent(QDragEnterEvent *event)
{
    std::cout << "drag detected" << std::endl;
    if (event->mimeData()->hasFormat("application/character")) {
         setStyleSheet(highlightedStyle);
        event->accept();
    } else {
        event->ignore();
    }
}

void DeleteCharacterWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    setStyleSheet(normalStyle);
    event->accept();
}

void DeleteCharacterWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/character")) {
        QByteArray itemData = event->mimeData()->data("application/character");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        int rowid;
        dataStream >> rowid;

        emit deleteCharacter(rowid);
        setStyleSheet(normalStyle);
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}
