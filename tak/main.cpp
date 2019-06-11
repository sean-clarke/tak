#include <iostream>
#include <string>
#include <vector>
#include <stack>

enum Color {
	light,
	dark
};

class Piece {

public:
	Color getColor() { return this->color; }

private:
	Color color;
};

std::string player_name;
Color player;
Color turn;
bool running;
int move;
std::vector<std::stack<Piece>> board;
std::stack<Piece> hand;

void help() {
	std::cout << "Here is a list of all available commands:" << std::endl;
	std::cout << "'n': Starts a new game of Tak." << std::endl;
	std::cout << "'s': Saves the current game." << std::endl;
	std::cout << "'l': Loads a previous game." << std::endl;
	std::cout << "'q': Exits the program." << std::endl;
	std::cout << "'h': Lists all available commands." << std::endl;

	std::cout << "'p' (p A1): [Place] Places a new piece on the board." << std::endl;
	std::cout << "'m' (m A1 B1) (m 2 B1 B2 1 B3): [Move] Moves a piece or stack currently on the board." << std::endl;
	std::cout << "'u': [Undo] Resets the board to your last action." << std::endl;
	std::cout << "'r': [Redo] Replays the last undone action." << std::endl;
	return;
}

void printBoard() {
	
	return;
}

void startGame() {
	std::cout << "You've started a new game of Tak!" << std::endl;

	// Set player color
	std::cout << "Do you want to go first (1), or second (2)?" << std::endl;
	char cmd;
	std::cin >> cmd;
	while (cmd != '1' && cmd != '2') {
		std::cout << "'" << cmd << "' is not a valid command, please enter either '1' or '2'!" << std::endl;
		std::cin >> cmd;
	}

	// Set board size
	std::cout << "What size of board would you like to play on?" << std::endl;
	std::cout << "Do you want to go first (1), or second (2)?" << std::endl;
	std::cout << "3x3 (3), 4x4 (4), 5x5 (5), 6x6 (6), or 7x7 (7)..." << std::endl;
	while (cmd != '3' && cmd != '4' && cmd != '5' && cmd != '6' && cmd != '7') {
		std::cout << "'" << cmd << "' is not a valid command, please enter either '3', '4', '5', '6', or '7'!" << std::endl;
		std::cin >> cmd;
	}

	return;
}

int main() {
	std::cout << "What is your name?" << std::endl;
	std::cin >> player_name;
	std::cout << "Hey " << player_name << ", let's play Tak!\n" << std::endl;
	std::cout << "If you want to start a new game, press 'n'..." << std::endl;
	std::cout << "When you are done playing, press 'q' to quit..." << std::endl;
	std::cout << "To see a list of all available commands, press 'h'...\n" << std::endl;
	
	running = true;
	std::string cmd;

	while (running) {
		std::cout << "> ";
		std::cin >> cmd;

		if (cmd != "") {
			switch (cmd.at(0)) {
			case 'q':
				running = false;
				break;
			case 'h':
				help();
				break;
			case 'n':
				startGame();
				break;
			default:
				std::cout << "'" << cmd << "' is not a valid command. Try 'h' for a list of all available commands..." << std::endl;
				break;
			}
		}
	}
	
	return 0;
}