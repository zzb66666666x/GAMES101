// clang-format off
//
// Created by goksu on 4/6/19.
//

#include <algorithm>
#include <vector>
#include "rasterizer.hpp"
#include <opencv2/opencv.hpp>
#include <math.h>

using std::cout;
using std::endl;

//link the two triangles with one id number 
rst::pos_buf_id rst::rasterizer::load_positions(const std::vector<Eigen::Vector3f> &positions)
{
    auto id = get_next_id();
    pos_buf.emplace(id, positions);

    return {id};
}

rst::ind_buf_id rst::rasterizer::load_indices(const std::vector<Eigen::Vector3i> &indices)
{
    auto id = get_next_id();
    ind_buf.emplace(id, indices);

    return {id};
}

rst::col_buf_id rst::rasterizer::load_colors(const std::vector<Eigen::Vector3f> &cols)
{
    auto id = get_next_id();
    col_buf.emplace(id, cols);

    return {id};
}

auto to_vec4(const Eigen::Vector3f& v3, float w = 1.0f)
{
    return Vector4f(v3.x(), v3.y(), v3.z(), w);
}


bool insideTriangle(int x, int y, const Vector3f* _v)
{   
    // TODO : Implement this function to check if the point (x, y) is inside the triangle represented by _v[0], _v[1], _v[2]
    float pos_x = x + 0.5f;
    float pos_y = y + 0.5f;
    float pos_z = 0;
    Eigen::Vector3f P(pos_x, pos_y, pos_z);
    Eigen::Vector3f A = _v[0];
    Eigen::Vector3f B = _v[1];
    Eigen::Vector3f C = _v[2];
    A.z() = pos_z;
    B.z() = pos_z;
    C.z() = pos_z;
    Eigen::Vector3f AB = B-A;
    Eigen::Vector3f BC = C-B;
    Eigen::Vector3f CA = A-C;
    Eigen::Vector3f AP = P-A;
    Eigen::Vector3f BP = P-B;
    Eigen::Vector3f CP = P-C;
    if ((AB.cross(AP).z()>0)&&(BC.cross(BP).z()>0)&&(CA.cross(CP).z()>0)){
        return true;
    }
    return false;
}

static std::tuple<float, float, float> computeBarycentric2D(float x, float y, const Vector3f* v)
{
    float c1 = (x*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*y + v[1].x()*v[2].y() - v[2].x()*v[1].y()) / (v[0].x()*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*v[0].y() + v[1].x()*v[2].y() - v[2].x()*v[1].y());
    float c2 = (x*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*y + v[2].x()*v[0].y() - v[0].x()*v[2].y()) / (v[1].x()*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*v[1].y() + v[2].x()*v[0].y() - v[0].x()*v[2].y());
    float c3 = (x*(v[0].y() - v[1].y()) + (v[1].x() - v[0].x())*y + v[0].x()*v[1].y() - v[1].x()*v[0].y()) / (v[2].x()*(v[0].y() - v[1].y()) + (v[1].x() - v[0].x())*v[2].y() + v[0].x()*v[1].y() - v[1].x()*v[0].y());
    return {c1,c2,c3};
}

