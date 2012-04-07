#ifndef CHAIN_H
#define CHAIN_H

#include <vector>

struct Coordinate
{
    short x;
    short y;
    bool branch_point;  //True if the point is the point of a 3 way branch
};

class Chain
{
public:
    Chain();
    void AddVertex(Coordinate &vertex);
    bool isLoop();
    bool isOpenLoop();
    bool isClosedLoop();
    int length() const;
private:
    std::vector<Coordinate> links;
    short _isLoop;
    short _loopType;
};

#endif // CHAIN_H
