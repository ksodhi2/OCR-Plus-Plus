// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <opencv2/opencv.hpp>
#include <CinderImGui.h>
#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>
#include <portable-file-dialogs.h>
#include <ocr/image_transcriber.h>

using cinder::app::KeyEvent;
using ocr::KNN;

namespace ocr_app {

class OCRApp : public cinder::app::App {
 private:
  ocr::TrainingData training_data;
  ocr::ImageTranscriber image_transcriber;
  bool webcam_is_on = false;
  
 public:
  OCRApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
};

}  // namespace ocr_app

#endif  // FINALPROJECT_APPS_MYAPP_H_
