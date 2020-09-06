//
// Created by goksu on 2/25/20.
//
#include "Scene.hpp"

#pragma once

class Renderer
{
//no data inside this class
//instead, we pass in the reference of scene and render it directly
public:
    void Render(const Scene& scene);

private:
};
