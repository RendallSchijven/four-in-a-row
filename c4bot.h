// c4bot.h
// Aswin van Woudenberg & Rendall Schijven

#ifndef C4BOT_H
#define C4BOT_H

#include "c4.h"
#include "node.h"

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

	typedef std::chrono::steady_clock::time_point Time;
    Time begin;

	std::vector<std::string> split(const std::string &s, char delim);
	void setting(std::string &key, std::string &value);
	void update(std::string &key, std::string &value);
	void move(int timeout);

	Move alphaBeta(const State &board, int depth);
	std::vector<int> minimax(const State &board, const Player &player, int depth, int alpha, int beta);
	int evaluate(const Player player, const State board);
    EvalTable evalTable = {{3, 4, 5, 7, 5, 4, 3},
                           {4, 6, 8, 10, 8, 6, 4},
                           {5, 8, 11, 13, 11, 8, 5},
                           {5, 8, 11, 13, 11, 8, 5},
                           {4, 6, 8, 10, 8, 6, 4},
                           {3, 4, 5, 7, 5, 4, 3}};

	int getTimeElapsed();
	double selectfn(Node* n);
	double selectfnOP(Node* n);
	void backPropagate(Node* n, int score);
	int simulate(State s);
	void expand(Node* n);
	Node* select(Node* n);
	Move makeMove(int timeout);

public:
	void run();
};

#endif // C4BOT_H

