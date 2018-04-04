// c4bot.h
// Aswin van Woudenberg & Rendall Schijven

#ifndef C4BOT_H
#define C4BOT_H

#include "c4.h"

#include <string>
#include <vector>
#include <chrono>

class C4Bot {
	int timebank;
	int time_per_move;
	std::string player_names[2];
	std::string your_bot;
	int your_botid;
	int field_columns;
	int field_rows;
	int round;
	State state = { { { { Player::None } } } };

    //This vector stores scores of specific positions on the board following the rules that the middle position is the best
    //and the more you go outward the worse the score will be.
	EvalTable evalTable = {{3, 4, 5, 7, 5, 4, 3},
						   {4, 6, 8, 10, 8, 6, 4},
						   {5, 8, 11, 13, 11, 8, 5},
						   {5, 8, 11, 13, 11, 8, 5},
						   {4, 6, 8, 10, 8, 6, 4},
						   {3, 4, 5, 7, 5, 4, 3}};


    //The functions in the starting bot
	std::vector<std::string> split(const std::string &s, char delim);
	void setting(std::string &key, std::string &value);
	void update(std::string &key, std::string &value);
	void move(int timeout);

    //Declaration of my own functions
	Move openingMoves(const State board, int myBot);
	Move ABHelper(const State &board, int depth);
	std::vector<int> alphaBeta(const State &board, const Player &player, int depth, int alpha, int beta);
	int evaluate(const Player player, const State board);

public:
	void createPatterns();
	void run();
};

#endif // C4BOT_H

