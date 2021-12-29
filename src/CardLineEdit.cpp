#include "CardLineEdit.h"

CardLineEdit::CardLineEdit(const QString& title,
                           QString (FlashCard::*get_text)(void) const,
                           void (FlashCard::*set_text)(const QString& text))
    : QLineEdit(title), get_text(get_text), set_text(set_text)
{
    connect(this, SIGNAL(editingFinished()), this, SLOT(save_result()));
}

void CardLineEdit::set_card(FlashCard* card)
{
    this->card = card;
    this->setText((this->card->*(get_text))());
}

void CardLineEdit::save_result()
{
    (card->*(set_text))(this->text());
}
