#include "MainWindow.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QVBoxLayout>

#include "CardLineEdit.h"
#include "CardContainer.h"

MainWindow::MainWindow()
{
    cardContainer = new CardContainer;

    create_layout();
}

MainWindow::~MainWindow()
{
}

void MainWindow::create_layout() {
    /* Set Window */
    setWindowTitle("Flash Card");
    setMinimumSize(1024,768);

    /* Create Central Widget */
    QWidget* centralWidget = new QWidget;

    QVBoxLayout* mainVLayout = new QVBoxLayout;

    /* Status Bar */
    QGroupBox* statusBox = new QGroupBox("Status");

    statusBox->setLayout(create_status_bar());
    statusBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    /* Vocabulary */
    QGroupBox* vocabBox = new QGroupBox("Vocabulary");

    vocabBox->setLayout(create_card_overview());
    vocabBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    /* Put everything together */
    mainVLayout->addWidget(statusBox);
    mainVLayout->addWidget(vocabBox);

    centralWidget->setLayout(mainVLayout);

    centralWidget->setLayout(mainVLayout);
    setCentralWidget(centralWidget);
}

QVBoxLayout* MainWindow::create_status_bar()
{
    QVBoxLayout* mainVLayout = new QVBoxLayout;

    /* Load, Store, Learn */
    QHBoxLayout* buttonHLayout = new QHBoxLayout;

    QPushButton* loadButton = new QPushButton("Load");
    connect(loadButton, SIGNAL(clicked()), cardContainer, SLOT(load_cards()));
    buttonHLayout->addWidget(loadButton);

    QPushButton* storeButton = new QPushButton("Store");
    connect(storeButton, SIGNAL(clicked()), cardContainer, SLOT(store_cards()));
    buttonHLayout->addWidget(storeButton);

    QPushButton* trainButton = new QPushButton("Train");
    //connect(...) to card container
    buttonHLayout->addWidget(trainButton);

    mainVLayout->addLayout(buttonHLayout);

    /* Filename, Total Cards, Learned Cards */
    QLineEdit* filenameLine = new QLineEdit("Filename");
    filenameLine->setDisabled(true);
    mainVLayout->addWidget(filenameLine);
    //connect(..)

    QLineEdit* cardsLine = new QLineEdit("0 / 10");
    cardsLine->setDisabled(true);
    mainVLayout->addWidget(cardsLine);
    //connect(..)

    return mainVLayout;
}

QHBoxLayout* MainWindow::create_card_overview()
{
    QHBoxLayout* mainHLayout = new QHBoxLayout;

    /* Left half overview */
    cardContainer = new CardContainer;
    // Move model to card container
    QStandardItemModel* cardModel = new QStandardItemModel;

    cardContainer->setModel(cardModel);

    mainHLayout->addWidget(cardContainer);

    /* Right half detail */
    QFormLayout* cardDetails = new QFormLayout;

    CardLineEdit* questionLine = new CardLineEdit("Empty");
    cardDetails->addRow(new QLabel("Question: "), questionLine);
    //connect(cardContainer, SIGNAL(itemChanged(FlashCard*)), questionLine, SLOT(setItem(FlashCard*)));

    QLineEdit* answerLine = new QLineEdit("Empty");
    cardDetails->addRow(new QLabel("Answer: "), answerLine);
    //connect(..)

    mainHLayout->addLayout(cardDetails);

    return mainHLayout;
}
