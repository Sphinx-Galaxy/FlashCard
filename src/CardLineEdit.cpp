#include "CardLineEdit.h"

#include "FlashCard.h"

CardLineEdit::CardLineEdit(const QString& title)
    : QLineEdit(title)
{

}

void CardLineEdit::setItem(FlashCard* item)
{
    qDebug("Got new item");
}
