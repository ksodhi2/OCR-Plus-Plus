// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include "ocr_app.h"

namespace ocr_app {

using cinder::app::KeyEvent;

OCRApp::OCRApp() = default;

void OCRApp::setup() {
  mylibrary::TrainingData training_data("data/emnist_training_data.csv");

  mylibrary::KNN knn(training_data, 11);
  mylibrary::ImageTranscriber image_transcriber(knn);

  Mat transcribed_image = image_transcriber.ReadImageFromFile("assets/IMG_0690.jpeg");
  imshow("Transcribed Image", transcribed_image);
  
  //while (true) {
    //Mat live_trascribed_image = image_transcriber.ReadImageFromCamera();
    //cv::imshow("live_trascribed_image", live_trascribed_image);
    //cv::waitKey(1);
  //}

}

void OCRApp::update() { }

void OCRApp::draw() { }

void OCRApp::keyDown(KeyEvent event) { }

}  // namespace ocr_app
