#include "./Controller/jobPool.h"
#include "./Modal/card.h"
#include "./UI/ui.hpp"

int main() {
	// "activates" the ui - clears the screen and captures input
	UI* ui = new UI();
	jobPool* deck = new jobPool(jobPool().get_credential().at(0), jobPool().get_credential.at(1));

	while(1) {
		int mode = ui->present_menu();
		if (mode == 0) {
			while(1) {
				card* c = deck->get_next_card();
				int result = ui->present_card(c);
				if (result == -1) {
					break;
				}

				deck->study(*card, result);
			}
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
