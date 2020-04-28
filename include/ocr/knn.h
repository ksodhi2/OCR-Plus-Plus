// Copyright 2020 [Karan Sodhi]. All rights reserved.

#ifndef FINALPROJECT_KNN_H
#define FINALPROJECT_KNN_H

#include <ocr/training_data.h>
#include <ocr/classifier.h>

namespace ocr {

class KNN : public Classifier {
 private:
  const TrainingData& training_data;
  
  /**
   * Value representing number of nearest neighbors to find (the k in KNN)
   */
  size_t k;
  
  /**
   * For every pixel on the characters, calculates the euclidean distance 
   * between their pixel values.
   * @param first_char the first character
   * @param second_char the second character
   * @return the total distance between each of their pixel values 
   */
  double CalculateDistance(const Character& first_char, const Character& second_char) const;

  /**
   * Finds the k "nearest" number of characters to the passed in character
   * nearest in this context means the characters with
   * pixel values most closely matching the imputed character
   * @param character the character to find the nearest characters for
   * @return a vector containing the training data indexes for the nearest characters 
   */
  vector<int> FindKNearest(const Character& character) const;

 public:
  KNN(const TrainingData& training_data, int k);

  /**
   * Classifies the character by finding their
   * nearest neighbors most occurring label
   * @param character the character object to classify
   * @return the character the classifier predicts the object to be  
   */
  char Classify(const Character& character) const;
};

}  // ocr



#endif  // FINALPROJECT_KNN_H
