#include "ui.hpp"
#include "../Modal/card.h"

int main() {
	// "activates" the ui - clears the screen and captures input
	UI* ui = new UI();

	while(1) {
		int mode = ui->present_menu();
		if (mode == 0) {
			ui->present_cards();
		}
		else if (mode == 1) {
			// open create panel
		}
		else if (mode == 2) {
			break;
		}
	}
	
	// this is important to allow the program to cleanly exit & allow the terminal to behave normally after termination
	delete ui;
}
