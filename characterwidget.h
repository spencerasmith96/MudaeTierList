#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QFrame>
#include <QNetworkAccessManager>

namespace Ui {
class CharacterWidget;
}

class CharacterWidget : public QFrame
{
    Q_OBJECT

public:
    explicit CharacterWidget(QString name, QString series, QString imageurl, QWidget *parent = nullptr);
    ~CharacterWidget();

public slots:
    void imageDownloadFinished(QNetworkReply* reply);

private:
    Ui::CharacterWidget *ui;
    QNetworkAccessManager *manager;
};

#endif // CHARACTERWIDGET_H
