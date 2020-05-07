// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#ifndef INCLUDE_OCR_CLASSIFIER_H_
#define INCLUDE_OCR_CLASSIFIER_H_

namespace ocr {

/**
 * Abstract class representing a handwriting classifier
 */
class Classifier {
 public:
  /**
   * @param character the character object to classify
   * @return the character the classifier predicts the object to be
   */
  virtual char Classify(const Character& character) const = 0;
};

}  // namespace ocr

#endif  // INCLUDE_OCR_CLASSIFIER_H_