void rst::rasterizer::draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer, col_buf_id col_buffer, Primitive type)
{
    //fetch three important components (aka. vertices, indices, color) from three hash maps
    //hash maps are: pos_buf，ind_buf，col_buf
    
    /************************************************************************************
    * the 3D model may also be formed by different components
    * for example, a scene on a desk, we may need to draw a cake and few cups of coffee
    * these object represents different terms inside the hash tables
    * we previously registered all the objects we need to draw in the main()
    * by calling draw() once, we can draw one small object
    * therefore, the three hash maps inside rasterizer contains everything about a 3D scene
    * 
    * one object(eg. a cup of coffee) is also formed by many triangles
    * so we have to pass in id numbers to fetch terms from hash maps
    * so the buf, ind, col below may mean all the info. needed for drawing a cup
    * this cup is described by vertices, colors and even normal vectors (if necessary)
    *************************************************************************************/
    auto& buf = pos_buf[pos_buffer.pos_id]; // a std vector containing 6 vertices
    auto& ind = ind_buf[ind_buffer.ind_id]; // a std vector contating two vectors of indices
    auto& col = col_buf[col_buffer.col_id]; // a std vector containing 6 vertices

    /*************************************************************************************************************
    * How to use buf, ind, col?
    * col, buf are two databases, they contain all the information(position&color) needed for this draw operation
    * ind is a data structure to store index numbers, the number of Eigen::Vector3i inside determines the number
    * of triangles needed to draw for one draw() operation
    * illustration:
    *   ind: {0,1,2}, {3,4,5}, ..., {102,232,342}   <-- all the triangles
    *       for the first triangle {0,1,2}:
    *             0               1               2
    *       col[0],buf[0]   col[1],buf[1]   col[2],buf[2]
    *   col: RGB,RGB,RGB,...,RGB   buf: xyz, xyz, xyz,...,xyz
    * 
    *   after the first triangle, we will loop through the rest and build all the triangles
    **************************************************************************************************************/

    float f1 = (50 - 0.1) / 2.0;
    float f2 = (50 + 0.1) / 2.0;

    Eigen::Matrix4f mvp = projection * view * model;

    //Remember that ind is a std vector containing two Eigen::Vector3i objects
    //therefore this for loop goes two times for this project
    //also, in this project, the scene we draw is actually composed of 2 triangles
    //we draw them within one rst::draw() operation
    for (auto& i : ind)
    {
        /*********************************************************************************************************
        * type of i is Eigen::Vector3i
        * i[j] (0<=j<=2), gives the place where you can find the correct position/color information
        * for example, the triangle I want to draw has indices {67,80,101}, then i = [67,80,101]
        * i[0],i[1],i[2] are index numbers for one triangle's three vertices
        * while the buf and col are like two database for all possible RGB values and positions in space
        * Consequently:
        * col[i[0]] means col[67], by looking into the 67'th position of std vector col, you get the RGB values out
        ***********************************************************************************************************/

        cout<<"drawing one triangle"<<endl;
        cout<<"doing transformation to move into screen space"<<endl;
        Triangle t;
        Eigen::Vector4f v[] = {
                mvp * to_vec4(buf[i[0]], 1.0f),
                mvp * to_vec4(buf[i[1]], 1.0f),
                mvp * to_vec4(buf[i[2]], 1.0f)
        };
        //Homogeneous division
        for (auto& vec : v) {
            vec /= vec.w();
        }
        //Viewport transformation
        for (auto & vert : v)
        {
            vert.x() = 0.5*width*(vert.x()+1.0);
            vert.y() = 0.5*height*(vert.y()+1.0);
            vert.z() = vert.z() * f1 + f2;
            cout<<"checking"<<vert.z()<<endl;
        }

        cout<<"showing vertices of the triangle"<<endl;
        cout<<v[0].head<3>().transpose()<<endl;
        cout<<v[1].head<3>().transpose()<<endl;
        cout<<v[2].head<3>().transpose()<<endl;
        for (int i = 0; i < 3; ++i)
        {
            t.setVertex(i, v[i].head<3>());
            t.setVertex(i, v[i].head<3>());
            t.setVertex(i, v[i].head<3>());
        }

        auto col_x = col[i[0]];
        auto col_y = col[i[1]];
        auto col_z = col[i[2]];

        t.setColor(0, col_x[0], col_x[1], col_x[2]);
        t.setColor(1, col_y[0], col_y[1], col_y[2]);
        t.setColor(2, col_z[0], col_z[1], col_z[2]);
        cout<<"showing color of the triangle"<<endl;
        cout<<t.color[0].transpose()<<endl;
        cout<<t.color[1].transpose()<<endl;
        cout<<t.color[2].transpose()<<endl;
        cout<<"finished setting information of one triangle, ready to rasterize it"<<endl;

        rasterize_triangle(t);
    }
}

