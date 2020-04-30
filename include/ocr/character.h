// Copyright 2020 [Karan Sodhi]. All rights reserved.

#ifndef FINALPROJECT_CHARACTER_H
#define FINALPROJECT_CHARACTER_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

namespace ocr {
  
const size_t kCharacterSize = 28;

class Character {
 private:
  /**
   * A 28x28 2D vector containing all the pixels of the Character
   * 0 is the most white value while 255 is the most black value
   */
  std::vector<std::vector<size_t>> pixels_;
  
 public:
  /**
   * Fills the pixel array with the pixel value from the image,
   * throws an exception if the image is not 28x28
   * @param character_image a 28x28 image of a character
   */
  Character(const cv::Mat& character_image);
  Character();
  
  /**
   * Fills the pixel array with the imputed value
   * @param value the value of the pixel to input (0 - 255)
   * @param row the row where the pixel is located
   * @param col the column where the pixel is located
   */
  void FillPixel(size_t value, size_t row, size_t col);

  /**
   * @param row the row where the pixel is located
   * @param col the column where the pixel is located
   * @return the pixel value at the specified location
   */
  int PixelValueAt(size_t row, size_t col) const;

  /**
   * Prints out a representation of the character to a generic output stream
   * '#" means that the pixel at that location is more black
   * while whitespace means the pixel is more white
   * @param os the output stream
   * @param character the character to print out
   * @return the output stream
   */
  friend std::ostream& operator<<(std::ostream& os, const Character& character);
};

}  // namespace ocr


#endif  // FINALPROJECT_CHARACTER_H
