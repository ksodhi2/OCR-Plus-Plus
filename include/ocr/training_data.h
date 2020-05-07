// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#ifndef INCLUDE_OCR_TRAINING_DATA_H_
#define INCLUDE_OCR_TRAINING_DATA_H_

#include <ocr/character.h>
#include <fstream>
#include <vector>
#include <string>

using std::string;
using std::vector;

namespace ocr {

struct LabeledCharacter {
  Character character;
  char label;
};

/**
 * Training Data that will be populated with character images
 * consisting of 28x28 pixels from the EMNIST dataset.
 * https://www.nist.gov/itl/products-and-services/emnist-dataset
 */
class TrainingData {
 private:
  vector<LabeledCharacter> training_samples;

  /**
   * @param label the integer label from by the EMNIST dataset
   * @return the corresponding character representing of the label
   */
  char LabelToChar(int label) const;

  /**
   * Checks if the a value in the CSV file of the EMNIST dataset is valid
   * a valid value is an integer between 0 and 255
   * @param file_path the value in the file
   * @return if the value is valid
   */
  bool IsValueValid(const string& value) const;

 public:
  /**
   * Populates the training data with a CSV file of the EMNIST dataset
   * the CSV file starts with a integer representation of the label,
   * the next 784 values are the pixel values of the character
   * and this pattern continues on in one big line.
   * If the file passed does not have the correct format an exception is thrown 
   * @param file_path the file path for the EMNIST dataset
   */
  explicit TrainingData(const string& file_path);

  /**
   * @return the total number of training samples
   */
  size_t Size() const;

  /**
   * @param index the index of the training sample
   * @return the training sample at that index
   */
  LabeledCharacter GetTrainingSampleAt(size_t index) const;
};

}  // namespace ocr

#endif  // INCLUDE_OCR_TRAINING_DATA_H_
