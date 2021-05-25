#ifndef MUDAETIERLIST_H
#define MUDAETIERLIST_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MudaeTierList; }
QT_END_NAMESPACE

class MudaeTierList : public QMainWindow
{
    Q_OBJECT

public:
    MudaeTierList(QWidget *parent = nullptr);
    ~MudaeTierList();

private:
    Ui::MudaeTierList *ui;
};
#endif // MUDAETIERLIST_H
