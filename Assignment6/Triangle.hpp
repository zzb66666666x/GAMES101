#pragma once

#include "BVH.hpp"
#include "Intersection.hpp"
#include "Material.hpp"
#include "OBJ_Loader.hpp"
#include "Object.hpp"
#include "Triangle.hpp"
#include <cassert>
#include <array>

//the class Triangle is supporting the MeshTriangle
//MeshTriangle is the list of triangles read from the 3D model
class Triangle : public Object
{
public:
    Vector3f v0, v1, v2; // vertices A, B ,C , counter-clockwise order
    Vector3f e1, e2;     // 2 edges v1-v0, v2-v0;
    Vector3f t0, t1, t2; // texture coords
    Vector3f normal;
    Material* m;

    Triangle(Vector3f _v0, Vector3f _v1, Vector3f _v2, Material* _m = nullptr)
        : v0(_v0), v1(_v1), v2(_v2), m(_m)
    {
        e1 = v1 - v0;
        e2 = v2 - v0;
        normal = normalize(crossProduct(e1, e2));
    }

    Intersection getIntersection(Ray ray) override;

    Vector3f evalDiffuseColor() const override;
    
    Bounds3 getBounds() override;
};

class MeshTriangle : public Object
{
public:
    MeshTriangle(const std::string& filename)
    {
        numTriangles = 0;
        objl::Loader loader;
        loader.LoadFile(filename);
        assert(loader.LoadedMeshes.size() == 1);
        auto mesh = loader.LoadedMeshes[0];
        Vector3f min_vert = Vector3f{std::numeric_limits<float>::infinity(),
                                     std::numeric_limits<float>::infinity(),
                                     std::numeric_limits<float>::infinity()};
        Vector3f max_vert = Vector3f{-std::numeric_limits<float>::infinity(),
                                     -std::numeric_limits<float>::infinity(),
                                     -std::numeric_limits<float>::infinity()};
        for (int i = 0; i < mesh.Vertices.size(); i += 3) {
            std::array<Vector3f, 3> face_vertices;
            for (int j = 0; j < 3; j++) {
                auto vert = Vector3f(mesh.Vertices[i + j].Position.X,
                                     mesh.Vertices[i + j].Position.Y,
                                     mesh.Vertices[i + j].Position.Z) *
                            60.f;
                face_vertices[j] = vert;

                min_vert = Vector3f(std::min(min_vert.x, vert.x),
                                    std::min(min_vert.y, vert.y),
                                    std::min(min_vert.z, vert.z));
                max_vert = Vector3f(std::max(max_vert.x, vert.x),
                                    std::max(max_vert.y, vert.y),
                                    std::max(max_vert.z, vert.z));
            }

            //material information
            auto new_mat =
                new Material(MaterialType::DIFFUSE_AND_GLOSSY,
                             Vector3f(0.5, 0.5, 0.5), Vector3f(0, 0, 0));   
            new_mat->Kd = 0.6;
            new_mat->Ks = 0.0;
            new_mat->specularExponent = 0;

            //four params passeed inside is actually the params needed for Triangle's constructor
            //the feature of emplace back here is actually about construct target object directly and push it
            //without calling copy constructor
            triangles.emplace_back(face_vertices[0], face_vertices[1],
                                   face_vertices[2], new_mat);
            numTriangles++;
        }
        bounding_box = Bounds3(min_vert, max_vert);
        std::vector<Object*> ptrs;
        for (auto& tri : triangles)
            ptrs.push_back(&tri);
        bvh = new BVHAccel(ptrs);
    }

    Bounds3 getBounds() { return bounding_box; }

    //not used function !!!
    Vector3f evalDiffuseColor() const {return Vector3f();}

    Intersection getIntersection(Ray ray)
    {
        //use bvh tree to make the intersection with small triangles inside mesh very fast
        Intersection intersec;
        if (bvh) {
            intersec = (this->bvh)->Intersect(ray);
        }
        return intersec;
    }

    //the bounding box of MeshTriangle will be processed together with spheres and the
    //bvh tree inside the scene will store these data
    //for triangles inside the mesh, their bounding boxes will be processed with other small triangles
    //and the bvh tree in the mesh will contain their data
    Bounds3 bounding_box;
    uint32_t numTriangles;
    std::vector<Triangle> triangles;
    BVHAccel* bvh;
    Material* m;
};

//concrete defintions of functions inside class Triangle

inline Bounds3 Triangle::getBounds() { return Union(Bounds3(v0, v1), v2); }

inline Intersection Triangle::getIntersection(Ray ray)
{
    Intersection inter;
    //implement Moller Trumbore Algorithm
    if (dotProduct(ray.direction, normal) > 0)
        return inter;
    double u, v, t_tmp = 0;
    Vector3f pvec = crossProduct(ray.direction, e2);
    double det = dotProduct(e1, pvec);
    if (fabs(det) < EPSILON)
        return inter;

    double det_inv = 1. / det;
    Vector3f tvec = ray.origin - v0;
    u = dotProduct(tvec, pvec) * det_inv;
    if (u < 0 || u > 1)
        return inter;
    Vector3f qvec = crossProduct(tvec, e1);
    v = dotProduct(ray.direction, qvec) * det_inv;
    if (v < 0 || u + v > 1)
        return inter;
    t_tmp = dotProduct(e2, qvec) * det_inv;

    // TODO find ray triangle intersection
    if (t_tmp>0){
        // fill in the info. of Intersection
        // bool happened;
        // Vector3f coords;
        // Vector3f normal;
        // double distance;
        // Object* obj;
        // Material* m;
        inter.happened = true;
        inter.coords = ray(t_tmp);
        inter.normal = normal;
        Vector3f light_path = inter.coords - ray.origin;
        inter.distance = dotProduct(light_path, light_path);
        inter.obj = this;
        inter.m = m;
    }
    return inter;
}

inline Vector3f Triangle::evalDiffuseColor() const
{
    return Vector3f(0.5, 0.5, 0.5);
}
