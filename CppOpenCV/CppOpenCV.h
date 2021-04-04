#pragma once

#include <opencv2/opencv.hpp>

#include "ArgParse.h"

void ImageProcess(ArgumentParser& args) {
  // You can now use OpenCV!!
  //// Followings are sample code(you can delete it).
  cv::Mat image = cv::imread(args["in_file_path"].get()[0]);
  cv::line(image, cv::Point2d(629, 614), cv::Point2d(920, 445),
           cv::Scalar(255, 0, 128), 50);
  cv::imwrite(args["out_dir_path"].get()[0] + R"(\out.jpg)", image);
}