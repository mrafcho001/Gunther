#ifndef CHAIN_H
#define CHAIN_H

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
    bool isLoop() const;
    bool isOpenLoop() const;
    bool isClosedLoop() const;
    int length() const;
    int chainPointCount();
private:
    std::vector<Coordinate> links;
    short _isLoop;
    short _loopType;
};

#endif // CHAIN_H
