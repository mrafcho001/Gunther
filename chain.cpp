#include "chain.h"

Chain::Chain() : _isLoop(-1)
{
}

void Chain::AddVertex(Coordinate &vertex)
{
    links.push_back(vertex);
}

bool Chain::isLoop()
{
    if (_isLoop == -1)
    {
        _isLoop = 0;
        
        for (int i=int(links.size()-1); i>0; i--) {
            if ((links[i].x == links[0].x) && (links[i].y == links[0].y)) {
                _isLoop = 1;
                break;
            }
        }
    }

    return _isLoop;
}

bool Chain::isOpenLoop()
{
    if (_loopType == -1)
    {
        _loopType = 1;
        
        for (int i=0; i<links.size(); i++) {
            if (links[i].branch_point) {
                _loopType = 0;
            }
        }
    }
    
    return (_loopType == 0);
}

bool Chain::isClosedLoop()
{
    return !this->isOpenLoop();
}

int Chain::length() const
{
    if(links.size() > 0)
    {
        if(_isLoop)
            return int(links.size()-1);
    }
    return int(links.size());
}

