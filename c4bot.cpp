// c4bot.cpp
// Aswin van Woudenberg & Rendall Schijven

#include "c4bot.h"
#include <iostream>
#include <sstream>

unsigned const n_trials = 1000;
unsigned const mc_match = 1;
unsigned const mc_other = 1;

void C4Bot::run() {
	std::string line;
	while (std::getline(std::cin, line)) {
		std::vector<std::string> command = split(line, ' ');
		if (command[0] == "settings") {
			setting(command[1], command[2]);
		} else if (command[0] == "update" && command[1] == "game") {
			update(command[2], command[3]);
		} else if (command[0] == "action" && command[1] == "move") {
			move(std::stoi(command[2]));
		} else {
			std::cerr << "Unknown command: " << line << std::endl;
		}
	}
}

/*int evaluateLine(int row1, int col1, int row2, int col2, int row3, int col3, const State &board) {
    int score = 0;

    // First cell
    if (board[row1][col1] == Player::O) {
        score = 1;
    }
    else if (board[row1][col1] == Player::X) {
        score = -1;
    }

    // Second cell
    if (board[row2][col2] == Player::O) {
        if (score == 1) {   // cell1 is mySeed
            score = 10;
        }
        else if (score == -1) {  // cell1 is oppSeed
            return 0;
        }
        else {  // cell1 is empty
            score = 1;
        }
    }
    else if (board[row2][col2] == Player::X) {
        if (score == -1) { // cell1 is oppSeed
            score = -10;
        }
        else if (score == 1) { // cell1 is mySeed
            return 0;
        }
        else {  // cell1 is empty
            score = -1;
        }
    }

    // Third cell
    if (board[row3][col3] == Player::O) {
        if (score > 0) {  // cell1 and/or cell2 is mySeed
            score *= 10;
        }
        else if (score < 0) {  // cell1 and/or cell2 is oppSeed
            return 0;
        }
        else {  // cell1 and cell2 are empty
            score = 1;
        }
    }
    else if (board[row3][col3] == Player::X) {
        if (score < 0) {  // cell1 and/or cell2 is oppSeed
            score *= 10;
        }
        else if (score > 1) {  // cell1 and/or cell2 is mySeed
            return 0;
        }
        else {  // cell1 and cell2 are empty
            score = -1;
        }
    }
    return score;
}

int eval(const State &board, const Player &player)
{
    int score = 0;
    score += evaluateLine(0, 0, 0, 1, 0, 2, board);  // row 0
    score += evaluateLine(1, 0, 1, 1, 1, 2, board);  // row 1
    score += evaluateLine(2, 0, 2, 1, 2, 2, board);  // row 2
    score += evaluateLine(0, 0, 1, 0, 2, 0, board);  // col 0
    score += evaluateLine(0, 1, 1, 1, 2, 1, board);  // col 1
    score += evaluateLine(0, 2, 1, 2, 2, 2, board);  // col 2
    score += evaluateLine(0, 0, 1, 1, 2, 2, board);  // diagonal
    score += evaluateLine(0, 2, 1, 1, 2, 0, board);  // alternate diagonal
    return score;
}*/

State mcTrial(const State &board)
{
    State testBoard = board;
    std::vector<Move> moves = getMoves(board);

    while(moves.size() > 0)
    {
        Move m = moves[rand() % moves.size()];
        testBoard = doMove(testBoard, m);
        moves = getMoves(testBoard);
    }
    return testBoard;
}

void mcUpdateScores(std::array<int,7> &scores, const State &board, const Player &player)
{
    Player winner = getWinner(board);

    for(int row = 0; row < 6; row++)
    {
        for(int col = 0; col < 7; col++)
        {
            //If human won
            if(winner != player)
            {
                if(board[row][col] == Player::X) scores[col] += mc_other;
                if(board[row][col] == Player::O) scores[col] -= mc_match;
            }

            //If code won
            if(winner == player)
            {
                if(board[row][col] == Player::O) scores[col] += mc_match;
                if(board[row][col] == Player::X) scores[col] -= mc_other;
            }
        }
    }
}

