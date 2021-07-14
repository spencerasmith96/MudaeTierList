#ifndef CHARACTERDATA_H
#define CHARACTERDATA_H
#include <QString>
#include <QSqlDatabase>
#include "characterwidget.h"
class CharacterData
{
public:
    CharacterData(QString characterName, QSqlDatabase &db);
    bool isValid();
    CharacterWidget *toWidget();
    uint getid();

private:
    bool valid = true;
    uint rowid;
    QString name;
    QString series;
    QString imageurl;
};

#endif // CHARACTERDATA_H
