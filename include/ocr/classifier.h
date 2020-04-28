// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#ifndef FINALPROJECT_CLASSIFIER_H
#define FINALPROJECT_CLASSIFIER_H

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

#endif  // FINALPROJECT_CLASSIFIER_H
