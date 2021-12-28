#include "src/MainWindow.h"

#include "src/FlashCard.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

void test()
{
    FlashCard myCard1("Card \nQuestion = Goodbye \nAnswer = Tschüss; Wiedersehen \nLevel = 0 \nDate = 0");

    FlashCard myCard2("Airport", {"Flughafen", "Flugzeug"}, 0, 0);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "FlashCard_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }


    test();

    MainWindow w;
    w.show();


    return a.exec();
}
