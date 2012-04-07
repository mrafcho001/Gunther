#ifndef BOXSTORAGE_H
#define BOXSTORAGE_H

#include <istream>

#define GRID_HEIGHT 5
#define GRID_WIDTH  5

#define SIDE_LEFT    0b0001   // 1 indicates line on that side of box
#define SIDE_UP      0b0010
#define SIDE_RIGHT   0b0100
#define SIDE_DOWN    0b1000

struct Coordinates {
    Coordinates(int x, int y) {
        X = x;
        Y = y;
    }
    int X;
    int Y;
};

class BoxStorage
{
public:
    BoxStorage();
    
    void MakeStorage(std::istream& cin);
    
    Coordinates BestPosition();
    
    int getLineCount(int x, int y);
    
    short getMask(int x, int y);

private:

    short _storage[GRID_HEIGHT][GRID_WIDTH];
    short int BoxCounts[GRID_HEIGHT][GRID_WIDTH];
};

#endif // BOXSTORAGE_H
