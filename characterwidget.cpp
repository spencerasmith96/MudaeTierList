#include "characterwidget.h"
#include "ui_characterwidget.h"
#include <QNetworkReply>
#include <QUrl>

CharacterWidget::CharacterWidget(QString name, QString series, QString imageurl, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::CharacterWidget)
{
    ui->setupUi(this);
    ui->characterName->setText(name);
    ui->seriesName->setText(series);

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &CharacterWidget::imageDownloadFinished);
    manager->get(QNetworkRequest(QUrl(imageurl)));
}

CharacterWidget::~CharacterWidget()
{
    delete ui;
}

void CharacterWidget::imageDownloadFinished(QNetworkReply *reply)
{
    QByteArray bytes = reply->readAll();
    QPixmap img;
    img.loadFromData(bytes);
    img = img.scaled(150, 150, Qt::AspectRatioMode::KeepAspectRatio);
    ui->imageLabel->setPixmap(img);
    manager->deleteLater();
    reply->deleteLater();
}
