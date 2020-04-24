// Copyright 2020 [Karan Sodhi]. All rights reserved.

#ifndef FINALPROJECT_CHARACTER_H
#define FINALPROJECT_CHARACTER_H


#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

namespace mylibrary {
  
const size_t kCharacterSize = 28;

class Character {
 private:
  std::vector<std::vector<int>> pixels_;
  
 public:
  Character(cv::Mat character_image);
  Character();
  void PrintPixels() const;
  void FillPixel(int value, int row, int col);
};

}  // namespace mylibrary


#endif  // FINALPROJECT_CHARACTER_H
