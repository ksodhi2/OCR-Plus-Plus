// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#ifndef FINALPROJECT_TRAINING_DATA_H
#define FINALPROJECT_TRAINING_DATA_H

#include <mylibrary/character.h>
using std::string;
    
namespace mylibrary {


/**
 * Training Data that will be populated with 112,800 character images
 * consisting of 28x28 pixels from the EMNIST dataset.
 * https://www.nist.gov/itl/products-and-services/emnist-dataset
 */
class TrainingData {
 private:
  std::vector<Character> characters;
  std::vector<int> labels;
  
 public:
  TrainingData(const string& file_path);
  void PrintData();
  int GetNumOfTrainingSamples();
};

}  // mylibrary

#endif  // FINALPROJECT_TRAINING_DATA_H
