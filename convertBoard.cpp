//
// Created by renda on 3-4-2018.
//

#include "convertBoard.h"

#include <iostream>
#include <sstream>
#include <chrono>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

int main() {
    int i = 1;
    while(i != 0){
        std::vector<int> moves;

        std::string input;
        std::cout << "Enter moves: " << std::endl;
        std::cin >> input;

        for(int i = 0; i < input.size(); ++i)
        {
            int move = input[i];
            moves.push_back(move - 49);
        }

        std::cout << "{";
        for(std::vector<int>::const_iterator i = moves.begin(); i != moves.end(); i++){
            if(i == moves.end() - 1) std::cout << *i;
            else std::cout << *i << ",";
        }
        std::cout << "}" << std::endl;
    }

    return 0;
}
