#include "ui.hpp"

UI::UI() {
	initscr();
	keypad(stdscr, true);
	
	noecho();
	curs_set(0);
	raw();
	
	refresh();
}

performance UI::present_card(card c) {
	curs_set(0);
	clear();
	draw_skeleton();
	stringstream ss;
	ss << c;
	string front = c.front() + ss.str();

	const char* card_front =  front.c_str();
	int text_start_line = LINES / 3;
	int text_start_col = COLS / 2 - (c.front().length() / 2);
	
	draw_skeleton();
	mvprintw(text_start_line, text_start_col, card_front);	
	mvprintw(LINES - 2, (COLS / 2) - 5, "Flip: Space");
	mvprintw(LINES - 3, (COLS / 2) - 7, "End Session: Q");
	
	refresh();
	
	bool waiting = true;
	while (waiting) {
		int input = getch();
		if (input == ' ') {
			waiting = false;
		}
		else if (input == 'q') {
			return unf;
		}
	}

	clear();	

	draw_skeleton();

	const char* card_back = c.back().c_str();
	mvprintw(text_start_line, COLS / 2 - (c.back().length() / 2), card_back);	
	string options[4] = {"Bad","Hard","Good","Easy"};
	//mvprintw(LINES - 2, (COLS / 2) - 18, "1: Bad | 2: Hard | 3: Good | 4: Easy");
	refresh();
	int selected = 0;
	waiting = true;
	performance perf = unf;
	int input;
	while (1) {
		if (input == 10) {
			break;
		}

		switch (input) {
			case KEY_LEFT:
				selected--;
				break;
			case KEY_RIGHT:
				selected++;
				break;
		}

		if (selected < 0) {
			selected = 0;
		}
		
		selected %= 4;
		move(LINES - 2, (COLS / 2) - 12);
		for (int i = 0; i < 4; i++) {
			if (i == selected) {
			attron(A_REVERSE);
			}

			printw(options[i].c_str());
			attroff(A_REVERSE);
			if (i < 3) {
				printw(" | ");
			}
		}
		input = getch();
	}
	if (selected == 0) {
		perf = bad;
	}

	else if (selected == 1) {
		perf = hard;
	}

	else if (selected == 2) {
		perf = easy;
	}

	else if (selected == 3) {
		perf = good;
	}

	return perf;
}

int UI::present_menu() {
	curs_set(0);
	clear();
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
void UI::create_card(string &front, string &back) {	
	clear();
	draw_skeleton();
	// mvprintw(LINES / 2, COLS / 2 - 11, "Front Side:");
	curs_set(1);
	

	front = "";
	back = "";
	

	char ch;
   
    while (1) // Assumes (default) position of cursor is at printing location.
    {
    	refresh();
    	mvprintw(LINES / 2, COLS / 2 - 11, "Front Side: %s", front.c_str());
        ch = getch();
        if (ch == '\n') // Keeps buffering input until end of line. Check done after acquiring input char (thus if inside while) to prevent it from being discarded automatically.
        {
                break;
        }
        if (ch == '\a' || ch == '\b') // Ensure normal attempts at backspace are caught.
        {
                if (!front.empty()) // pop_back will cause a crash when attempting to remove stuff from an empty vector.
                {
                        front.pop_back(); // Removes previously entered character from buffered input.
                        addch('\b'); // Actual backspacing from user's perspective in these 5 lines.
                        addch(' ');
                        int y, x;
                        getyx (stdscr, y, x);
                        move (y, x-1); // More than one line of user input deemed unlikely/useless.
                }
        }
        else
        {
                front.push_back(ch);
                addch(ch);
        }
    }
	
	clear();
	draw_skeleton();
	// mvprintw(LINES / 2, COLS / 2 - 10, "Back Side:");
	refresh();
	while (1) // Assumes (default) position of cursor is at printing location.
    {
    	refresh();
    	mvprintw(LINES / 2, COLS / 2 - 10, "Back Side: %s", back.c_str());
        ch = getch();
        if (ch == '\n') // Keeps buffering input until end of line. Check done after acquiring input char (thus if inside while) to prevent it from being discarded automatically.
        {
                break;
        }
        if (ch == '\a' || ch == '\b') // Ensure normal attempts at backspace are caught.
        {
                if (!back.empty()) // pop_back will cause a crash when attempting to remove stuff from an empty vector.
                {
                        back.pop_back(); // Removes previously entered character from buffered input.
                        addch('\b'); // Actual backspacing from user's perspective in these 5 lines.
                        addch(' ');
                        int y, x;
                        getyx (stdscr, y, x);
                        move (y, x-1); // More than one line of user input deemed unlikely/useless.
                }
        }
        else
        {
                back.push_back(ch);
                addch(ch);
        }
    }
	
	
}

void UI::draw_skeleton() {
	box(stdscr, '*', '*');
}

UI::~UI() {
	echo();
	endwin();
}

