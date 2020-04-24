// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <mylibrary/character.h>
#include <iostream>

namespace mylibrary {

Character::Character() {
  pixels_.resize(kCharacterSize, std::vector<int>(kCharacterSize));
}

/**
 * Fills the pixel array with a '#' if the pixel at (row, col) of the 28x28
 * image is black and ' ' if the pixel is white.
 */
Character::Character(cv::Mat character_image) {
  pixels_.resize(kCharacterSize, std::vector<int>(kCharacterSize));
  for (int row = 0; row < character_image.rows; row++) {
    for (int col = 0; col < character_image.cols; col++) {
      int pixel_value = static_cast<int>(character_image.at<uchar>(row, col));
      pixels_[row][col] = pixel_value;
    }
  }
}

void Character::PrintPixels() const {
  for (int row = 0; row < kCharacterSize; row++) {
    for (int col = 0; col < kCharacterSize; col++) {
      int pixel_value = pixels_[row][col];
      if (pixel_value >= 128) {
        std::cout << '#';
      } else {
        std::cout << ' ';
      }
    }
    std::cout << std::endl;
  }
}

void Character::FillPixel(int value, int row, int col) {
  pixels_[row][col] = value;
}

}

