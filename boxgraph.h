#ifndef BOXGRAPH_H
#define BOXGRAPH_H
#include <boxstorage.h>
#include <ostream>
#include <vector>

#define DIR_LEFT    SIDE_LEFT
#define DIR_UP      SIDE_UP
#define DIR_RIGHT   SIDE_RIGHT
#define DIR_DOWN    SIDE_DOWN

struct Coordinate
{
    short x;
    short y;
    bool branch_point;  //True if the point is the point of a 3 way branch
};



class BoxGraph
{
public:
    BoxGraph();
    BoxGraph(BoxStorage* bs);

    void SelectBestMove();
    int BestMoveX() const;
    int BestMoveY() const;

    friend std::ostream &operator<<(std::ostream& out, const BoxGraph &bg);


private:
    void initVisited();
    void createFollowChain(int x, int y, Chain &chain);
    std::vector<Chain> createChains(int x, int y);
    BoxStorage *_graph;
    std::vector<Chain> chains;
    bool visited[GRID_HEIGHT][GRID_WIDTH];
    int _bestMoveX;
    int _bestMoveY;
};

#endif // BOXGRAPH_H
