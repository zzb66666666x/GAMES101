//
// Created by goksu on 2/25/20.
//
#include "Scene.hpp"

#pragma once

//not used in this project, we reframed the whole structure of the code
//we use class intersection to contain everything about the intersection info.
struct hit_payload
{
    float tNear;
    uint32_t index;
    Vector2f uv;
    Object* hit_obj;
};

class Renderer
{
//no data inside this class
//instead, we pass in the reference of scene and render it directly
public:
    void Render(const Scene& scene);

private:
};
