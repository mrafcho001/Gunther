#ifndef CHAIN_H
#define CHAIN_H

#include <vector>

#define SIDE_LEFT    0b0001   // 1 indicates line on that side of box
#define SIDE_UP      0b0010
#define SIDE_RIGHT   0b0100
#define SIDE_DOWN    0b1000

struct Coordinate
{
    short x;
    short y;
    bool branch_point;  //True if the point is the point of a 3 way branch

    Coordinate(): x(0), y(0), branch_point(false) { }
    Coordinate(short xi, short yi): x(xi), y(yi) { }
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
    Coordinate position();
    short direction();
    void removeFront();
private:
    std::vector<Coordinate> links;
    short _isLoop;
    short _loopType;
};

#endif // CHAIN_H