Move getBestMove(const std::array<int, 7> &scores, const State &board)
{
    int highScore = 0;

    std::vector<int> highestPositions;
    for(int row = 0; row < 6; row++)
    {
        for(int col = 0; col < 7; col++)
        {
            if(scores[col] >= highScore && board[row][col] == Player::None)
            {
                highScore = scores[col];
                highestPositions.push_back(col);
            }
        }
    }
    Move m = highestPositions[rand() % highestPositions.size()];
    return m;
}

Move mcMove(const State &board)
{
    std::array<int, 7> scores = {0,0,0,0,0,0,0};
    for(int i = 0; i < n_trials; i++)
    {
        State tempBoard = mcTrial(board);
        mcUpdateScores(scores, tempBoard, getCurrentPlayer(board));
    }

    return getBestMove(scores, board);
}

int eval(const Player player, const State board, int depth){
    Player opponent = (player == Player::X) ? Player::O : Player::X;

    if(getWinner(board) == player){
        return 10 - depth;
    }
    else if(getWinner(board) == opponent){
        return  depth - 10;
    } else return 0;
}

std::vector<int> minimax(const State &board, const Player &player, int depth, int alpha, int beta)
{
    std::vector<Move> moves = getMoves(board);

    int score;
    int bestMove = -1;

    if(depth == 0|| moves.size() == 1){
        score = eval(player, board, depth);
        return {score,bestMove};
    }
    else
    {
        depth--;

        for(Move m: moves)
        {
            State tempboard = doMove(board, m);;

            if(player == Player::O) //Computer
            {
                score = minimax(tempboard, Player::X, depth, alpha, beta)[0];

                if(score > alpha)
                {
                    alpha = score;
                    bestMove = m;
                }
            }
            else //Human
            {
                score = minimax(tempboard, Player::O, depth, alpha, beta)[0];

                if(score < beta)
                {
                    beta = score;
                    bestMove = m;
                }
            }
            //Alpha beta pruning
            if(alpha >= beta) break;
        }
        return {(player == Player::O) ? alpha : beta, bestMove};
    }
}

Move alphaBeta(const State &board, int depth)
{
    Move result = minimax(board, getCurrentPlayer(board), depth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max())[1];
    std::vector<Move> moves = getMoves(board);
    return {(result != -1) ? result : *select_randomly(moves.begin(), moves.end())};
}

void C4Bot::move(int timeout) {
    //"C:\Users\renda\Desktop\c4ui.exe" "C:\Users\renda\Desktop\Git\four-in-a-row\cmake-build-debug\four-in-a-row.exe"

    //Monte carlo
    std::cout << "place_disc " << mcMove(state) << std::endl;

    //Alpha beta
    //std::cout << "place_disc " << alphaBeta(state, 9) << std::endl;

    //Original
	//std::vector<Move> moves = getMoves(state);
	//std::cout << "place_disc " << *select_randomly(moves.begin(), moves.end()) << std::endl;
}

void C4Bot::update(std::string &key, std::string &value) {
	if (key == "round") {
		round = std::stoi(value);
	} else if (key == "field") {
		int row = 0;
		int col = 0;
		std::vector<std::string> fields = split(value, ',');
		for (std::string &field : fields) {
			if (field == "0") {
				state[row][col] = Player::X; 
			} else if (field == "1") {
				state[row][col] = Player::O;
			} else {
				state[row][col] = Player::None;
			}
			col++;
			if (col == 7) {
				row++; 
				col = 0;
			}
		}
	}
}

void C4Bot::setting(std::string &key, std::string &value) {
	if (key == "timebank") {
		timebank = std::stoi(value);
	} else if (key == "time_per_move") {
		time_per_move = std::stoi(value);
	} else if (key == "player_names") {
		std::vector<std::string> names = split(value, ',');
		player_names[0] = names[0];
		player_names[1] = names[1];
	} else if (key == "your_bot") {
		your_bot = value;
	} else if (key == "your_botid") {
		your_botid = std::stoi(value);
	} else if (key == "field_columns") {
		field_columns = std::stoi(value);
	} else if (key == "field_rows") {
		field_rows = std::stoi(value);
	}
}

std::vector<std::string> C4Bot::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

