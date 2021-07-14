#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QFrame>
#include <QNetworkAccessManager>
#include <QMouseEvent>

namespace Ui {
class CharacterWidget;
}

class CharacterWidget : public QFrame
{
    Q_OBJECT

public:
    explicit CharacterWidget(QString name, QString series, QString imageurl, QPixmap &imagePixmap, QWidget *parent = nullptr);
    explicit CharacterWidget(QString name, QString series, QString imageurl, QWidget *parent = nullptr);
    ~CharacterWidget();

    QString getName();
    void mousePressEvent(QMouseEvent *event);

signals:
    void dropped(CharacterWidget *me);

public slots:
    void imageDownloadFinished(QNetworkReply* reply);

private:
    Ui::CharacterWidget *ui;
    QNetworkAccessManager *manager;
    void setNameLabel(QString name);
    void setSeriesLabel(QString series);
};

#endif // CHARACTERWIDGET_H
