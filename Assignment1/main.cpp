#include "Triangle.hpp"
#include "rasterizer.hpp"
#include <eigen3/Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

constexpr double MY_PI = 3.1415926;
using std::cos;
using std::sin;
using std::tan;
using std::abs;
using std::cout;
using std::endl;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos)
{   //In the main function, we define eye_pos: Eigen::Vector3f eye_pos = {0, 0, 5};
    Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1,
        -eye_pos[2], 0, 0, 0, 1;

    view = translate * view;

    return view;
}

Eigen::Matrix4f get_model_matrix(float rotation_angle)
{
    Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
    // TODO: Implement this function
    // Create the model matrix for rotating the triangle around the Z axis.
    // Then return it.
    float angle = rotation_angle/180*MY_PI;
    model(0,0) = cos(angle);
    model(0,1) = -sin(angle);
    model(1,0) = sin(angle);
    model(1,1) = cos(angle);
    return model;
}

Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar)
{
    // Students will implement this function
    Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();
    // TODO: Implement this function
    // Create the projection matrix for the given parameters.
    // Then return it.
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

    /* run: ./Rasterizer -r 20 image.png
     * here, the image.png is the argv[3] which tells the file name
     * -r 20 means rotating the triangle by 20 degree
     * simply run ./Rastertizer will enable you to rotate the triangle with keyboard
     */
    if (argc >= 3) {    //specified output filename
        cout<<"More than 3 args"<<endl;
        command_line = true;
        angle = std::stof(argv[2]); // -r by default, read the angle to rotate the triangle
        if (argc == 4) {
            cout<<"4 args"<<endl;
            filename = std::string(argv[3]);
        }
    }

    //Specify the size of screen
    rst::rasterizer r(700, 700);

    Eigen::Vector3f eye_pos = {0, 0, 5};

    std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};
    //three Eigen::Vector3f are contained in one std::vector
    std::vector<Eigen::Vector3i> ind{{0, 1, 2}};
    //one Eigen::Vector3i are contained in one std::vector

    //load the positions and indices to the rasterizer
    auto pos_id = r.load_positions(pos);        //should be 0 here
    auto ind_id = r.load_indices(ind);          //should be 1 here

    int key = 0;
    int frame_count = 0;

    if (command_line) {
        //save the rotated triangle into some image
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);
        //store the matrices needed for MVP Transform
        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));
        //core step is drawing
        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        //show the result
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        //store the image with filename
        cv::imwrite(filename, image);

        return 0;
    }
    //command_line is false
    //I want to rorate the triangle in the window
    while (key != 27) {
        //ESC(ASCII 27): out of loop
        r.clear(rst::Buffers::Color | rst::Buffers::Depth);
        //store matrices need into rasterizer for MVP Transformation
        r.set_model(get_model_matrix(angle));
        r.set_view(get_view_matrix(eye_pos));
        r.set_projection(get_projection_matrix(45, 1, 0.1, 50));
        //core step of drawing
        r.draw(pos_id, ind_id, rst::Primitive::Triangle);
        //draw the image with cv
        cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
        image.convertTo(image, CV_8UC3, 1.0f);
        cv::imshow("image", image);
        key = cv::waitKey(10);
        //next frame for animation
        std::cout << "frame count: " << frame_count++ << '\n';
        //A: left rotate 10 degree
        //B: right rotate 10 degree
        if (key == 'a') {
            angle += 10;
        }
        else if (key == 'd') {
            angle -= 10;
        }
    }

    return 0;
}
