#include "boxstorage.h"

BoxStorage::BoxStorage()
{
}

BoxStorage::MakeStorage(istream& cin)
{
    int input;
    int tempStorage[GRID_HEIGHT][GRID_WIDTH];
    
    for (int i=0; i<(2*GRID_HEIGHT+1); i++) {
        for (int j=0; j<(2*GRID_WIDTH+1); j++) {
            cin >> tempStorage[i][j];
        }
    }
    
    for (int i=0; i<GRID_HEIGHT; i++) {
        for (int j=0; j<GRID_WIDTH; j++) {
            _storage[i][j] = 0b0000;
            
            if (tempStorage[2*i+1][2*j] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_LEFT;
            }
            
            if (tempStorage[2*i][2*j+1] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_UP;
            }
         
            if (tempStorage[2*i+1][2*j+2] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_RIGHT;
            }
            
            if (tempStorage[2*i+2][2*j+1] == 1) {
                _storage[i][j] = _storage[i][j] | SIDE_DOWN;
            }
        }
    }
}

BoxStorage::BestCoordinates()
{
    for (int i=0; i<GRID_HEIGHT; i++) {
        for (int j=0; i<GRID_WIDTH; j++) {
            if (BoxCounts[i][j] < 2) {
                if (!(_storage & SIDE_LEFT)) {
                    if ( (j==0) || ((j>0) && (BoxCounts[i][j-1]<2)) )
                        return Coordinates(2*i+1, 2*j);
                }
                if (!(_storage & SIDE_UP)) {
                    if ( (i==0) || ((i>0) && (BoxCounts[i-1][j]<2)) )
                        return Coordinates(2*i, 2*j+1);
                }
                if (!(_storage & SIDE_RIGHT)) {
                    if ( (j=GRID_WIDTH-1) || ((j<GRID_WIDTH-1) && (BoxCounts[i][j+1]<2)) ) {                              
                        return Coordinates(2*i+1, 2*j+2);
                    }
                }
                if (!(_storage & SIDE_DOWN)) {
                    if ( (i=GRID_HEIGHT-1) || ((i<GRID_HEIGHT-1) && (BoxCounts[i+1][j]<2)) ) {
                        return Coordinates(2*i+2, 2*j+1);
                    }
                }
            }
        }
    }
    
    return Coordinates(-1, -1);
}

