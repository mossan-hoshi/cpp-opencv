#include <iostream>
#include "ArgParse.h"
#include <opencv2/opencv.hpp>



int main()
{
    // You can now use OpenCV!!
    //// Followings are sample code(you can delete it).
    cv::Mat image = cv::Mat::zeros(100, 100, CV_8UC3);
    cv::line(image, cv::Point2d(0, 50), cv::Point2d(99, 50), cv::Scalar(255, 0, 128), 5);
    cv::imshow("result(image is also can watch by Image Watch(VS Extension))",image);
    cv::waitKey(0);
}
