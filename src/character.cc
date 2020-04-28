// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <ocr/character.h>

namespace ocr {

Character::Character(): pixels_(kCharacterSize, std::vector<size_t>(kCharacterSize)) {}

Character::Character(const cv::Mat& character_image) : Character() {
  if (character_image.rows != kCharacterSize 
      || character_image.cols != kCharacterSize) {
    throw std::invalid_argument("Must pass in 28x28 image");
  }
  
  for (size_t row = 0; row < character_image.rows; row++) {
    for (size_t col = 0; col < character_image.cols; col++) {
      size_t pixel_value = static_cast<int>(character_image.at<uchar>(row, col));
      pixels_[row][col] = pixel_value;
    }
  }
}

void Character::FillPixel(size_t value, size_t row, size_t col) {
  pixels_[row][col] = value;
}

int Character::PixelValueAt(size_t row, size_t col) const { 
  return pixels_[row][col]; 
}

std::ostream& operator<<(std::ostream& os, const Character& character) {
  for (size_t row = 0; row < kCharacterSize; row++) {
    for (size_t col = 0; col < kCharacterSize; col++) {
      int pixel_value = character.pixels_[row][col];
      if (pixel_value >= 128) {
        os.put('#');
      } else {
        os.put(' ');
      }
    }
    os.put('\n');
  }
  return os;
}

}  // namespace ocr

