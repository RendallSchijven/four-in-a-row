//Node.h
//Rendall Schijven

#ifndef NODE_H
#define NODE_H

#include <vector>
#include "c4.h"

class Node;
typedef std::vector<Move> Moves;
typedef std::vector<Node*> Children;
class Node {
private:
    Node* parent;
    Children children;
    State state;
    Move move;
    double utility;
    int visits;
    int type;
public:
    Node(Node* parent, State state, Move , double utility, int visits, int type);
    Node(Node& node);
    void visit();
    void addUtility(int score);
    int getVisits();
    double getUtility();
    Node* getParent();
    State getState();
    Children* getChildren();
    void addChild(Node* n);
    Move getMove();
    ~Node();
};


#endif //NODE_H
