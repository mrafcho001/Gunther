#ifndef BOXSTORAGE_H
#define BOXSTORAGE_H

#include <istream.h>

#define GRID_HEIGHT 5
#define GRID_WIDTH  5

#define SIDE_LEFT    0b0001   // 1 indicates line on that side of box
#define SIDE_UP      0b0010
#define SIDE_RIGHT   0b0100
#define SIDE_DOWN    0b1000

class BoxStorage
{
public:
    BoxStorage();
    
    MakeStorage(istream& cin);

private:
    short _storage[GRID_HEIGHT][GRID_WIDTH];

};

#endif // BOXSTORAGE_H