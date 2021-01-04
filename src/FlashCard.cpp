#include "FlashCard.h"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

#include <time.h>

using namespace std;

vector<int> FlashCard::level_list  = {0, 1, 3, 5, 7, 14};

FlashCard::FlashCard(const string &content) {
#ifdef DEBUG
    cout << "Loading flashcard with content: " << endl;
    cout << content << endl;
#endif // DEBUG

    std::string row = "";
    int crow = 0;

    for(size_t pos = 0; pos < content.size(); ++pos) {
        if(content.find("=", pos) == string::npos)
            break;

        pos = content.find("=", pos) + 1;

        row = content.substr(pos, content.find("\n", pos) - pos);

        fill_row(row, crow);
        crow++;
    }
}

FlashCard::FlashCard(const string &question, const vector<string> &answer, int level, long date)
    : question(question), answer(answer), level(level), date(date) {

    if(date == 0)
        date = time(NULL);
}

FlashCard::~FlashCard() {}

string FlashCard::get_content() const {
    string result = "";

    result += "Question = " + question + "\n";
    result += "Answer = ";
    for(size_t i = 0; i < answer.size(); ++i)
        result += answer.at(i) + (i+1 < answer.size() ? "; " : "");
    result += "\n";

    result += "Level = " + to_string(level) + "\n";
    result += "Date = " + to_string(date) + "\n";

    return result;
}

bool FlashCard::check_answer(const string &given_answer) {
    for(vector<string>::const_iterator it = answer.begin(); it != answer.end(); ++it) {
        if(given_answer.compare(*it) == 0) {
            increase_level();
            update_date();
            return true;
        }
    }

    clear_level();
    return false;
}

bool FlashCard::check_question(const string &given_question) {
    if(given_question.compare(question) == 0) {
        increase_level();
        update_date();
        return true;
    }

    clear_level();
    return false;
}

string FlashCard::escape_start_end(const string &input) {
#ifdef DEBUG
    cout << "Escaping input: " << endl;
    cout << input << endl;
#endif // DEBUG

    string result = "";
    size_t pos = 0;

    while(input[pos++] == ' ');

    result = input.substr(--pos);

    pos = result.size();

    while(result[pos--] == ' ')
        result.pop_back();

    return result;
}

vector<string> FlashCard::generate_answer(const string &row) {
    vector<string> result;

    for(size_t pos = 0; pos < row.size(); ++pos) {
        result.push_back(escape_start_end(row.substr(pos, row.find(";", pos) - pos)));

        #ifdef DEBUG
        cout << "Answer: " << result.back() << endl;
        #endif // DEBUG

        if(row.find(";", pos) == string::npos)
            break;

        pos = row.find(";", pos);
    }

    return result;
}

bool FlashCard::fill_row(const string &row, int crow) {
#ifdef DEBUG
    cout << "Filling row with content: " << endl;
    cout << row << endl;
#endif // DEBUG

    switch(crow) {
    case 0:
        question = escape_start_end(row);
        break;
    case 1:
        answer = generate_answer(row);
        break;
    case 2:
        level = stoi(row);
        break;
    case 3:
        date = stol(row);
        break;
    default:
        return false;
    }

    return true;
}

string FlashCard::get_answer() const {
    string result = "";

    for(size_t i = 0; i < answer.size(); ++i)
        result += answer.at(i) + (i+1 < answer.size() ? "; " : "");

    return result;
}

void FlashCard::increase_level() {
    if(level < MAXIMUM_LEVEL)
        level++;
}

void FlashCard::update_date() {
    date = time(NULL) / (60*60*24);
}

void FlashCard::clear_level() {
    if(level < level_list.size())
        level = 0;
    else
        level -= level_list.size();
}

bool FlashCard::is_due() const {
    //Add 12 hours, so the difference doesnt need to be precisely 24 hours
    return date + get_level(level) < (time(NULL) + 60*60*12) / (60*60*24);
}
