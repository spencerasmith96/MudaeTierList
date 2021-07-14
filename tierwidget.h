#ifndef TIERWIDGET_H
#define TIERWIDGET_H

#include <QWidget>
#include "characterwidget.h"

namespace Ui {
class TierWidget;
}

class TierWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TierWidget(QString labelText = "", QString backgroundColor = "", QWidget *parent = nullptr);
    ~TierWidget();

    QString getName();
    QString getColor();
    QStringList getCharacterNames();
    QVector<CharacterWidget*> getCharacterWidgets();
    void addCharacter(CharacterWidget *newCharacter, int characterPos);

public slots:
    void onDrop(CharacterWidget *droppedCharacter);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private:
    Ui::TierWidget *ui;
    QString normalStyle = "background: palette(window)";
    QString highlightedStyle = "background: gray";
    QString color;
    QVector<CharacterWidget*> characterWidgets;
};

#endif // TIERWIDGET_H
