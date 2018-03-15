#include <ncurses.h>
#include "../Modal/card.h"

class UI {
public:
	UI();
	int present_menu();
	void present_cards();
	int present_card(card* c);
	~UI();
private:
	void draw_skeleton();
};
