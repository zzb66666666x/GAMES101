#pragma once

#include "BVH.hpp"
#include "Intersection.hpp"
#include "Material.hpp"
#include "OBJ_Loader.hpp"
#include "Object.hpp"
#include "Triangle.hpp"
#include <cassert>
#include <array>

class Triangle : public Object
{
public:
    Vector3f v0, v1, v2; // vertices A, B ,C , counter-clockwise order
    Vector3f e1, e2;     // 2 edges v1-v0, v2-v0;
    Vector3f t0, t1, t2; // texture coords
    Vector3f normal;
    float area;
    Material* m;

    Triangle(Vector3f _v0, Vector3f _v1, Vector3f _v2, Material* _m = nullptr)
        : v0(_v0), v1(_v1), v2(_v2), m(_m)
    {
        e1 = v1 - v0;
        e2 = v2 - v0;
        normal = normalize(crossProduct(e1, e2));
        area = crossProduct(e1, e2).norm()*0.5f;
    }

    Intersection getIntersection(Ray ray) override
    {
        Intersection inter;
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

    // not used function here (only overide the base class)
    Vector3f evalDiffuseColor(const Vector2f&) const override 
    {
        return Vector3f(0.5, 0.5, 0.5);
    }

    Bounds3 getBounds() override
    {
        return Union(Bounds3(v0, v1), v2); 
    }

    void Sample(Intersection &pos, float &pdf)
    {
        float x = std::sqrt(get_random_float()), y = get_random_float();
        pos.coords = v0 * (1.0f - x) + v1 * (x * (1.0f - y)) + v2 * (x * y);
        pos.normal = this->normal;
        pdf = 1.0f / area;
    }

    float getArea()
    {
        return area;
    }

    bool hasEmit()
    {
        return m->hasEmission();
    }
};

class MeshTriangle : public Object
{
public:
    Bounds3 bounding_box;
    std::unique_ptr<Vector3f[]> vertices;
    uint32_t numTriangles;
    std::unique_ptr<uint32_t[]> vertexIndex;
    std::unique_ptr<Vector2f[]> stCoordinates;
    std::vector<Triangle> triangles;
    BVHAccel* bvh;
    float area;
    Material* m;

    MeshTriangle(const std::string& filename, Material *mt = new Material())
    {
        numTriangles = 0;
        objl::Loader loader;
        loader.LoadFile(filename);
        area = 0;
        m = mt;
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
                                     mesh.Vertices[i + j].Position.Z);
                face_vertices[j] = vert;

                min_vert = Vector3f(std::min(min_vert.x, vert.x),
                                    std::min(min_vert.y, vert.y),
                                    std::min(min_vert.z, vert.z));
                max_vert = Vector3f(std::max(max_vert.x, vert.x),
                                    std::max(max_vert.y, vert.y),
                                    std::max(max_vert.z, vert.z));
            }

            triangles.emplace_back(face_vertices[0], face_vertices[1],
                                   face_vertices[2], mt);
            numTriangles++;
        }

        bounding_box = Bounds3(min_vert, max_vert);

        std::vector<Object*> ptrs;
        for (auto& tri : triangles){
            ptrs.push_back(&tri);
            area += tri.area;
        }
        bvh = new BVHAccel(ptrs);
    }

    Bounds3 getBounds() 
    {
        return bounding_box; 
    }

    // not used function here (only overide the base class)
    Vector3f evalDiffuseColor(const Vector2f &) const override
    {
        return Vector3f();
    }

    Intersection getIntersection(Ray ray)
    {
        Intersection intersec;
        if (bvh) {
            intersec = bvh->Intersect(ray);
        }
        return intersec;
    }
    
    void Sample(Intersection &pos, float &pdf)
    {
        bvh->Sample(pos, pdf);
        pos.emit = m->getEmission();
    }

    float getArea()
    {
        return area;
    }

    bool hasEmit()
    {
        return m->hasEmission();
    }
};


