// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include "ocr_app.h"

namespace ocr_app {

OCRApp::OCRApp()
    : training_data("data/emnist_training_data.csv"),
      image_transcriber(KNN(training_data, 11)) {}

void OCRApp::setup() {
  ImGui::initialize(ImGui::Options().itemSpacing(glm::vec2(40, 40)));
}

void OCRApp::update() {
  ImGui::Text("Welcome to OCR++\n"
      "Choose an option below to transcribe your image\n"
      "Press ESC to close out of the image");

  if (ImGui::Button("Transcribe Image From a File")) {
    auto dialog = pfd::open_file("Select a file", ".",
                                {"Image Files", "*.png *.jpg *.jpeg"}, false);
    if (!dialog.result().empty()) {
      Mat transcribed_image =
          image_transcriber.TranscribeImageFromFile(dialog.result()[0]);
      imshow("Transcribed Image", transcribed_image);
    }
  }

  if (ImGui::Button("Transcribe Images Live from a Webcam")) {
    is_webcam_on = true;
  }

  if (is_webcam_on) {
    Mat transcribed_image = image_transcriber.TranscribeImageFromCamera();
    cv::imshow("Live Image Transcription", transcribed_image);
  }
}

void OCRApp::draw() {
  cinder::gl::clear();
}

void OCRApp::keyDown(KeyEvent event) {
  if (event.getCode() == KeyEvent::KEY_ESCAPE) {
    is_webcam_on = false;
    cv::destroyAllWindows();
  }
}

}  // namespace ocr_app
