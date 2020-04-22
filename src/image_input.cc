// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <mylibrary/character.h>
#include <mylibrary/image_input.h>

#include <opencv2/opencv.hpp>
#include <vector>

namespace mylibrary {

vector<Character> extractCharacters(const Mat& input_image) {
  Mat processed_image = ProcessImage(input_image);

  vector<vector<cv::Point>> contours;
  cv::findContours(processed_image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
  std::vector<mylibrary::Character> characters;
  
  int character_num = 0;
  for (auto& contour : contours) {
    if (cv::contourArea(contour) < 3000 || cv::contourArea(contour) > 30000) {
      continue;
    }
    cv::Rect boundingRect = cv::boundingRect(contour);
    cv::rectangle(input_image, boundingRect, cv::Scalar(0, 255, 0), 2);
    Mat character_region = processed_image(boundingRect);
    cv::resize(character_region, character_region, cv::Size(28, 28), cv::INTER_AREA);
    mylibrary::Character character(character_region);

    cv::imshow(std::to_string(character_num), character_region);
    character_num++;
    characters.push_back(character);
  }
  cv::imshow("input", input_image);
  return characters;
}

Mat ProcessImage(const Mat& input_image) {
  Mat processed_image;
  cv::cvtColor(input_image, processed_image, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(processed_image, processed_image, cv::Size(5, 5), 0);
  cv::threshold(processed_image, processed_image, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
  cv::imshow("proccesed", processed_image);
  return processed_image;
}

vector<Character> extractCharactersFromFile(std::string file_path) {
  cv::Mat input = cv::imread(file_path);
  return extractCharacters(input);
}

// work in progress
void extractCharactersFromCamera() {
  cv::VideoCapture cap(0);

  while (true) {
    cv::Mat input;
    cap >> input;
    vector<Character> characters = extractCharacters(input);
    for (auto const & character : characters) {
      character.PrintPixels();
      std::cout<< "-----------------------------"<<std::endl;
    }
    cv::waitKey(1);
  }
}


}  // namespace mylibrary
