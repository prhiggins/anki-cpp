#include "../Service/studyService.h"
#include "../Modal/card.h"
#include<ncurses.h>
# include <algorithm>
# include <iostream>
# include <fstream>
# include <iterator>
# include <string>
# include <sstream>
# include <vector>
# include <ncurses.h>
class UI {
public:
	UI();
	int present_menu();
	void create_card(string &front, string &back);
	performance present_card(card c);
	~UI();
private:
	void draw_skeleton();
};
