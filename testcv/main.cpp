#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
 {
    char s[] = "Hi,Cpp.";
    int n = strlen(s);
    printf("%s:%d\n",s,n);

    cout << "Hello Opencv4.2" << endl;
    cout << cv::COLOR_RGB2BGRA << cv::COLOR_RGB2GRAY << endl;
    cv::Mat a = cv::imread("bilibili.jpg");
    cv::imshow("2233",a);
    cv::waitKey(0);
    return 0;
 }