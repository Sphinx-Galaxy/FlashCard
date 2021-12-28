#include "CardContainer.h"

#include <stdlib.h>
#include <time.h>

CardContainer::CardContainer()
{
//    string card_content = "";
//    size_t pos = 0;

//    for(size_t i = 0; i < content.size(); ++i) {
//        card_content = content.substr(content.find("Card", pos), content.find("Card", pos+1));

//#ifdef DEBUG
//        cout << "Generating card content... Found Keyword \"Card\" " << (content.find("Card") == string::npos ? "nowhere" : "at " + to_string(content.find("Card")));
//#endif // DEBUG

//        pos = content.find("Card", pos+1);

//        i = pos;
//        flash_stack.push_back(new FlashCard(card_content));

//        if(pos == string::npos)
//            break;
//    }

    srand(time(NULL));

    connect(this, SIGNAL(clicked(const QModelIndex)), this, SLOT(cardClicked(const QModelIndex)));
}

CardContainer::~CardContainer() {
    for(size_t i = 0; i < flashStack.size(); ++i)
        delete flashStack.at(i);
}

//QString CardContainer::get_content() const  {
//    string result = "";

//    for(size_t i = 0; i < flash_stack.size(); ++i) {
//        result += "Card\n";
//        result += flash_stack[i]->get_content() + "\n";
//    }

//    return result;
//}

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

}

void CardContainer::store_cards()
{

}
