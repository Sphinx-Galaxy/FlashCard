#include <iostream>

#include "Container.h"
#include "FileHandler.h"

using namespace std;

int main() {

    /* Ask for learn file */
    string filename;
    do {
        cout << "Select your work file: " << endl;

        char buffer[256];
        cin.getline(buffer, sizeof(buffer));
        filename = buffer;

    } while(FileHandler::is_valid(filename) == false);

    /* Build flash card container */
    Container container(FileHandler::import_cards(filename));

    /* Check if you actually need to learn */
    if(container.is_done())
        return 0;

    /* Ask flash cards */
    string answer;
    bool result;
    do {
        container.draw_card();

        /* First / Second level */
        if(container.get_active_card()->get_level() < FlashCard::get_level_list().size())
            cout << "Question: " << container.get_active_card()->get_question() << endl;
        else
            cout << "Answer: " << container.get_active_card()->get_answer() << endl;

        // Acquire answer input
        char buffer[256];
        cin.getline(buffer, sizeof(buffer));
        answer = buffer;

        /* First / Second level */
        if(container.get_active_card()->get_level() < FlashCard::get_level_list().size())
            result = container.get_active_card()->check_answer(answer);
        else
            result = container.get_active_card()->check_question(answer);

        cout << "Your answer was " << (result ? "correct" : "wrong") << endl;

        if(result == false)
            cout << "Correct answer would be: " << container.get_active_card()->get_answer();

        cout << endl;

    } while(answer.compare("q") == 0 || !container.is_done());

    /* Save the container */
    FileHandler::export_cards(filename, container.get_content());

    return 0;
}
