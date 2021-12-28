#ifndef CONTAINER_H
#define CONTAINER_H

/*
 * Author: Mattis Jaksch
 *
 */

#include "FlashCard.h"

#include <string>
#include <vector>

class Container
{
    public:
        Container(const std::string &content);
        virtual ~Container();

        std::string get_content() const;
        FlashCard *get_active_card() const  {return active_card;}

        FlashCard * draw_card();

        bool is_done() const;

    private:
        std::vector<FlashCard*> flash_stack;
        FlashCard* active_card;
};

#endif // CONTAINER_H
