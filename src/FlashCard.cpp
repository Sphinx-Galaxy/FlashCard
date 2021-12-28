#include "FlashCard.h"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <time.h>

QVector<int> FlashCard::level_list  = {0, 1, 3, 5, 7, 14};

FlashCard::FlashCard(const QString& content)
{
    QString row = "";
    int crow = 0;

    for(size_t pos = 0; pos < content.size(); ++pos) {
        if(content.indexOf("=", pos) == -1)
            break;

        pos = content.indexOf("=", pos) + 1;

        row = content.mid(pos, content.indexOf("\n", pos) - pos);

        decode_row(row, crow);
        crow++;
    }

    this->setText(question);
}

FlashCard::FlashCard(const QString& question, const QVector<QString>& answer, int level, long date)
    : question(question), answer(answer), level(level), date(date), QStandardItem(question) {

    if(date == 0)
        date = time(NULL);
}

FlashCard::~FlashCard() {}

QString FlashCard::get_content() const {
    QString result = "";

    result += "Question = " + question + "\n";
    result += "Answer = ";
    for(size_t i = 0; i < answer.size(); ++i)
        result += answer.at(i) + (i+1 < answer.size() ? "; " : "");
    result += "\n";

    result += "Level = " + QString::number(level) + "\n";
    result += "Date = " + QString::number(date) + "\n";

    return result;
}

bool FlashCard::check_answer(const QString &given_answer) {
    for(QVector<QString>::const_iterator it = answer.begin(); it != answer.end(); ++it) {
        if(given_answer.compare(*it) == 0) {
            increase_level();
            update_date();
            return true;
        }
    }

    clear_level();
    return false;
}

bool FlashCard::check_question(const QString &given_question) {
    if(given_question.compare(question) == 0) {
        increase_level();
        update_date();
        return true;
    }

    clear_level();
    return false;
}

QString FlashCard::escape_start_end(const QString &input) {
#ifdef DEBUG
    cout << "Escaping input: " << endl;
    cout << input << endl;
#endif // DEBUG

    QString result = "";
    size_t pos = 0;

    while(input.at(pos++) == ' ');

    result = input.right(input.size() - pos + 1);

    pos = result.size();

    while(result.at(--pos) == ' ')
        result.chop(1);

    return result;
}

QVector<QString> FlashCard::decode_answer(const QString& row) {
    QVector<QString> result;

    for(int pos = 0; pos < row.size(); ++pos)
    {
        pos = row.indexOf(";", pos);
        result.push_back(escape_start_end(row.left(pos)));

        if(pos == -1)
            break;
    }

    return result;
}

bool FlashCard::decode_row(const QString& row, int crow)
{
    switch(crow) {
    case 0:
        question = escape_start_end(row);
        break;
    case 1:
        answer = decode_answer(row);
        break;
    case 2:
        level = row.toInt();
        break;
    case 3:
        date = row.toLong();
        break;
    default:
        return false;
    }

    return true;
}

void FlashCard::increase_level() {
    if(level < MAXIMUM_LEVEL)
        level++;
}

void FlashCard::update_date() {
    date = time(NULL) / (60*60*24);
}

void FlashCard::clear_level() {
    level -= level%level_list.size();
}

bool FlashCard::is_due() const {
    //Add 12 hours, so the difference doesnt need to be precisely 24 hours
    return date + get_level(level) < (time(NULL) + 60*60*12) / (60*60*24);
}
