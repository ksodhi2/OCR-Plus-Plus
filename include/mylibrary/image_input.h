// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <opencv2/opencv.hpp>
#include <vector>
#include <mylibrary/character.h>

using std::vector;
using cv::Mat;

namespace mylibrary {

/**
 * From a text image extracts all the characters that were written on it
 * @param image the image to extract characters from
 * @return a vector containing all of the characters,
 * each represented as a Character object
 */
std::vector<Character> extractCharacters(const cv::Mat& image);

/**
 * Uses an image file to extract characters
 * @param file_path the file path of the image to extract characters from
 * @return a vector containing all of the characters,
 * each represented as a Character object
 */
vector<Character> extractCharactersFromFile(std::string file_path);

/**
 * Processes the image by greying it out, smoothing it, and thresholding it
 * @param input_image the image that was inputed
 * @return the processed image
 */
Mat ProcessImage(const Mat& input_image);

/**
 * Uses the webcam to extract characters
 */
void extractCharactersFromCamera();
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
