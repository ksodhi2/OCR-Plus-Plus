// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <opencv2/opencv.hpp>
#include "my_app.h"
#include <cinder/app/App.h>

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  cv::VideoCapture cap(0);

  cv::Mat edges;
  cv::namedWindow("edges",1);
  for(;;)
  {
    cv::Mat frame;
    cap >> frame; // get a new frame from camera
    cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
    cv::Canny(edges, edges, 0, 30, 3);
    imshow("edges", edges);
    if(cv::waitKey(30) >= 0) break;
  }
}

void MyApp::update() { }

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
