#ifndef TIERWIDGET_H
#define TIERWIDGET_H

#include <QWidget>

namespace Ui {
class TierWidget;
}

class TierWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TierWidget(QString labelText = QString(), QString backgroundColor = QString(), QWidget *parent = nullptr);
    ~TierWidget();

private:
    Ui::TierWidget *ui;
};

#endif // TIERWIDGET_H
