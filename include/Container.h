#ifndef CONTAINER_H
#define CONTAINER_H

#include "FlashCard.h"

#include <string>
#include <vector>

using namespace std;

class Container
{
    public:
        Container(const string &content);
        virtual ~Container();

        string get_content() const;
        FlashCard *get_active_card() const  {return active_card;}

        FlashCard * draw_card();

        bool is_done() const;

    private:
        vector<FlashCard*> flash_stack;
        FlashCard* active_card;
};

#endif // CONTAINER_H
