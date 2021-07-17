#include "characterwidget.h"
#include "ui_characterwidget.h"
#include <QNetworkReply>
#include <QUrl>
#include <QIcon>
#include <QDrag>
#include <QMimeData>
#include <iostream>
#include <QTextLine>

CharacterWidget::CharacterWidget(int rowid, QString name, QString series, QString imageurl, QPixmap& imagePixmap, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CharacterWidget)
{
    ui->setupUi(this);

    id = rowid;
    setNameLabel(name);
    setSeriesLabel(series);
    ui->imageLabel->setToolTip(imageurl);
    ui->imageLabel->setPixmap(imagePixmap);
}

CharacterWidget::CharacterWidget(int rowid, QString name, QString series, QString imageurl, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CharacterWidget)
{
    hide();
    id = rowid;
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
    return ui->characterName->toolTip();
}

int CharacterWidget::getID()
{
    return id;
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
    QFontMetrics fontMetrics(ui->characterName->font());
    QString elidedName = fontMetrics.elidedText(name, Qt::ElideRight, width());

    ui->characterName->setText(elidedName);
    ui->characterName->setToolTip(name);
}

void CharacterWidget::setSeriesLabel(QString series)
{
    QFontMetrics fontMetrics(ui->seriesName->font());

    int width = ui->seriesName->width();
    int i = 1;
    int lastSpace = 0;
    for(; i < series.length(); ++i){
        if(fontMetrics.horizontalAdvance(series, i) > width){
            lastSpace == 0 ? --i : i = lastSpace + 1;
            break;
        }
        if(series[i] == ' '){
            lastSpace = i;
        }
    }
    QString elided = series.left(i);
    int remaining = series.length() - i;
    if(remaining > 0){
        QString bottomText = fontMetrics.elidedText(series.right(remaining), Qt::ElideRight, ui->seriesName->width());
        elided.append("\n" + bottomText);
    }


    ui->seriesName->setText(elided);
    ui->seriesName->setToolTip(series);
}

void CharacterWidget::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        QDrag *drag = new QDrag(this);

        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);

        dataStream << id <<  ui->characterName->toolTip() << ui->seriesName->toolTip() << ui->imageLabel->toolTip() << ui->imageLabel->pixmap(Qt::ReturnByValueConstant());

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
