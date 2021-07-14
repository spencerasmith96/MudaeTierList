#include "characterwidget.h"
#include "ui_characterwidget.h"
#include <QNetworkReply>
#include <QUrl>
#include <QIcon>
#include <QDrag>
#include <QMimeData>
#include <iostream>

CharacterWidget::CharacterWidget(QString name, QString series, QString imageurl, QPixmap& imagePixmap, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CharacterWidget)
{
    ui->setupUi(this);

    setNameLabel(name);
    setSeriesLabel(series);
    ui->imageLabel->setToolTip(imageurl);
    ui->imageLabel->setPixmap(imagePixmap);
}

CharacterWidget::CharacterWidget(QString name, QString series, QString imageurl, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CharacterWidget)
{
    hide();
    ui->setupUi(this);
    setNameLabel(name);
    setSeriesLabel(series);
    ui->imageLabel->setToolTip(imageurl);

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &CharacterWidget::imageDownloadFinished);
    manager->get(QNetworkRequest(QUrl(imageurl)));
}

CharacterWidget::~CharacterWidget()
{
    delete ui;
}

QString CharacterWidget::getName()
{
    return ui->characterName->text();
}

void CharacterWidget::imageDownloadFinished(QNetworkReply *reply)
{
    QPixmap img;
    if(reply->error() == QNetworkReply::NoError){
        QByteArray bytes = reply->readAll();
        img.loadFromData(bytes);
    }
    else{
        img.load(":/qresource/no-image");
    }
    img = img.scaled(ui->imageLabel->maximumSize(), Qt::AspectRatioMode::KeepAspectRatio);
    ui->imageLabel->setPixmap(img);

    manager->deleteLater();
    reply->deleteLater();
    show();
}

void CharacterWidget::setNameLabel(QString name)
{
    ui->characterName->setText(name);
    ui->characterName->setToolTip(name);
}

void CharacterWidget::setSeriesLabel(QString series)
{
    ui->seriesName->setText(series);
    ui->seriesName->setToolTip(series);
}

void CharacterWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QDrag *drag = new QDrag(this);

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        dataStream <<  ui->characterName->text() << ui->seriesName->text() << ui->imageLabel->toolTip() << ui->imageLabel->pixmap(Qt::ReturnByValueConstant());

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/character", itemData);

        drag->setMimeData(mimeData);
        drag->setPixmap(ui->imageLabel->pixmap());
        hide();

        Qt::DropAction dropAction = drag->exec(Qt::MoveAction);
        if(dropAction == Qt::MoveAction){
            emit dropped(this);
        }
        else{
            show();
        }
    }
}
