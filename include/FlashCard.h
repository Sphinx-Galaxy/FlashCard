#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <string>
#include <vector>

#define MAXIMUM_LEVEL 11

class FlashCard {
    public:
        FlashCard(const std::string &content);
        FlashCard(const std::string &question, const std::vector<std::string> &answer, int level = 0, long date = 0);
        virtual ~FlashCard();

        std::string get_question() const {return question;}
        std::string get_answer() const;

        static std::vector<int> get_level_list() {return level_list;}
        int get_level() const {return level;}
        int get_level(int level) const {return level_list.at(level%level_list.size());}

        long get_date() const {return date;}

        std::string get_content() const;

        bool check_answer(const std::string &given_answer);
        bool check_question(const std::string &given_question);

        bool is_due() const;

    private:
        std::string question;
        std::vector<std::string> answer;
        static std::vector<int> level_list;

        int level;
        long date;

        bool fill_row(const std::string &row, int crow);
        std::vector<std::string> generate_answer(const std::string &row);

        void increase_level();
        void update_date();
        void clear_level();

        std::string escape_start_end(const std::string &input);
};

#endif // FLASHCARD_H
