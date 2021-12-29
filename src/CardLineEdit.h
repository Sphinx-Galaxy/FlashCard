#ifndef CARDLINEEDIT_H
#define CARDLINEEDIT_H

#include "FlashCard.h"

#include <QLineEdit>
#include <QWidget>

class CardLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CardLineEdit(const QString& title,
                 QString (FlashCard::*get_text)(void) const,
                 void (FlashCard::*set_text)(const QString& text));

public slots:
    void set_card(FlashCard* card);
    void save_result();

private:
    FlashCard* card;

    QString (FlashCard::*get_text)(void) const;
    void (FlashCard::*set_text)(const QString& text);
};

#endif // CARDLINEEDIT_H
