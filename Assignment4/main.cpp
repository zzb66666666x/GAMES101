#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using std::string;

//Control points for Bezier Curve
//global definition
std::vector<cv::Point2f> control_points;

typedef enum color_theme{
    GREEN = 1,
    RED,
    BLUE
} COLOR;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 4) 
    {
        //collect four control points for Bezier Curve
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }     
}

void fill_pixel( cv::Mat &window, cv::Point2f point, COLOR color, bool use_anti_alias){
    if (use_anti_alias){
        window.at<cv::Vec3b>(point.y, point.x)[color] = 255;
    }
    else{
        window.at<cv::Vec3b>(point.y, point.x)[color] = 255;
    }
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window, bool use_anti_alias) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        //analytic solution for 3 order Bezier Curve
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;
        fill_pixel(window, point, RED, use_anti_alias);
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm
    int num_points = control_points.size(); //num_points = 4 in the first call
    bool final_phase = false;
    assert(num_points >= 2);
    if (num_points == 2){
        final_phase = true;
    }
    std::vector<cv::Point2f> next_call;
    for (int i=0; i<num_points-1; i++){
        auto& temp1 = control_points[i];
        auto& temp2 = control_points[i+1];
        next_call.push_back((1-t)*temp1+t*temp2);
    }
    if (final_phase){
        return next_call[0];
    }
    else{
        return recursive_bezier(next_call, t);
    }
}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window, bool use_anti_alias) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.
    double step_size = 0.001;
    for (double t=0.0; t<=1.0; t+=step_size){
        auto point = recursive_bezier(control_points, t);
        fill_pixel(window, point, GREEN, use_anti_alias);
    }
}

int main(int argc, const char ** argv) 
{
    try{
        if (argc>4 || argc < 1){
            throw "invalid number of params";
        }
        cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
        cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
        cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);
        cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);
        string path = "../images/";
        string filename = "naive_bezier.png";
        bool use_naive_bezier = true;
        bool use_anti_alias = false;
        int key = -1;
        if (argc >= 2){
            //specify mode
            string mode = argv[1];
            if (mode != "naive"){
                if (mode == "recursive"){
                    use_naive_bezier = false;
                    filename = "recursive_bezier.png";
                }
                else {
                    throw "invalid mode";
                }
            }
            if(argc >= 3){
                if (argv[2] == "AA_on"){
                    use_anti_alias = true;
                }
                else if (argv[2] == "AA_off"){
                    throw "invalid argument";
                }
                if (argc == 4){
                    //specify filename
                    string name = argv[3];
                    filename = name;
                }
            }
        }
        filename = path + filename;
        while (key != 27) {
            for (auto &point : control_points) {
                cv::circle(window, point, 3, {255, 255, 255}, 3);
            }

            if (control_points.size() == 4) {
                if (use_naive_bezier){
                    naive_bezier(control_points, window, use_anti_alias);
                }
                else{
                    bezier(control_points, window, use_anti_alias);
                }

                cv::imshow("Bezier Curve", window);
                cv::imwrite(filename, window);
                //The function waitKey waits for a key event infinitely (when delay ≤ 0 ).
                key = cv::waitKey(0);
                return 0;
            }

            cv::imshow("Bezier Curve", window);
            //The function waitKey waits for delay milliseconds, when param passed is positiv.
            key = cv::waitKey(20);
        }
        return 0;
    }
    catch (const char* msg){
        std::cout<<msg<<std::endl;
    }
}
