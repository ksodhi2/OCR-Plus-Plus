//
// Created by Karan Sodhi on 4/20/20.
//

#include <mylibrary/character.h>
#include <iostream>

namespace mylibrary {

/**
 * Fills the pixel array with a '#' if the pixel at (row, col) of the 28x28
 * image is black and ' ' if the pixel is white.
 */
Character::Character(cv::Mat character_image) {
  pixels_.resize(kCharacterSize, std::vector<char>(kCharacterSize));
  for (int row = 0; row < character_image.rows; row++) {
    for (int col = 0; col < character_image.cols; col++) {
      
      int pixel_value = static_cast<int>(character_image.at<uchar>(row, col));
      if (pixel_value >= 128) {
        pixels_[row][col] = '#';
      } else {
        pixels_[row][col] = ' ';
      }
    }
  }
}

void Character::PrintPixels() const {
  for (int row = 0; row < kCharacterSize; row++) {
    for (int col = 0; col < kCharacterSize; col++) {
      std::cout << pixels_[row][col];
    }
    std::cout << std::endl;
  }
}

}

