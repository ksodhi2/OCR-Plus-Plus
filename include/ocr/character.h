// Copyright 2020 [Karan Sodhi]. All rights reserved.

#ifndef INCLUDE_OCR_CHARACTER_H_
#define INCLUDE_OCR_CHARACTER_H_

#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

namespace ocr {

const size_t kCharacterSize = 28;
const size_t kMinPixelValue = 0;
const size_t kMaxPixelValue = 255;

class Character {
 private:
  /**
   * A 28x28 2D vector containing all the pixels of the Character
   * 0 is the most white value while 255 is the most black value
   */
  std::vector<std::vector<size_t>> pixels_;

 public:
  /**
   * Dilates, re-sizes, and adds a border around a greyscale image of a 
   * character to make it match the format of the characters in the EMNIST dataset.
   * Then fills in the pixel array with the pixel values from the processed image
   * @param character_image a greyscale image of a character, if the
   * character image passed in is not in greyscale an exception is thrown.
   */
  explicit Character(const cv::Mat& character_image);
  Character();

  /**
   * Fills the pixel array with the imputed pixel value
   * the value must be between 0 and 255 or an exception is thrown
   * @param pixel_value the value of the pixel to input (0 - 255)
   * @param row the row where the pixel is located
   * @param col the column where the pixel is located
   */
  void FillPixel(size_t pixel_value, size_t row, size_t col);

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

#endif  // INCLUDE_OCR_CHARACTER_H_
