#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#define _USE_MATH_DEFINES

#include "config.h"
#include <cmath>
#include <bit>
#include <limits>

#include "utils/Vec3.h"
#include "utils/Vec2.h"
#include "utils/Para.h"





/*
    放一些常用的const常数，及常用的函数

*/
namespace solar
{

enum ParaPropertyId{

    kNothing=0,
    kSiteName,
    kLongitude,
    kLatitude,

    kSunShape,      //更改sunshape的类型
    kCSR,
    kSigma,
    kThetaMax,
    kAzimuth,
    kElevation,
    kIrradiance,
    kTrackable,

    kAttenuation,   //更改Attenuation的类型
    kBeta,

    kPosition,
    kAxis,
    kAngle,
    kPerspective,

    kGrid,
    kFill,
    kSteps,
    kDivision,
    kMin,
    kMax,
    kFile,

    kTranslation,
    kScale,

    kGeometry,      //更改Geometry的类型
    kA,  kB,  kC,
    kHeight,
    kRadius,
    kUpRadius,
    kDownRadius,

    kProfile,       //更改Profile的类型
    kRectU, kRectV,
    kCircleRadius, kCirclePhi,
    kRegularEdgeLength, kRegularEdgeCnt,
    kTriA, kTriB, kTriC,
    kPolyPoints,

    kMaterial,      //更改Material的类型

    kArmature,      //tracker中更改Armature的类型
    kPrimaryShift,
    kPrimaryAxis,
    kPrimaryAngles,
    kSecondaryShift,
    kSecondaryAxis,
    kSecondaryAngles,
    kFacetShift,
    kFacetNormal,
    kAngleDefault,
    kDrivePrimaryR,
    kDrivePrimaryP,
    kDriveSecondaryP,
    kDriveSecondaryS,

    kAimingType,        //Target的属性
    kAimingPoint

};

const double E = M_E;


PURE_FUNCTION constexpr auto inv_sqrt(double number) noexcept -> double
{
    static_assert(std::numeric_limits<double>::is_iec559); // (enable only
        // on IEEE 754)

    auto const y = std::bit_cast<double>(
        0x5fe6ec85e7de30da - (std::bit_cast<std::uint64_t>(number) >> 1));
    return y * (1.5 - (number * 0.5 * y * y));
}


}

#endif // UTILS_H