//Screen space rasterization
void rst::rasterizer::rasterize_triangle(const Triangle& t) {
    //WARNING: t.v is a pointer to Eigen::Vector3f and v is a std array of three Eigen::Vector4f objects
    auto v = t.toVector4(); 
    float x_min, x_max, y_min, y_max, temp_x, temp_y;
    Eigen::Vector3f rgb;
    Eigen::Vector3f point;
    x_min = v[0].x();
    x_max = x_min;
    y_min = v[0].y();
    y_max = y_min;
    // TODO : Find out the bounding box of current triangle.
    for (int i=1; i<3; i++){
        temp_x = v[i].x();
        temp_y = v[i].y();
        if (temp_x<x_min){x_min = temp_x;}
        else if (temp_x>x_max){x_max = temp_x;}
        if (temp_y<y_min){y_min = temp_y;}
        else if (temp_y>y_max){y_max = temp_y;}
    } 
    if ((x_min<0)||(x_max<0)||(y_min<0)||(y_max<0)){
        throw "invalid position for pixels";
    }
    // iterate through the pixel and find if the current pixel is inside the triangle
    unsigned int x_begin, x_end, y_begin, y_end;
    x_begin = (uint)floor(x_min);
    x_end = (uint)ceil(x_max);
    y_begin = (uint)floor(y_min);
    y_end = (uint)ceil(y_max);
    cout<<"x is from "<<x_begin<<" to "<<x_end<<endl;
    cout<<"y is from "<<y_begin<<" to "<<y_end<<endl;
    for (int x = (int)x_begin; x<x_end; x++){
        for (int y = (int)y_begin; y<y_end; y++){
            if(insideTriangle(x,y,t.v)){
                // If so, use the following code to get the interpolated z value.
                auto[alpha, beta, gamma] = computeBarycentric2D(x, y, t.v);
                float w_reciprocal = 1.0/(alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
                float z_interpolated = alpha * v[0].z() / v[0].w() + beta * v[1].z() / v[1].w() + gamma * v[2].z() / v[2].w();
                z_interpolated *= w_reciprocal;
                // TODO : set the current pixel (use the set_pixel function) to the color of the triangle 
                // (use getColor function) if it should be painted.
                point<<(float)x, (float)y, z_interpolated;
                rgb = t.color[0]*255;
                //z-buffer algorithm
                int ind = (height-1-y)*width + x;
                if (depth_buf[ind]>abs(z_interpolated)){
                    set_pixel(point, rgb);
                }
            }
        }
    }
}

void rst::rasterizer::set_model(const Eigen::Matrix4f& m)
{
    model = m;
}

void rst::rasterizer::set_view(const Eigen::Matrix4f& v)
{
    view = v;
}

void rst::rasterizer::set_projection(const Eigen::Matrix4f& p)
{
    projection = p;
}

/***********************************
* binary code of rst::Buffers buff
* 11: clear all, including frame_buf and depth_buf
* 00: do nothing
* 01: only clear the frame_buf
* 10: only clear the depth_buf
************************************/
void rst::rasterizer::clear(rst::Buffers buff)
{
    if ((buff & rst::Buffers::Color) == rst::Buffers::Color)
    {
        std::fill(frame_buf.begin(), frame_buf.end(), Eigen::Vector3f{0, 0, 0});
    }
    if ((buff & rst::Buffers::Depth) == rst::Buffers::Depth)
    {
        std::fill(depth_buf.begin(), depth_buf.end(), std::numeric_limits<float>::infinity());
    }
}

rst::rasterizer::rasterizer(int w, int h) : width(w), height(h)
{
    frame_buf.resize(w * h);
    depth_buf.resize(w * h);
}

int rst::rasterizer::get_index(int x, int y)
{
    return (height-1-y)*width + x;
}

void rst::rasterizer::set_pixel(const Eigen::Vector3f& point, const Eigen::Vector3f& color)
{
    //old index: auto ind = point.y() + point.x() * width;
    auto ind = (height-1-point.y())*width + point.x();
    frame_buf[ind] = color;

}

// clang-format on