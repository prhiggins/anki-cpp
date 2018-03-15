#include "ui.hpp"

UI::UI() {
	initscr();
	keypad(stdscr, true);
	
	noecho();
	curs_set(0);
	raw();
	
	refresh();
	deck = new jobPool(jobPool::get_credential().at(0),  jobPool::get_credential().at(1));
}

void UI::present_cards() {
	while(1) {
		card* c = deck->get_next_card()
		deck->study(c, present_card(c));

	}
}
int UI::present_card(card* c) {
	const char* card_front =  c->front().c_str();
	int text_start_line = LINES / 3;
	int text_start_col = COLS / 2 - c->front().length();
	
	draw_skeleton();
	mvprintw(text_start_line, text_start_col, card_front);	
	mvprintw(LINES - 2, (COLS / 2) - 5, "Flip: Space");
	refresh();
	
	bool waiting = true;
	while (waiting) {
		int input = getch();
		if (input == ' ') {
			waiting = false;
		}
	}

	clear();	

	draw_skeleton();

	const char* card_back = c->back().c_str();
	mvprintw(text_start_line, COLS / 2 - c->back().length(), card_back);	
	
	mvprintw(LINES - 2, (COLS / 2) - 18, "1: Bad | 2: Hard | 3: Easy | 4: Good");
	
	refresh();

	waiting = true;
	int performance = -1;
	while (waiting) {
		int input = getch();
		if (input == '1') {
			performance = 0;
			waiting = false;
		}

		else if (input == '2') {
			performance = 1;
			waiting = false;
		}

		else if (input == '3') {
			performance = 2;
			waiting = false;
		}

		else if (input == '4') {
			performance = 3;
			waiting = false;
		}
	}

	return performance;
}

int UI::present_menu() {
	draw_skeleton();
	string options[3] = {"Practice","Create","Exit"};
	
	int selected = 0;

	while(1) {
		for (int i = 0; i < 3; i++) {
			if (i == selected) {
				attron(A_REVERSE);
			}
			int offset = options[i].length() / 2;
			mvprintw(LINES / 2 + i, COLS / 2 - offset, options[i].c_str());
			attroff(A_REVERSE);
		}
		int input = getch();
		switch(input) {
			case KEY_UP:
				selected--;
				break;
			case KEY_DOWN:
				selected++;
				break;
			default:
				break;
		}

		if (selected < 0) {
			selected = 2;
		}

		selected %= 3;
		if (input == 10) {
			break;
		}
	}
	return selected;
}

void UI::draw_skeleton() {
	box(stdscr, '*', '*');
}

UI::~UI() {
	echo();
	endwin();
}

