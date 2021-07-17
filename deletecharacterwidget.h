#ifndef DELETECHARACTERWIDGET_H
#define DELETECHARACTERWIDGET_H

#include <QWidget>

namespace Ui {
class DeleteCharacterWidget;
}

class DeleteCharacterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DeleteCharacterWidget(QWidget *parent = nullptr);
    ~DeleteCharacterWidget();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dropEvent(QDropEvent *event) override;

signals:
    void deleteCharacter(int characterID);

private:
    QString normalStyle = "background: palette(window)";
    QString highlightedStyle = "background: gray";
    Ui::DeleteCharacterWidget *ui;
};

#endif // DELETECHARACTERWIDGET_H
