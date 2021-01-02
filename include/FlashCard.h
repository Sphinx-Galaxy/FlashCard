#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <string>
#include <vector>

#define MAXIMUM_LEVEL 13

using namespace std;

class FlashCard {
    public:
        FlashCard(const string &content);
        FlashCard(const string &question, const vector<string> &answer, int level = 0, long date = 0);
        virtual ~FlashCard();

        string get_question() const {return question;}
        string get_answer() const;

        static vector<int> get_level_list() {return level_list;}
        int get_level() const {return level;}
        int get_level(int level) const {return level_list.at(level%level_list.size());}

        long get_date() const {return date;}

        string get_content() const;

        bool check_answer(const string &given_answer);
        bool check_question(const string &given_question);

        bool is_due() const;

    private:
        string question;
        vector<string> answer;
        static vector<int> level_list;

        int level;
        long date;

        bool fill_row(const string &row, int crow);
        vector<string> generate_answer(const string &row);

        void increase_level();
        void update_date();
        void clear_level();

        string escape_start_end(const string &input);
};

#endif // FLASHCARD_H
