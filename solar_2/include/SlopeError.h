
#ifndef SLOPEERROR_H
#define SLOPEERROR_H


namespace solar{

class SlopeError
{
public:
    SlopeError();
};

class GaussianSlopeError : public SlopeError
{
public:
    GaussianSlopeError();
};


class PillboxSlopeError :public SlopeError
{
public:
    PillboxSlopeError();
};

}   //namespace solar

#endif // SLOPEERROR_H
