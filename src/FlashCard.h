#ifndef FLASHCARD_H
#define FLASHCARD_H

/*
 * Author: Mattis Jaksch
 *
 */

#include <QString>
#include <QVector>
#include <QStandardItem>

#define MAXIMUM_LEVEL 11

class FlashCard : public QStandardItem
{
public:
    FlashCard(const QString& content);
    FlashCard(const QString& question, const QVector<QString>& answer, int level = 0, long date = 0);
    virtual ~FlashCard();

    QString get_question() const
    {
        return question;
    }

    QVector<QString> get_answer() const
    {
        return answer;
    }

    static QVector<int> get_level_list()
    {
        return level_list;
    }

    int get_level() const
    {
        return level;
    }

    int get_level(int level) const
    {
        return level_list.at(level%level_list.size());
    }

    long get_date() const
    {
        return date;
    }

    QString get_content() const;

    bool check_answer(const QString& given_answer);
    bool check_question(const QString& given_question);

    bool is_due() const;

private:
    QString question;
    QVector<QString> answer;
    static QVector<int> level_list;

    int level;
    long date;

    bool decode_row(const QString& row, int crow);
    QVector<QString> decode_answer(const QString& row);

    void increase_level();
    void update_date();
    void clear_level();

    QString escape_start_end(const QString& input);
};

#endif // FLASHCARD_H
