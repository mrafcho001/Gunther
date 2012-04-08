#ifndef BOXGRAPH_H
#define BOXGRAPH_H
#include "boxstorage.h"
#include <ostream>
#include <vector>
#include "chain.h"

#define DIR_LEFT    SIDE_LEFT
#define DIR_UP      SIDE_UP
#define DIR_RIGHT   SIDE_RIGHT
#define DIR_DOWN    SIDE_DOWN



class BoxGraph
{
public:
    BoxGraph();
    BoxGraph(BoxStorage* bs);

    void SelectBestMove();
    int BestMoveCol() const;
    int BestMoveRow() const;
    int BestMoveDir() const;

    friend std::ostream &operator<<(std::ostream& out, const BoxGraph &bg);


private:
    void fixDirection();
    void initVisited();
    void createFollowChain(int x, int y, Chain &chain);
    void createChains(int row, int col);
    void visit(int row, int col, Chain *chain);
    BoxStorage *_graph;
    std::vector<Chain> chains;
    bool visited[GRID_HEIGHT][GRID_WIDTH];
    int _bestMoveCol;
    int _bestMoveRow;
    short _bestMoveDir;
};

#endif // BOXGRAPH_H
