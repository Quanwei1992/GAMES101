//
// Created by Göksu Güvendiren on 2019-05-14.
//

#pragma once

#include "Vector.hpp"
#include "Light.hpp"
#include "global.hpp"

class AreaLight : public Light
{
public:
    AreaLight(const Vector3f &p, const Vector3f &i) : Light(p, i)
    {
        normal = Vector3f(0, -1, 0);
        u = Vector3f(1, 0, 0);
        v = Vector3f(0, 0, 1);
        length = 100;
    }

    Vector3f SamplePoint() const
    {
        auto random_u = get_random_float();
        auto random_v = get_random_float();
        return position + random_u * u + random_v * v;
    }

    float length;
    Vector3f normal;
    Vector3f u;
    Vector3f v;
};
