#include "characterdata.h"
#include <QSqlQuery>
#include <iostream>

CharacterData::CharacterData(QString characterName, QSqlDatabase& db)
{
    name = characterName;

    QSqlQuery query(db);
    query.prepare("SELECT characterid FROM aliases WHERE name=(?)");
    query.addBindValue(characterName);
    query.exec();

    if(query.next()){
        rowid = query.value(0).toInt();
    }
    else{
        // error has occurred, e.g. name doesn't exist in database
        series = QString();
        imageurl = QString();
        valid = false;
        return;
    }

    query.prepare("SELECT series, imageurl FROM characters WHERE rowid=(?)");
    query.addBindValue(rowid);
    query.exec();
    if(query.next()){
        series = query.value(0).toString();
        imageurl = query.value(1).toString();
    }
    else{
        // error has occurred, e.g. rowid doesn't exist in database. This shouldn't happen.
        series = QString();
        imageurl = QString();
        valid = false;
        return;
    }
}

bool CharacterData::isValid()
{
    return valid;
}

CharacterWidget *CharacterData::toWidget()
{
    return new CharacterWidget(name, series, imageurl);
}

uint CharacterData::getid()
{
    return rowid;
}
