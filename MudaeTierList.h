#ifndef MUDAETIERLIST_H
#define MUDAETIERLIST_H

#include <QMainWindow>
#include <vector>
#include <QLabel>
#include "characterwidget.h"
#include "tierwidget.h"
#include "addcharactersdialog.h"
#include <QtSql>
#include <QDropEvent>
#include <unordered_set>

QT_BEGIN_NAMESPACE
namespace Ui { class MudaeTierList; }
QT_END_NAMESPACE

class MudaeTierList : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MudaeTierList *ui;
    QVector<CharacterWidget*> characterWidgets;
    QVector<TierWidget*> tierWidgets;
    QSqlDatabase db;
    std::unordered_set<int> characterIDs;

public:
    MudaeTierList(QWidget *parent = nullptr);
    ~MudaeTierList();

    TierWidget* addTier(QString tierLabel = QString(), QString backgroundColor = QString());

public slots:
    void onButtonClicked();
    void onNewTierList();
    void onDropped(CharacterWidget *droppedCharacter);
    void onSaveAs();
    void onAddCharacters();
    void onAddCharactersAccepted(AddCharactersDialog *acceptedDialog);
    void onOpen();
    void onDeleteCharacter(int id);

private:
    void clearData();
    bool addCharacter(QString &characterName);

};
#endif // MUDAETIERLIST_H
