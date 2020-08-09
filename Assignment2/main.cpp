// clang-format off
#include <iostream>
#include <opencv2/opencv.hpp>
#include "rasterizer.hpp"
#include "global.hpp"
#include "Triangle.hpp"

constexpr double MY_PI = 3.1415926;
using std::cout;
using std::endl;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1,0,0,-eye_pos[0],
                 0,1,0,-eye_pos[1],
                 0,0,1,-eye_pos[2],
                 0,0,0,1;

    view = translate*view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio, float zNear, float zFar)
{
    // TODO: Copy-paste your implementation from the previous assignment.
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
    float t = tan(eye_fov/2) * abs(zNear);
    float b = -t;
    float r = aspect_ratio * t;
    float l = -r;
    Eigen::Matrix4f trans;
    Eigen::Matrix4f scale;
    trans<<1,0,0,(-(r+l)/2),
           0,1,0,(-(t+b)/2),
           0,0,1,(-(zNear+zFar)/2),
           0,0,0,1;
    scale<<(2/(r-l)),0,0,0,
           0,(2/(t-b)),0,0,
           0,0,(2/(zNear-zFar)),0,
           0,0,0,1;
    Eigen::Matrix4f ortho = scale * trans;
    Eigen::Matrix4f persp;
    persp<<zNear, 0,0,0,
           0,zNear,0,0,
           0,0,zFar+zNear,-(zFar*zNear),
           0,0,1,0;
    projection = ortho * persp;
    return projection;
}

int main(int argc, const char** argv)
{
    float angle = 0;
    bool command_line = false;
    std::string filename = "output.png";

    if (argc == 2)
    {
        command_line = true;
        filename = std::string(argv[1]);
    }

    cout<<"rasterizer initialization"<<endl;
    rst::rasterizer r(700, 700);

    cout<<"getting eye position"<<endl;
    Eigen::Vector3f eye_pos = {0,0,5};


    //define two triangles which contains 6 vertices
    //we need a vector of vertices and also a vector of indices 
    //to tell the order or vertices within one triangle
    cout<<"defining triangles"<<endl;
    std::vector<Eigen::Vector3f> pos
            {
                    {2, 0, -2},
                    {0, 2, -2},
                    {-2, 0, -2},
                    {3.5, -1, -5},
                    {2.5, 1.5, -5},
                    {-1, 0.5, -5}
            };

    std::vector<Eigen::Vector3i> ind
            {
                    {0, 1, 2},
                    {3, 4, 5}
            };

    //two triangles, 6 vertices, need 6 colors
    std::vector<Eigen::Vector3f> cols
            {
                    {217.0, 238.0, 185.0},
                    {217.0, 238.0, 185.0},
                    {217.0, 238.0, 185.0},
                    {185.0, 217.0, 238.0},
                    {185.0, 217.0, 238.0},
                    {185.0, 217.0, 238.0}
            };

    //load the vertices and its index and color into rasterizer
    cout<<"loading information into rasterizer"<<endl;
    auto pos_id = r.load_positions(pos);
    auto ind_id = r.load_indices(ind);
    auto col_id = r.load_colors(cols);

    int key = 0;
    int frame_count = 0;

    if (command_line)
    {
        cout<<"using command line"<<endl;
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);
        
        cout<<"loading matrices for MVP transformation"<<endl;
        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        cout<<"draw triangles by rasteriazer"<<endl;
        r.draw(pos_id, ind_id, col_id, rst::Primitive::Triangle);
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);

        cv::imwrite(filename, image);

        return 0;
    }

    cout<<"real time operation mode"<<endl;
    while(key != 27)
    {
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);

        cout<<"loading matrices for MVP transformation"<<endl;
        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

        cout<<"draw triangles by rasteriazer"<<endl;
        r.draw(pos_id, ind_id, col_id, rst::Primitive::Triangle);

        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
        cv::imshow("image", image);
        key = cv::waitKey(10);

        std::cout << "frame count: " << frame_count++ << '\n';
    }

    return 0;
}
// clang-format on