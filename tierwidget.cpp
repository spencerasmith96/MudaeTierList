#include <QDragEnterEvent>
#include <QMimeData>
#include <iostream>
#include "characterwidget.h"
#include "tierwidget.h"
#include "ui_tierwidget.h"

TierWidget::TierWidget(QString labelText, QString backgroundColor, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TierWidget)
{
    ui->setupUi(this);

    color = backgroundColor;
    QString styleSheet = "background: " + backgroundColor;
    ui->tierLabel->setStyleSheet(styleSheet);
    ui->tierLabel->setText(labelText);
}

void TierWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("application/character")) {
        ui->characterArea->setStyleSheet(highlightedStyle);
        event->accept();
    } else {
        event->ignore();
    }
}

void TierWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    ui->characterArea->setStyleSheet(normalStyle);
    event->accept();
}

void TierWidget::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("application/character")) {
        QByteArray itemData = event->mimeData()->data("application/character");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        QString name, series, url;
        QPixmap imagePixmap;
        dataStream >> name >> series >> url >> imagePixmap;

        CharacterWidget* droppedCharcter = new CharacterWidget(name, series, url, imagePixmap);

        int characterPos = (event->position().x() - ui->characterArea->pos().x()) / droppedCharcter->size().width();

        characterPos = (characterPos < 0) ?  0 : characterPos;
        characterPos = (characterPos > characterWidgets.size()) ? characterWidgets.size() : characterPos;

        addCharacter(droppedCharcter, characterPos);

        event->acceptProposedAction();
        ui->characterArea->setStyleSheet(normalStyle);
    } else {
        event->ignore();
    }
}

TierWidget::~TierWidget()
{
    for(auto character: characterWidgets){
        delete character;
    }
    delete ui;
}

QString TierWidget::getName()
{
    return ui->tierLabel->text();
}

QString TierWidget::getColor()
{
    return color;
}

QStringList TierWidget::getCharacterNames()
{
    QStringList nameList(characterWidgets.size());
    for(auto character: characterWidgets){
        nameList.append(character->getName());
    }
    return nameList;
}

void TierWidget::onDrop(CharacterWidget *droppedCharacter)
{
    characterWidgets.removeOne(droppedCharacter);
    delete droppedCharacter;
}

QVector<CharacterWidget *> TierWidget::getCharacterWidgets()
{
    return characterWidgets;
}

void TierWidget::addCharacter(CharacterWidget *newCharacter, int characterPos)
{
    ui->characterAreaLayout->insertWidget(characterPos, newCharacter);
    //characterWidgets.append(newCharacter);
    characterWidgets.insert(characterPos, newCharacter);
    connect(newCharacter, &CharacterWidget::dropped, this, &TierWidget::onDrop);
}
