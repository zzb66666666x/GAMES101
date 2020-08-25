#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using std::string;

//Control points for Bezier Curve
std::vector<cv::Point2f> control_points;

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

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm
    return cv::Point2f();

}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.

}

int main(int argc, const char ** argv) 
{
    try{
        if (argc>3 || argc < 1){
            throw "invalid number of params";
        }
        cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
        cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
        cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);
        cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);
        string path = "../images/";
        string filename = "naive_bezier.png";
        bool use_naive_bezier = true;
        int key = -1;
        if (argc >= 2){
            //specify mode
            string mode = argv[1];
            if (mode != "naive"){
                if (mode == "recursive"){
                    use_naive_bezier = false;
                    filename = "recursive_bezier.png";
                    throw "not finished mode";
                }
                else {
                    throw "invalid mode";
                }
            }
            if(argc == 3){
                //specify filename
                string name = argv[2];
                filename = name;
            }
        }
        filename = path + filename;
        while (key != 27) {
            for (auto &point : control_points) {
                cv::circle(window, point, 3, {255, 255, 255}, 3);
            }

            if (control_points.size() == 4) {
                if (use_naive_bezier){
                    naive_bezier(control_points, window);
                }
                else{
                    bezier(control_points, window);
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
