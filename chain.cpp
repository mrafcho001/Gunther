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
        int dx = links[links.size()-1].x - links[0].x;
        if(dx < 0) dx = -dx;
        int dy = links[links.size()-1].y - links[0].y;
        if(dy < 0) dy = -dy;
        if ( dx+dy == 1)
        {
            _isLoop = 1;
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
        if(_isLoop >= 0)
            return int(links.size()-1);
    }
    return int(links.size());
}

Coordinate Chain::position()
{
    return links[0];
}

short Chain::direction()
{
    if(links.size() == 1)
        return 0;

    if(links[1].x > links[0].x)
    {
        return SIDE_RIGHT;
    }
    if(links[1].x < links[0].x)
    {
        return SIDE_LEFT;
    }
    if(links[1].y > links[0].y)
    {
        return SIDE_DOWN;
    }
    if(links[1].y < links[0].y)
    {
        return SIDE_UP;
    }
    return 0;
}

void Chain::removeFront()
{
    links.erase(links.begin());
}
