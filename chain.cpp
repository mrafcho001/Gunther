#include "chain.h"

Chain::Chain() : _isLoop(-1)
{
}

void Chain::AddVertex(Coordinate &vertex)
{
    links.push_back(vertex);
}

bool Chain::isLoop() const
{
    if(_isLoop == -1)
    {
        //Calculate
    }

    return _isLoop;
}

bool Chain::isOpenLoop() const
{
    return (_loopType == 0);
}

bool Chain::isClosedLoop() const
{
    return (_loopType == 1);
}

int Chain::length() const
{
    if(links.size() > 0)
    {
        if(links[0].branch_point)
            return links.size()-1;
    }
    return links.size();
}
