//
// Created by LEI XU on 5/13/19.
//
#pragma once
#ifndef RAYTRACING_OBJECT_H
#define RAYTRACING_OBJECT_H

#include "Vector.hpp"
#include "global.hpp"
#include "Bounds3.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"

//class Object
// <-- class Sphere
// <-- class MeshTriangle
// <-- class Triangle
//at the same time
//list of Triangle objects --> data of MeshTriangle
class Object
{
public:
    Object() {}
    virtual ~Object() {}
    virtual Intersection getIntersection(Ray _ray) = 0;
    virtual Vector3f evalDiffuseColor() const =0;
    virtual Bounds3 getBounds()=0;
};



#endif //RAYTRACING_OBJECT_H
