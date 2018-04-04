// c4bot.cpp
// Aswin van Woudenberg & Rendall Schijven

#include "c4bot.h"
#include "openingBook.h"

#include <iostream>
#include <sstream>
#include <fstream>

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

/**
 * This is the function that i used to create my opening book used in C4Bot::openingMoves.
 * The function computes move patterns by playing my alpha beta algorithm against a random move generator.
 * To run this call it from main.cpp instead of C4Bot.run.
 * After running it for the desired amount of repetitions(i < amount of boards to be played)
 * i paste the contents of the text file into the vector in openingBook.h then it can be used by C4Bot::openingMoves.
 */
//TODO move to separate source file
void C4Bot::createPatterns() {
    //Loop that executes the program i times. Every loop 1 board is solved.
    for(int i = 0; i < 30000; i++)
    {
        State testState = { { { { Player::None } } } };
        bool first = true;
        std::vector<int> moveSaver;
        std::vector<Move> moves = getMoves(testState);

        //TODO run at max depth
        while(moves.size() != 0)
        {
            Move m;
            //For even numbers let alpha beta algorithm start
            if(i % 2 == 0)
            {
                if(getCurrentPlayer(testState) == Player::X)
                {
                    if(first) {
                        m = 3;
                        first = false;
                    }
                    //Run the alpha beta algorithm with desired depth, more depth is almost always more accurate but also slower.
                    else m = ABHelper(testState, 10);
                } else{
                    m = *select_randomly(moves.begin(), moves.end());
                }
            }
            //For odd numbers let the random move generator start.
            else
            {
                if(getCurrentPlayer(testState) == Player::O)
                {
                    if(testState[5][3] == Player::None) m = 3;
                    else m = ABHelper(testState, 42);
                } else{
                    m = *select_randomly(moves.begin(), moves.end());
                }
            }

            //Run the selected move on the test board.
            testState = doMove(testState, m);

            //Save the selected move.
            moveSaver.push_back(m);

            //Print the calculated moves to the console.
            std::cout << m << std::endl;

            //Update moves
            moves = getMoves(testState);
        }

        //Create a new filestream which either opens the file if it exists or creates it and ads the output to the end of the file.
        //File will be located in cmake-build-debug.
        std::ofstream openingBook;
        openingBook.open("OpeningBook.txt", std::ios_base::app);

        //Write the move vectors to the file
        openingBook << "{";
        for(std::vector<int>::const_iterator i = moveSaver.begin(); i != moveSaver.end(); i++){
            if(i == moveSaver.end() - 1) openingBook << *i;
            else openingBook << *i << ",";
        }
        openingBook << "},";

        //Close the filestream
        openingBook.close();
    }
}

/**
 * Function that calculates the first few moves to increase the speed of the bot.
 * It uses a library of moves defined in c4bot.h where it checks if playing those
 * moves on an empty board results in the same board which is being played.
 * In this case the function returns the next move from the library.
 * @param: The current playing board.
 * @param: The id of my bot.
 *
 * @return The move to be played
 */
Move C4Bot::openingMoves(const State board, int myBot)
{
    //Standard first move.
    if(round == 1 && myBot == 0 || round == 1 && myBot == 1 && state[5][3] == Player::None) return 3;

    //Loop through each move vector in the library and check if it`s alike to the current board.
    for(std::vector<int> moves : openingBook)
    {
        State temp = { { { { Player::None } } } };

        for(int i = 0; i < moves.size() - 1; i++)
        {
            temp = doMove(temp, moves[i]);
            if(temp == board && i % 2 == 0 && myBot == 1) return moves[i + 1];
            else if(temp == board && i % 2 != 0 && myBot == 0) return moves[i + 1];
        }
    }

    //If no results were found in the library run the alphaBeta algorithm.
    return ABHelper(state, 8);
}

//Start alpha beta
/**
 * This function evaluates the state of the board. It does so by using an
 * evaluation table defined in c4bot.h which gives points for a "chip" on a board position.
 * If it`s the opponents chip points get decreased if it`s the players chip points increase.
 * @param: The current player ie minimizing or maximizing.
 * @param: The current status of the playing board.
 *
 * @return The score of the board
 */
int C4Bot::evaluate(const Player player, const State board)
{
    Player opponent = (player == Player::X) ? Player::O : Player::X;

    if(getWinner(board) == player) return 10000;
    if(getWinner(board) == opponent) return -10000;

    int utility = 138;
    int score = 0;
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 7; j++)
            if (board[i][j] == player)
                score += C4Bot::evalTable[i][j];
            else if (board[i][j] == opponent)
                score -= C4Bot::evalTable[i][j];
    return utility + score;
}

/**
 * Recursive function that scores a position using the alpha beta algorithm.
 * @param: The current playing board.
 * @param: The current player.
 * @param: The search depth
 * @param: The value of the maximizing player
 * @Param: The value of the minimizing player
 *
 * @return The score and move to be played.
 */
std::vector<int> C4Bot::alphaBeta(const State &board, const Player &player, int depth, int alpha, int beta)
{
    //Get all the possible moves
    std::vector<Move> moves = getMoves(board);

    //If there is only one move left, return this move
    if(moves.size() == 1) return {0, moves.at(0)};

    int score;
    int bestMove = -1;

    //If max depth has been reached, score the board using the evaluation function
    if(depth == 0 || getWinner(board) != Player::None){
        score = evaluate(player, board);
        return {score,bestMove};
    }
    else
    {
        depth--;

        //For each move in moves
        for(Move m: moves)
        {
            //Apply the move to a temporary board.
            State tempboard = doMove(board, m);;

            //If player is maximizing player
            if(player == Player::O)
            {
                //Call recursively with the opposite player.
                score = alphaBeta(tempboard, Player::X, depth, alpha, beta)[0];

                //If the score is greater than alpha, alpha becomes score and bestmove is current move.
                if(score > alpha)
                {
                    alpha = score;
                    bestMove = m;
                }
            }
            //If player is minimizing player
            else
            {
                score = alphaBeta(tempboard, Player::O, depth, alpha, beta)[0];

                if(score < beta)
                {
                    beta = score;
                    bestMove = m;
                }
            }
            //Alpha beta pruning
            if(alpha >= beta) break;
        }
        //If current player is player O return alpha and best move, else return beta and best move.
        return {(player == Player::O) ? alpha : beta, bestMove};
    }
}

/**
 * Function that calls the alpha beta algorithm and returns the move or returns random move
 * if output from the algorithm was not correct.
 * @param: The current playing board.
 * @param: The search depth
 *
 * @return The move to be played
 */
Move C4Bot::ABHelper(const State &board, int depth)
{
    //Get the move using alpha beta algorithm.
    Move result = alphaBeta(board, getCurrentPlayer(board), depth, std::numeric_limits<int>::min(), std::numeric_limits<int>::max())[1];

    //If alpha beta algorithm fails to provide correct output return a random move.
    std::vector<Move> moves = getMoves(board);
    return {(result != -1) ? result : *select_randomly(moves.begin(), moves.end())};
}
//End alpha beta

void C4Bot::move(int timeout) {
    //For the first few moves use the openingMoves function, after that use alpha beta with iterative deepening.
    Move move;

    //Now for the first five rounds, if your library is better you can do more rounds.
    if(round <= 5){
        move = openingMoves(state, your_botid);
    }
    else if(round > 5)
    {
        int depth = 10;
        if(round % 2 == 0) depth += 1;
        move = ABHelper(state, depth);
    }

    std::cout << "place_disc " << move << std::endl;
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

