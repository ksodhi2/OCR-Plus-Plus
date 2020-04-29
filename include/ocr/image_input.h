// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <opencv2/opencv.hpp>
#include <opencv2/text.hpp>
#include <ocr/knn.h>
#include <vector>

using cv::Mat;
using std::vector;

namespace ocr {

/**
* File paths for TextBoxes (Fast Text Detector with a Single Deep Neural Network)
* more info here https://github.com/MhLiao/TextBoxes
* https://docs.opencv.org/master/d1/d66/classcv_1_1text_1_1TextDetectorCNN.html
*/
const string text_detection_model = "data/TextBoxes_icdar13.caffemodel";
const string text_detection_description = "data/textbox.prototxt";

class ImageTranscriber {
  
 private:
  const Classifier& classifier;
  
  /**
   * Finds text from an image and attempts to transcribe it 
   * by displaying the correct characters above the text
   * @param image the image to read
   * @return a transcribed image
   */
  Mat ReadImage(const Mat& image);
  
  /**
   * Processes the image by greying it out, smoothing it, and thresholding it
   * @param input_image the image that was imputed
   * @return the processed image
   */
  Mat ProcessImage(const Mat& input_image);

  /**
   * Uses the TextBoxes CNN to find areas on the image that have text
   * @param input_image the image to find text on
   * @return a vector containing rectangles of area thea on the image with text
   */
  vector<cv::Rect> FindAreaWithText(const Mat& input_image);

  /**
   * @param rectangle a single rectangle 
   * @param rect_list a list of rectangles
   * @return if the single rectangle overlaps with any of the rectangles in the list
   */
  bool DoesRectangleOverlap(const cv::Rect& rectangle, const vector<cv::Rect>& rect_list);
  
 public:
  ImageTranscriber(const Classifier& classifier);
  
  /**
   * Uses an image file to find text from an image and transcribe it
   * @param file_path the file path of the image to transcribe
   * @return a transcribed image
   */
  Mat ReadImageFromFile(const std::string& file_path);

  /**
   * Finds text from a web cam and attempts to transcribe it live
   * @return the transcribed image frame from the web cam
   */
  Mat ReadImageFromCamera();
  
};

}  // namespace ocr


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
