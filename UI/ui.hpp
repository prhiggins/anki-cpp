#include <ncurses.h>
#include "../Modal/card.h"
#include "../Controller/jobPool.h"

class UI {
public:
	UI();
	int present_menu();
	void present_cards();
	int present_card(card* c);
	~UI();
private:
	jobPool* deck;
	void draw_skeleton();
};
