#ifndef CONTAINER_H
#define CONTAINER_H

/*
 * Author: Mattis Jaksch
 *
 */

#include "FlashCard.h"

#include <QListView>
#include <QString>
#include <QVector>

class CardContainer : public QListView
{
Q_OBJECT

public:
    CardContainer();
    virtual ~CardContainer();

    FlashCard* get_active_card() const
    {
        return activeCard;
    }

    int get_flashstack_size() const
    {
        return flashStack.size();
    }

    int get_learnable_cards() const;

    void set_filename(const QString& filename);

    FlashCard* draw_card();

    bool is_done() const;

public slots:
    void load_cards();
    void store_cards();

    void save_card();

    void card_clicked(const QModelIndex index);

signals:
    void card_selected(FlashCard*);


private:
    QString filename;
    QVector<FlashCard*> flashStack;
    FlashCard* activeCard;

    QStandardItemModel* cardModel;
};

#endif // CONTAINER_H
