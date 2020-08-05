//
// Created by goksu on 4/6/19.
//

#pragma once

#include "Triangle.hpp"
#include <algorithm>
#include <eigen3/Eigen/Eigen>
using namespace Eigen;

namespace rst {

//forced enum, we must use Buffers::Color or Buffers::Depth to use it.
enum class Buffers
{
    Color = 1,
    Depth = 2
};

//enable arithmetic of class Buffers
//reload operator bitwise or of class Buffers
//a = 01, b = 10, so a|b = 11 which doesn't belong to any names of class Buffers
inline Buffers operator|(Buffers a, Buffers b)
{
    //forced change of data type: from class Buffers to int
    //class Buffers won't accept implicit cast of data type here
    return Buffers((int)a | (int)b);
}

//enable arithmetic of class Buffers
//reload operator bitwise and of class Buffer
//a = 01, b = 10, so a&b = 00 which doesn't belong to any names of class Buffers
inline Buffers operator&(Buffers a, Buffers b)
{
    return Buffers((int)a & (int)b);
}

enum class Primitive
{
    Line,
    Triangle
};

/*
 * For the curious : The draw function takes two buffer id's as its arguments.
 * These two structs make sure that if you mix up with their orders, the
 * compiler won't compile it. Aka : Type safety
 * */
struct pos_buf_id
{
    int pos_id = 0;
};

struct ind_buf_id
{
    int ind_id = 0;
};

class rasterizer
{
  public:
    //constructor
    rasterizer(int w, int h);

    //std::vector<Eigen::Vector3f>: this is a vector cotaining 3D float vector as basic element
    //signature of std vector: std::vector<sometype>
    pos_buf_id load_positions(const std::vector<Eigen::Vector3f>& positions);
    ind_buf_id load_indices(const std::vector<Eigen::Vector3i>& indices);

    void set_model(const Eigen::Matrix4f& m);       //model = m
    void set_view(const Eigen::Matrix4f& v);        //view = v
    void set_projection(const Eigen::Matrix4f& p);  //projection = p

    //fill the rgb to the screen pos (x,y)
    void set_pixel(const Eigen::Vector3f& point, const Eigen::Vector3f& color); 

    void clear(Buffers buff);

    void draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, Primitive type);

    //interface function to get the frame buffer since frame_buf is private
    std::vector<Eigen::Vector3f>& frame_buffer() { return frame_buf; }

  private:
    void draw_line(Eigen::Vector3f begin, Eigen::Vector3f end);
    void rasterize_wireframe(const Triangle& t);

  private:
    Eigen::Matrix4f model;
    Eigen::Matrix4f view;
    Eigen::Matrix4f projection;

    //key value pairs, the dictionary
    //map the integer index numbers to 3D vectors
    std::map<int, std::vector<Eigen::Vector3f>> pos_buf;
    std::map<int, std::vector<Eigen::Vector3i>> ind_buf;

    std::vector<Eigen::Vector3f> frame_buf;     //rgb values
    std::vector<float> depth_buf;               //depth info.
    int get_index(int x, int y);

    int width, height;

    int next_id = 0;
    int get_next_id() { return next_id++; }
};
} // namespace rst
