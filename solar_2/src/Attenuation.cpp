
#include "Attenuation.h"
#include "Utils.h"


namespace solar{

    auto VacuumAttenuation::getValue(double d)const ->double
    {
        return 1.0 ;
    }

    auto ExponentialAttenuation::getValue(double d)const ->double
    {
        double exponent = -(1.0696 * 1e-5 + 9.196 * 1e-4 * beta) * d;
        double ret = pow(E,exponent);
        return ret;
    }

    auto CustomAttenuation::getValue(double d)const ->double
    {
        double ret;
        if( d<=1000 )
        {
            ret = 0.99331 - 1.176*1e-4*d + 1.97*1e-8*d*d;
        }
        else ret = pow( E, -0.0001106 * d );
        return ret;
    }
}


