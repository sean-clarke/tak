#include <iostream>
#include <string>
#include <vector>
#include <stack>

enum PieceType {
	road,
	wall,
	capstone
};

enum Color {
	light,
	dark
};

class Piece {
public:
    Piece(PieceType type, Color color);
    ~Piece();
    PieceType* getType() { return &this->type; }
	PieceType* flipType();
    Color* getColor() { return &this->color; }

protected:
    PieceType type;
    Color color;
};

Piece::Piece(PieceType type, Color color) {
    this->type = type;
    this->color = color;
}

Piece::~Piece() {

}

PieceType* Piece::flipType() {
	switch (this->type) {
	case wall:
		this->type = road;
		break;
	case road:
		this->type = wall;
		break;
	case capstone:
		break;
	}
	return &this->type;
}

class Capstone: public Piece {
public:
	Capstone(Color color);
};

Capstone::Capstone(Color color) : Piece(capstone, color) {};

class Position {
public:
	Position();
	~Position();
	bool isEmpty();
	Color* controlledBy();
private:
	std::stack<Piece> pieces;
};

Position::Position() {

}

Position::~Position() {

}

bool Position::isEmpty() {
	return this->pieces.empty();
}

Color* Position::controlledBy() {
	return this->pieces.top().getColor();
}

class Board {
public:
	Board();
	~Board();
	Position* getPosition(int column, int row);
	void print();

private:
    std::vector<std::vector<Position*>> positions;
};

Board::Board() {

}

Board::~Board() {

}

Position* Board::getPosition(int column, int row) {
	return this->positions.at(column).at(row);
}

void Board::print() {

	return;
}

class Game {
public:
	Game();
	~Game();

	Board* getBoard() { return &this->board; }
	Color* getPlayer() { return &this->player; }
	int* getSize() { return &this->size; }
	int* getTurn() { return &this->turn; }

	int start();
	int save();
	int load();
	int reset();

	int place();
	int move();
	int undo();
	int redo();

	void printBoard();

private:
	Board board;
	Color player;
	int size;
	int turn;

	Piece light_pieces_pool[50] = { Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light), Piece(road, light) };
	Piece dark_pieces_pool[50] = { Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark), Piece(road, dark) };
	Capstone light_capstones[2] = { Capstone(light), Capstone(light) };
	Capstone dark_capstones[2] = { Capstone(dark), Capstone(dark) };

	Position positions[8][8] = {{ Position(), Position(), Position(), Position(), Position(), Position(), Position(), Position() },
								{ Position(), Position(), Position(), Position(), Position(), Position(), Position(), Position() },
								{ Position(), Position(), Position(), Position(), Position(), Position(), Position(), Position() },
								{ Position(), Position(), Position(), Position(), Position(), Position(), Position(), Position() },
								{ Position(), Position(), Position(), Position(), Position(), Position(), Position(), Position() },
								{ Position(), Position(), Position(), Position(), Position(), Position(), Position(), Position() },
								{ Position(), Position(), Position(), Position(), Position(), Position(), Position(), Position() },
								{ Position(), Position(), Position(), Position(), Position(), Position(), Position(), Position() }};
	int light_pieces_remaining;
	int dark_pieces_remaining;
	int light_capstones_remaining;
	int dark_capstones_remaining;
	std::stack<Piece*> hand;
};

Game::Game() {
	return;
}

Game::~Game() {

}

void Game::printBoard() {

}

int Game::reset() {
	this->turn = 0;
	this->hand = {};

	return 1;
}

int Game::start() {
	std::cout << "You've started a new game of Tak!" << std::endl;

	this->reset();

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
	std::cout << "3x3 (3), 4x4 (4), 5x5 (5), 6x6 (6), 7x7 (7), or 8x8 (8)?" << std::endl;
	std::cin >> cmd;
	while (cmd != '3' && cmd != '4' && cmd != '5' && cmd != '6' && cmd != '7' && cmd != '8') {
		std::cout << "'" << cmd << "' is not a valid command, please enter either '3', '4', '5', '6', '7', or '8'!" << std::endl;
		std::cin >> cmd;
	}
	this->size = cmd - '0';

	if (this->size == 8) {
		this->light_pieces_remaining = 50;
		this->dark_pieces_remaining = 50;
		this->light_capstones_remaining = 2;
		this->dark_capstones_remaining = 2;
	}
	else if (this->size == 7) {
		this->light_pieces_remaining = 40;
		this->dark_pieces_remaining = 40;

		std::cout << "Do you want to play with 1 (1) or 2 (2) capstones per player?" << std::endl;
		std::cin >> cmd;
		while (cmd != '1' && cmd != '2') {
			std::cout << "'" << cmd << "' is not a valid command, please enter either '1' or '2'!" << std::endl;
		}
		if (cmd == '2') {
			this->light_capstones_remaining = 2;
			this->dark_capstones_remaining = 2;
		}
		else {
			this->light_capstones_remaining = 1;
			this->dark_capstones_remaining = 1;
		}
	}
	else if (this->size > 4) {
		this->light_capstones_remaining = 1;
		this->dark_capstones_remaining = 1;
		if (this->size == 6) {
			this->light_pieces_remaining = 30;
			this->dark_pieces_remaining = 30;
		}
		else {
			this->light_pieces_remaining = 21;
			this->dark_pieces_remaining = 21;
		}
	}
	else {
		this->light_capstones_remaining = 0;
		this->dark_capstones_remaining = 0;
		if (this->size == 4) {
			this->light_pieces_remaining = 15;
			this->dark_pieces_remaining = 15;
		}
		else {
			this->light_pieces_remaining = 10;
			this->dark_pieces_remaining = 10;
		}
	}

	return 1;
}

void help() {
	std::cout << "Here is a list of all available commands:" << std::endl;
	std::cout << "'n': Starts a new game of Tak." << std::endl;
	std::cout << "'s': Saves the current game." << std::endl;
	std::cout << "'l': Loads a previous game." << std::endl;
	std::cout << "'q': Exits the program." << std::endl;
	std::cout << "'h': Lists all available commands." << std::endl;

	std::cout << "'p' (p A1): [Place] Places a new piece on the board." << std::endl;
	std::cout << "'m' (m A1 B1): [Move] Moves a piece or stack currently on the board." << std::endl;
	std::cout << "'u': [Undo] Resets the board to your last action." << std::endl;
	std::cout << "'r': [Redo] Replays the last undone action." << std::endl;
	return;
}

int main() {

	bool running = true;;
	
	// memory initialization
	Game game;

	// intro
	std::cout << "What is your name?" << std::endl;
	std::string player_name;
	std::cin >> player_name;
	std::cout << "Hey " << player_name << ", let's play Tak!\n" << std::endl;
	std::cout << "If you want to start a new game, press 'n'..." << std::endl;
	std::cout << "When you are done playing, press 'q' to quit..." << std::endl;
	std::cout << "To see a list of all available commands, press 'h'...\n" << std::endl;
	
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
				game.start();
				break;
			default:
				std::cout << "'" << cmd << "' is not a valid command. Try 'h' for a list of all available commands..." << std::endl;
				break;
			}
		}
	}
	
	return 0;
}