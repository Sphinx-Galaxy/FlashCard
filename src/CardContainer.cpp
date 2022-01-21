#include "CardContainer.h"

#include "TrainDialog.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

CardContainer::CardContainer()
{
    cardModel = new QStandardItemModel(this);

    srand(time(NULL));

    connect(this, SIGNAL(clicked(const QModelIndex)), this, SLOT(card_clicked(const QModelIndex)));

    setModel(cardModel);
}

CardContainer::~CardContainer()
{

}

FlashCard* CardContainer::draw_card()
{
    do {
        activeCard = flashStack.at(rand() % flashStack.size());
    } while(!activeCard->is_due());

    return activeCard;
}

int CardContainer::get_learnable_cards() const
{
    int cnt = 0;
    foreach(FlashCard* card, flashStack)
    {
        if(card->is_due())
            cnt += 1;
    }

    return cnt;
}

bool CardContainer::is_done() const
{
    foreach(FlashCard* card, flashStack)
    {
        if(card->is_due())
            return false;
    }

    return true;
}

void CardContainer::card_clicked(const QModelIndex index)
{
    activeCard = new FlashCard(flashStack.at(index.row())->get_content());

    emit card_selected(activeCard);
}

void CardContainer::save_card()
{
    flashStack.remove(this->currentIndex().row());
    flashStack.push_back(new FlashCard(activeCard->get_content()));

    cardModel->removeRow(this->currentIndex().row());
    cardModel->insertRow(this->currentIndex().row(), flashStack.last());

    delete activeCard;
}

void CardContainer::load_cards()
{
    /* Show dialog */
    filename = QFileDialog::getOpenFileName(this, tr("Open File"), "./");

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox error;
        error.setText("File cannot be opened");
        error.exec();
        return ;
    }

    /* Load content and cards */
    QString card_content = "";
    QTextStream in(&file);
    QString line;

    while(!in.atEnd()) {
        line = in.readLine();

        if(line != "\n" && line.size() > 0)
        {
            card_content += line + "\n";
        }

        if(card_content.size() > 0
                && card_content.contains("Question")
                && card_content.contains("Answer")
                && card_content.contains("Level")
                && card_content.contains("Date"))
        {
            flashStack.push_back(new FlashCard(card_content));
            cardModel->appendRow(flashStack.last());
            //connect(flashStack.last(), SIGNAL(data_changed()), cardModel, SLOT(update()));

            card_content = "";
        }
    }
}

void CardContainer::add_card()
{
    flashStack.push_back(new FlashCard("empty", {"empty"}));
    cardModel->appendRow(flashStack.last());
}


void CardContainer::store_cards()
{
    /* Show dialog */
    filename = QFileDialog::getSaveFileName(this, tr("Open File"), "./");

    /* Store content */
    if(!filename.isEmpty())
    {
        store_cards(filename);
    }
}

void CardContainer::store_cards(const QString& filename)
{
    QString content = "";

    foreach(FlashCard* card, flashStack)
    {
        content += "Card\n";
        content += card->get_content() + "\n";
    }

    //Save config
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox error;
        error.setText("File cannot be opened");
        error.exec();
        return ;
    }

    QTextStream in(&file);
    in << content;
    file.close();

}

void CardContainer::train()
{
    while(!is_done())
    {
        draw_card();

        TrainDialog train(activeCard,
            activeCard->get_level() < activeCard->get_level_list().size() ? false : true);

        if(train.exec() == 0)
        {
            return;
        }
    }

    store_cards(filename);
}
