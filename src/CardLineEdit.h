#ifndef CARDLINEEDIT_H
#define CARDLINEEDIT_H

class FlashCard;

#include <QLineEdit>
#include <QWidget>

class CardLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    CardLineEdit(const QString& title);

public slots:
    void setItem(FlashCard* item);
};

#endif // CARDLINEEDIT_H
