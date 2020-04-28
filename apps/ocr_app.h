// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <opencv2/opencv.hpp>
#include <mylibrary/image_input.h>
#include <cinder/app/App.h>

namespace ocr_app {

class OCRApp : public cinder::app::App {
 public:
  OCRApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
};

}  // namespace ocr_app

#endif  // FINALPROJECT_APPS_MYAPP_H_
