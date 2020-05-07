// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <ocr/image_transcriber.h>

namespace ocr {

ImageTranscriber::ImageTranscriber(const Classifier& classifier)
    : classifier(classifier) {}

Mat ImageTranscriber::OverlayTextOnImage(const Mat& input_image) {
  Mat processed_image = ProcessImage(input_image);

  vector<vector<cv::Point>> contours;
  cv::findContours(processed_image, contours,
                   cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
  vector<cv::Rect> text_areas = FindAreaWithText(processed_image);

  for (const auto& contour : contours) {
    cv::Rect boundingRect = cv::boundingRect(contour);
    // checking if contour corresponds to an actual character
    if (boundingRect.area() < kMinCharacterArea ||
        !DoRectanglesOverlap(boundingRect, text_areas)) {
      continue;
    }

    Mat character_region = processed_image(boundingRect);
    ocr::Character character(character_region);

    string predicted_character = string(1, classifier.Classify(character));
    cv::Point text_location(boundingRect.x, boundingRect.y);  // upper right corner
    int text_size = 5;
    int text_thickness = 3;
    cv::Scalar text_color(0, 255, 0);  // green
    cv::putText(input_image, predicted_character, text_location,
                cv::FONT_HERSHEY_SIMPLEX, text_size, text_color, text_thickness);
  }
  return input_image;
}

vector<cv::Rect> ImageTranscriber::FindAreaWithText(const Mat& input_image) {
  Mat image;
  cv::cvtColor(input_image, image, cv::COLOR_GRAY2BGR);
  vector<cv::Rect> rects;
  vector<cv::Rect> rects_with_text;
  vector<float> confidence;
  cv::text::TextDetectorCNN::create
      (kTestDetectionDescription, kTextDetectionModel)
          ->detect(image, rects, confidence);

  for (int i = 0; i < rects.size(); i++) {
    if (confidence[i] > kMinTextConfidence) {
      rects_with_text.push_back(rects[i]);
    }
  }
  return rects_with_text;
}

bool ImageTranscriber::DoRectanglesOverlap(const cv::Rect& rectangle,
                                           const vector<cv::Rect>& rect_list) {
  for (const cv::Rect& rect : rect_list) {
    if ((rectangle & rect).area() > 0) {
      return true;
    }
  }
  return false;
}

Mat ImageTranscriber::ProcessImage(const Mat& input_image) {
  Mat processed_image;
  cv::cvtColor(input_image, processed_image, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(processed_image, processed_image, cv::Size(5, 5), 0);
  cv::threshold(processed_image, processed_image, kMinPixelValue, kMaxPixelValue,
                cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
  return processed_image;
}

Mat ImageTranscriber::TranscribeImageFromFile(const std::string& file_path) {
  Mat input = cv::imread(file_path);
  if (input.empty()) {
    throw std::invalid_argument("Must pass in valid image file");
  }
  return OverlayTextOnImage(input);
}

Mat ImageTranscriber::TranscribeImageFromCamera() {
  cv::VideoCapture capture(0);
  Mat input;
  capture >> input;
  return OverlayTextOnImage(input);
}

}  // namespace ocr
