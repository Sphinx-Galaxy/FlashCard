#include "TrainDialog.h"

#include "FlashCard.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>

TrainDialog::TrainDialog(FlashCard* flashcard, bool reversed)
    : flashcard(flashcard), reversed(reversed)
{
    create_layout();
}

TrainDialog::~TrainDialog()
{
    delete answerLine;
    delete questionLine;
}

void TrainDialog::create_layout()
{
    QFormLayout * formLayout = new QFormLayout;

    // Question
    questionLine = new QLineEdit;
    questionLine->setText(reversed ? flashcard->get_answer() : flashcard->get_question());
    questionLine->setDisabled(true);
    formLayout->addRow("Question", questionLine);

    // Answer
    answerLine = new QLineEdit;
    formLayout->addRow("Question", answerLine);

    QHBoxLayout* hlayout = new QHBoxLayout;

    QPushButton* okButton = new QPushButton("Ok");
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(check_answer()));
    hlayout->addWidget(okButton);

    QPushButton* cancleButton = new QPushButton("Cancel");
    connect(cancleButton, SIGNAL(clicked()), this, SLOT(reject()));
    hlayout->addWidget(cancleButton);

    QVBoxLayout* vlayout = new QVBoxLayout(this);
    vlayout->addLayout(formLayout);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);
}

void TrainDialog::check_answer()
{
    if(reversed)
    {
        show_check_info(flashcard->check_question(answerLine->text()));
    }
    else
    {
        show_check_info(flashcard->check_answer(answerLine->text()));
    }
}

void TrainDialog::show_check_info(bool ok)
{
    QMessageBox info(this);

    if(ok)
    {
        info.setText("Correct");
    }
    else
    {
        if(reversed)
        {
            info.setText("Wrong! <" + flashcard->get_question() + ">");
        }
        else
        {
            info.setText("Wrong! <" + flashcard->get_answer() + ">");
        }
    }

    info.exec();
}
