// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <ocr/image_transcriber.h>

namespace ocr {

ImageTranscriber::ImageTranscriber(const Classifier& classifier) : classifier(classifier) {}

Mat ImageTranscriber::ReadImage(const Mat& input_image) {
  Mat processed_image = ProcessImage(input_image);
  
  vector<vector<cv::Point>> contours;
  cv::findContours(processed_image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
  vector<cv::Rect> text_areas = FindAreaWithText(processed_image);
  
  for (const auto& contour : contours) {
    cv::Rect boundingRect = cv::boundingRect(contour);
    if (boundingRect.area() < 5000 || !DoesRectangleOverlap(boundingRect, text_areas)) {
      continue;
    }
    Mat character_region = processed_image(boundingRect);
    cv::dilate(character_region, character_region, cv::Mat(9, 9, 0));
    cv::resize(character_region, character_region, cv::Size(20, 20), cv::INTER_AREA);
    cv::copyMakeBorder(character_region, character_region,4, 4, 4, 4, cv::BORDER_CONSTANT);
    ocr::Character character(character_region);
    
    cv::putText(input_image, string(1, classifier.Classify(character)), 
                cv::Point(boundingRect.x, boundingRect.y),
                cv::FONT_HERSHEY_SIMPLEX, 5, cv::Scalar(0, 255, 0), 3);
  }
  return input_image;
}

vector<cv::Rect> ImageTranscriber::FindAreaWithText(const Mat& input_image) {
  Mat image;
  cv::cvtColor(input_image, image, cv::COLOR_GRAY2BGR);
  vector<cv::Rect> rects;
  vector<cv::Rect> viable_rects;
  vector<float> confidence;
  cv::text::TextDetectorCNN::create
      (text_detection_description, text_detection_model)
          ->detect(image, rects, confidence);
  
  for (int i = 0; i < rects.size(); i++) {
    if (confidence[i] > .5) {
      viable_rects.push_back(rects[i]);
    }
  }
  return rects;
}

bool ImageTranscriber::DoesRectangleOverlap(const cv::Rect& rectangle, 
                                            const vector<cv::Rect>& rect_list) {
  for (const cv::Rect& rect: rect_list) {
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
  cv::threshold(processed_image, processed_image, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
  return processed_image;
}

Mat ImageTranscriber::ReadImageFromFile(const std::string& file_path) {
  Mat input = cv::imread(file_path);
  if (input.empty()) {
    throw std::invalid_argument("Must pass in valid image file");
  }
  return ReadImage(input);
}

Mat ImageTranscriber::ReadImageFromCamera() {
  cv::VideoCapture cap(0);
  Mat input;
  cap >> input;
  return ReadImage(input);
}

}  // namespace ocr
