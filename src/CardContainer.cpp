#include "CardContainer.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

CardContainer::CardContainer()
{
    srand(time(NULL));

    connect(this, SIGNAL(clicked(const QModelIndex)), this, SLOT(cardClicked(const QModelIndex)));
}

CardContainer::~CardContainer() {
    for(size_t i = 0; i < flashStack.size(); ++i)
        delete flashStack.at(i);
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

void CardContainer::cardClicked(const QModelIndex index)
{
    qDebug("Column: " + (QString::number(index.column())).toLatin1() + " clicked");
    emit(flashStack.at(index.column()));
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
            card_content = "";
        }
    }
}

void CardContainer::store_cards()
{
    /* Show dialog */
    filename = QFileDialog::getSaveFileName(this, tr("Open File"), "./");

    /* Store content */
    if(!filename.isEmpty())
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
}
