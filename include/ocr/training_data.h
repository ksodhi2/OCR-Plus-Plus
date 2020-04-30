// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#ifndef FINALPROJECT_TRAINING_DATA_H
#define FINALPROJECT_TRAINING_DATA_H

#include <ocr/character.h>
#include <fstream>

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
   * Checks if the file path provides is a valid CSV file of the EMNIST dataset
   * a valid file will contain a multiple of 785 numbers
   * (28x28 for the pixels, and one for the label) that are all 
   * integers between 0 and 255. Also checks if the file exists and is non empty.
   * @param file_path the file path for the EMNIST dataset
   * @return if the file is valid
   */
  bool IsTrainingFileValid(const string& file_path);

 public:
  /**
   * Populates the training data with a CSV file of the EMNIST dataset
   * the CSV file starts with a integer representation of the label,
   * the next 784 values are the pixel values of the character
   * and this pattern continues on in one big line.
   * If the file passed does not have the correct format an exception is throwed 
   * @param file_path the file path for the EMNIST dataset
   */
  TrainingData(const string& file_path);
  
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

#endif  // FINALPROJECT_TRAINING_DATA_H
