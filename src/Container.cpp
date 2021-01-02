#include "Container.h"

#include <stdlib.h>
#include <time.h>

#ifdef DEBUG
#include <iostream>
#endif // DEBUG

Container::Container(const string &content) {
    string card_content = "";
    size_t pos = 0;

    for(size_t i = 0; i < content.size(); ++i) {
        card_content = content.substr(content.find("Card", pos), content.find("Card", pos+1));

#ifdef DEBUG
        cout << "Generating card content... Found Keyword \"Card\" " << (content.find("Card") == string::npos ? "nowhere" : "at " + to_string(content.find("Card")));
#endif // DEBUG

        pos = content.find("Card", pos+1);

        i = pos;
        flash_stack.push_back(new FlashCard(card_content));

        if(pos == string::npos)
            break;
    }

    srand(time(NULL));
}

Container::~Container() {
    for(size_t i = 0; i < flash_stack.size(); ++i)
        delete flash_stack.at(i);
}

string Container::get_content() const  {
    string result = "";

    for(size_t i = 0; i < flash_stack.size(); ++i) {
        result += "Card\n";
        result += flash_stack[i]->get_content() + "\n";
    }

    return result;
}

FlashCard * Container::draw_card() {
    do {
        active_card = flash_stack.at(rand() % flash_stack.size());
    } while(!active_card->is_due());

    return active_card;
}

bool Container::is_done() const {
    for(vector<FlashCard*>::const_iterator it = flash_stack.begin(); it != flash_stack.end(); ++it)
        if((*it)->is_due())
            return false;

    return true;
}
