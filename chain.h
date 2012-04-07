#ifndef CHAIN_H
#define CHAIN_H

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
