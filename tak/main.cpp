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
	void placePiece(Piece* piece) { this->pieces.push(piece); }
	Piece* pickupPiece();

private:
	std::stack<Piece*> pieces;
};

Position::Position() {

}

Position::~Position() {

}

bool Position::isEmpty() {
	return this->pieces.empty();
}

Color* Position::controlledBy() {
	return this->pieces.top()->getColor();
}

Piece* Position::pickupPiece() {
	Piece* rtrn = this->pieces.top();
	this->pieces.pop();
	return rtrn;
}

class Board {
public:
	Board();
	~Board();
	Position* getPosition(int column, int row);
	void setPositions(std::vector<std::vector<Position*>> positions);
	void reset();
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

void Board::setPositions(std::vector<std::vector<Position*>> positions) {
	this->positions = positions;
}

void Board::reset() {
	for (int y = 0; y < this->positions.size(); y++) {
		for (int x = 0; x < this->positions.size(); x++) {
			while (!this->positions[y][x]->isEmpty()) {
				this->positions[y][x]->pickupPiece();
			}
		}
	}
	return;
}

void Board::print() {

	return;
}

class Game {
public:
	Game();
	~Game();

	int getSize() { return this->size; }
	int getTurn() { return this->turn; }
	bool hasStarted() { return this->started; }
	int resolveAction(std::string action);

	int start();
	int save();
	int load();
	void reset();

	int place(int column, int row, PieceType* type);
	int move();
	int undo();

	void printBoard();

private:
	Board board;
	Color player;
	int size;
	int turn;
	bool started;

	Board* getBoard() { return &this->board; }
	Color* getPlayer() { return &this->player; }
	Piece* getPiece(PieceType* type);
	void printMeta();

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
	std::stack<std::string> history;
};

Game::Game() {
	this->started = false;
	return;
}

Game::~Game() {

}

Piece* Game::getPiece(PieceType* type) {
	if (this->turn % 2 == 0) {
		this->light_pieces_remaining -= 1;
		return &this->light_pieces_pool[this->light_pieces_remaining];
	}
	else {
		this->dark_pieces_remaining -= 1;
		return &this->dark_pieces_pool[this->dark_pieces_remaining];
	}
}

int Game::place(int column, int row, PieceType* type) {
	if (0 <= column && column < this->size && 0 <= row && row < this->size && this->getBoard()->getPosition(column, row)->isEmpty()) {
		Piece* piece = this->getPiece(type);
		this->getBoard()->getPosition(column, row)->placePiece(piece);
		return 1;
	}
	else {
		return 0;
	}
}

int Game::move() {
	return 1;
}

void Game::printBoard() {

}

void Game::printMeta() {
	std::cout << "Game size: " << std::to_string(this->size) << std::endl;
	std::cout << "Game turn: " << std::to_string(this->turn) << std::endl;
}

void Game::reset() {
	this->turn = 0;
	this->hand = {};

	this->getBoard()->reset();

	return;
}

int Game::save() {
	return 1;
}

int Game::load() {
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

	std::vector<std::vector<Position*>> board_positions;
	for (int c = 0; c < this->size; ++c) {
		std::vector<Position*> board_column;
		for (int r = 0; r < this->size; ++r) {
			board_column.push_back(&this->positions[c][r]);
		}
		board_positions.push_back(board_column);
	}
	this->getBoard()->setPositions(board_positions);

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

	this->started = true;
	this->printMeta();

	return 1;
}

int Game::undo() {
	return 0;
}

int Game::resolveAction(std::string action) {
	// try to do action

	// if change, check if player won, resolve game, else check if game over conditions met, determine winner and resolve game, else step game meta, else return 0
	return 0;
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
	return;
}

int main() {

	bool running = true;;
	
	// memory initialization
	Game game;
	Color light_val = light;
	Color dark_val = dark;
	PieceType road_val = road;
	PieceType wall_val = road;
	PieceType capstone_val = road;

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
			case 's':
				game.save();
				break;
			case 'l':
				game.load();
				break;
			case 'p':
				game.place(0, 0, &road_val);
				break;
			case 'm':
				game.move();
				break;
			case 'u':
				game.undo();
				break;
			default:
				std::cout << "'" << cmd << "' is not a valid command. Try 'h' for a list of all available commands..." << std::endl;
				break;
			}
		}
	}
	
	return 0;
}