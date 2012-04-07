#include "boxstorage.h"

BoxStorage::BoxStorage()
{
}

void BoxStorage::MakeStorage(std::istream& cin)
{
    int tempStorage[GRID_HEIGHT][GRID_WIDTH];
    
    for (int i=0; i<(2*GRID_HEIGHT+1); i++) {
        for (int j=0; j<(2*GRID_WIDTH+1); j++) {
            cin >> tempStorage[i][j];
        }
    }
    
    for (int i=0; i<GRID_HEIGHT; i++) {
        for (int j=0; j<GRID_WIDTH; j++) {
            _storage[i][j] = 0b0000;
            BoxCounts[i][j] = 0;
            
            if (tempStorage[2*i+1][2*j] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_LEFT;
                BoxCounts[i][j]++;
            }
            
            if (tempStorage[2*i][2*j+1] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_UP;
                BoxCounts[i][j]++;
            }
         
            if (tempStorage[2*i+1][2*j+2] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_RIGHT;
                BoxCounts[i][j]++;
            }
            
            if (tempStorage[2*i+2][2*j+1] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_DOWN;
                BoxCounts[i][j]++;
            }
        }
    }
}

Coordinates BoxStorage::BestPosition()
{
    for (int i=0; i<GRID_HEIGHT; i++) {
        for (int j=0; i<GRID_WIDTH; j++) {
            if (BoxCounts[i][j] < 2) {
                if (!(_storage[i][j] & SIDE_LEFT)) {
                    if ( (j==0) || ((j>0) && (BoxCounts[i][j-1]<2)) )
                    {
                        Coordinates value(2*i+1, 2*j);
                        return value;
                    }
                }
                if (!(_storage[i][j] & SIDE_UP)) {
                    if ( (i==0) || ((i>0) && (BoxCounts[i-1][j]<2)) )
                    {
                        Coordinates value(2*i, 2*j+1);
                        return value;
                    }
                }
                if (!(_storage[i][j] & SIDE_RIGHT)) {
                    if ( (j=GRID_WIDTH-1) || ((j<GRID_WIDTH-1) && (BoxCounts[i][j+1]<2)) ) {
                        Coordinates value(2*i+1, 2*j+2);
                        return value;
                    }
                }
                if (!(_storage[i][j] & SIDE_DOWN)) {
                    if ( (i=GRID_HEIGHT-1) || ((i<GRID_HEIGHT-1) && (BoxCounts[i+1][j]<2)) ) {
                        Coordinates value(2*i+2, 2*j+1);
                        return value;
                    }
                }
            }
        }
    }
    
    return Coordinates(-1, -1);
}

int BoxStorage::getLineCount(int x, int y)
{
    return BoxCounts[x][y];
}

<<<<<<< HEAD
=======
short BoxStorage::getMask(int x, int y)
{
    return 
}

>>>>>>> Added BoxStorage
