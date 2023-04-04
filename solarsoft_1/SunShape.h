#ifndef SUNSHAPE_H
#define SUNSHAPE_H


#include<QDebug>

class SunShape
{
public:
    SunShape(){};
    virtual ~SunShape(){};

    virtual void testPrint()const =0;
    virtual void setPara(double para) =0;
    virtual double getPara() const=0;
};

class GaussionSunShape: public SunShape
{
public:
    GaussionSunShape(){};
    GaussionSunShape(double para):sigma(para){};

    virtual void setPara(double para) override;
    virtual double getPara() const override;
    virtual void testPrint()const override;


private:
    double sigma;
};

class PillboxSunShape:public SunShape
{
public:
    PillboxSunShape(){};
    PillboxSunShape(double para):theta_max(para){};

    virtual void setPara(double para) override;
    virtual double getPara() const override;
    virtual void testPrint()const override;

private:
    double theta_max;
};

class BuieSunShape: public SunShape
{
public:
    BuieSunShape(){ };
    BuieSunShape(double para):csr(para){ };

    virtual void setPara(double para) override;
    virtual double getPara() const override;
    virtual void testPrint()const override;

private:
    double csr;
};

#endif // SUNSHAPE_H
