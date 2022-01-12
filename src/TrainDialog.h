#ifndef TRAINDIALOG_H
#define TRAINDIALOG_H

class FlashCard;

class QLineEdit;

#include <QDialog>

class TrainDialog : public QDialog
{
    Q_OBJECT
public:
    TrainDialog(FlashCard* flashcard, bool reversed);
    virtual ~TrainDialog();

    void create_layout();

private slots:
    void check_answer();

private:
    FlashCard* flashcard;
    bool reversed;

    QLineEdit* answerLine;
    QLineEdit* questionLine;

    void show_check_info(bool ok);
};

#endif // TRAINDIALOG_H
