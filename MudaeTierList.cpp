#include "mudaetierlist.h"
#include "ui_MudaeTierList.h"
#include "characterwidget.h"
#include "characterdata.h"
#include "addcharactersdialog.h"
#include "deletecharacterwidget.h"
#include <iostream>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

MudaeTierList::MudaeTierList(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MudaeTierList)
{
    ui->setupUi(this);

    if(!QSqlDatabase::drivers().contains("QSQLITE")){
        std::cout << "install driver plz" << std::endl;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/Mudae.db";
    std::cout << dbPath.toStdString() << std::endl;
    db.setDatabaseName(dbPath);
    db.open();
    setAcceptDrops(true);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
    connect(ui->actionNew, &QAction::triggered, this, &MudaeTierList::onNewTierList);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MudaeTierList::onSaveAs);
    connect(ui->actionAddCharacters, &QAction::triggered, this, &MudaeTierList::onAddCharacters);
    connect(ui->actionOpen, &QAction::triggered, this, &MudaeTierList::onOpen);
    connect(ui->deleteCharacterWidget, &DeleteCharacterWidget::deleteCharacter, this, &MudaeTierList::onDeleteCharacter);

    onNewTierList();
}

MudaeTierList::~MudaeTierList()
{
    db.close();
    clearData();
    delete ui;
}

TierWidget* MudaeTierList::addTier(QString tierLabel, QString backgroundColor)
{
    TierWidget *newTier = new TierWidget(tierLabel, backgroundColor);
    tierWidgets.append(newTier);
    ui->tiersLayout->addWidget(newTier);
    return newTier;
}

void MudaeTierList::onButtonClicked()
{
    QString bestGirl = "Hifumin";
    addCharacter(bestGirl);
}

void MudaeTierList::onNewTierList()
{
    clearData();

    // Sets up initial tiers
    addTier("S", "Red");
    addTier("A", "Orange");
    addTier("B", "Yellow");
    addTier("C", "Green");
    addTier("D", "Purple");
    addTier("F", "Light Blue");
}

void MudaeTierList::onDropped(CharacterWidget *droppedCharacter)
{
    if(characterWidgets.contains(droppedCharacter)){
        characterWidgets.removeOne(droppedCharacter);
        delete droppedCharacter;
    }
}

void MudaeTierList::onSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Tier List"), "NewTierList", tr("Tier List (*.tl);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    QDataStream out(&file);
    out << tierWidgets.size();
    for(auto tier: tierWidgets){
        out << tier->getName() << tier->getColor() << tier->getCharacterNames();
    }
    QStringList unassignedCharacters;
    for(auto character: characterWidgets){
        unassignedCharacters.append(character->getName());
    }
    out << unassignedCharacters;
    file.close();
}

void MudaeTierList::onAddCharacters()
{
    AddCharactersDialog *newDialog = new AddCharactersDialog(this);
    newDialog->open();
    connect(newDialog, &AddCharactersDialog::accepted, this, &MudaeTierList::onAddCharactersAccepted);
}

void MudaeTierList::onAddCharactersAccepted(AddCharactersDialog *acceptedDialog)
{
    QStringList characterNames = acceptedDialog->getLines();
    QString notFoundCharacters;
    for(auto name: characterNames){
        if(!addCharacter(name)){
            notFoundCharacters.append(name + "\n");
        }
    }
    acceptedDialog->deleteLater();
    if(notFoundCharacters.length() > 0){
        QMessageBox::warning(this, tr("Characters not found in database:"), notFoundCharacters);
    }
}

void MudaeTierList::onOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save Tier List"), "", tr("Tier List (*.tl);;All Files (*)"));

    if(fileName.isEmpty()){
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(this, tr("Unable to open file"), file.errorString());
        return;
    }

    clearData();
    QDataStream in(&file);
    qsizetype tierCount;
    in >> tierCount;
    tierWidgets.reserve(tierCount);
    for(qsizetype tierIndex = 0; tierIndex < tierCount; ++tierIndex){
        QString name, color;
        QStringList characterNames;
        in >> name >> color >> characterNames;
        std::cout << tierIndex << name.toStdString() << std::endl;;
        TierWidget *newTier = addTier(name, color);
        int characterIndex = 0;
        for(QString& character: characterNames){
            std::cout << character.toStdString();
            CharacterData newData(character, db);
            if(newData.isValid()){
                if(characterIDs.find(newData.getid()) != characterIDs.end()){
                    continue;
                }
                characterIDs.emplace(newData.getid());
                CharacterWidget* newCharacter = newData.toWidget();
                newTier->addCharacter(newCharacter, characterIndex++);
            }
        }
    }

    QStringList unassignedCharacters;
    in >> unassignedCharacters;
    for(auto character: unassignedCharacters){
        addCharacter(character);
    }

    file.close();
}

void MudaeTierList::onDeleteCharacter(int id)
{
    characterIDs.erase(id);
}

void MudaeTierList::clearData()
{
    // Clears characters
    for(auto character: characterWidgets){
        delete character;
    }
    characterWidgets.clear();

    // Clears tiers
    for(auto tier: tierWidgets){
        delete tier;
    }
    tierWidgets.clear();

    characterIDs.clear();
}

bool MudaeTierList::addCharacter(QString &characterName)
{
    CharacterData newData(characterName, db);
    if(newData.isValid()){
        if(characterIDs.find(newData.getid()) != characterIDs.end()){
            return true;
        }
        characterIDs.emplace(newData.getid());
        CharacterWidget* newCharacter = newData.toWidget();
        ui->unassignedCharactersLayout->addWidget(newCharacter);
        characterWidgets.append(newCharacter);
        connect(newCharacter, &CharacterWidget::dropped, this, &MudaeTierList::onDropped);
        return true;
    }
    return false;
}

