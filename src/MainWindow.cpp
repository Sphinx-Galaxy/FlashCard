#include "MainWindow.h"

#include <QGroupBox>
#include <QVBoxLayout>

MainWindow::MainWindow()
{
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
    QHBoxLayout* statusHLayout = new QHBoxLayout;
    QGroupBox* statusBox = new QGroupBox("Status");

    // Button: Start Learning, Load Dataset, Save Dataset

    // Lines: Total Words, Learning Words (today)

    statusBox->setLayout(statusHLayout);

    /* Vocabulary */
    QHBoxLayout* vocabHLayout = new QHBoxLayout;
    QGroupBox* vocabBox = new QGroupBox("Vocabulary");

    // Left Half: Wordlist

    // Right Half: Edit Words

    vocabBox->setLayout(vocabHLayout);

    /* Put everything together */
    mainVLayout->addWidget(statusBox);
    mainVLayout->addWidget(vocabBox);

    centralWidget->setLayout(mainVLayout);

    centralWidget->setLayout(mainVLayout);
    setCentralWidget(centralWidget);
}
