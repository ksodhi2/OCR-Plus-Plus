// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <ocr/character.h>

namespace ocr {

Character::Character(): pixels_(kCharacterSize,
                                 std::vector<size_t>(kCharacterSize)) {}

Character::Character(const cv::Mat& character_image) : Character() {
  if (character_image.channels() != 1) {
    throw std::invalid_argument("Character passed in not in greyscale");
  }
  
  cv::Mat processed_image;
  // increases text width
  cv::dilate(character_image, processed_image, cv::Mat(9, 9, 0));
  // re-sizes image to 20x20
  cv::resize(processed_image, processed_image,
             cv::Size(20, 20), cv::INTER_AREA);
  // adds a 4 pixel black border around each side, making the image 28x28
  cv::copyMakeBorder(processed_image, processed_image,
                     4, 4, 4, 4, cv::BORDER_CONSTANT);

  for (size_t row = 0; row < processed_image.rows; row++) {
    for (size_t col = 0; col < processed_image.cols; col++) {
      size_t pixel_value = processed_image.at<uchar>(row, col);
      FillPixel(pixel_value, row, col);
    }
  }
}

void Character::FillPixel(size_t pixel_value, size_t row, size_t col) {
  if (pixel_value < kMinPixelValue || pixel_value > kMaxPixelValue) {
    throw std::invalid_argument("Pixel value must be between 0 and 255");
  }
  pixels_[row][col] = pixel_value;
}

int Character::PixelValueAt(size_t row, size_t col) const {
  return pixels_[row][col];
}

std::ostream& operator<<(std::ostream& os, const Character& character) {
  for (size_t row = 0; row < kCharacterSize; row++) {
    for (size_t col = 0; col < kCharacterSize; col++) {
      int pixel_value = character.pixels_[row][col];
      if (pixel_value >= kMaxPixelValue / 2) {
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

