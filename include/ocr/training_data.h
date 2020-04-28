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

 public:
  /**
   * Populates the training data with a CSV file of the EMNIST dataset
   * the CSV file starts with a integer representation of the label,
   * the next 784 values are the pixel values of the character
   * this pattern continues on in one big line
   */
  TrainingData(const string& file_path);
  
  /**
   * @return the total number of training samples
   */
  size_t Size() const;
  
  /**
   * @param index the index of the training sample
   * @return the character at that index
   */
  Character GetCharacterAt(size_t index) const;

  /**
   * @param index the index of the training sample
   * @return the label at that index
   */
  int GetLabelAt(size_t index) const;
};

}  // namespace ocr

#endif  // FINALPROJECT_TRAINING_DATA_H
