// Copyright 2020 [Karan Sodhi]. All rights reserved.
#include <ocr/knn.h>

namespace ocr {

KNN::KNN(const TrainingData& training_data, int k) : training_data(training_data), k(k) {}

double KNN::CalculateDistance(const Character& first_char, const Character& second_char) const {
  double distance = 0;
  for (size_t row = 0; row < kCharacterSize; row++) {
    for (size_t col = 0; col < kCharacterSize; col++) {
      distance += pow(first_char.PixelValueAt(row, col) - second_char.PixelValueAt(row, col), 2);
    }
  }
  return sqrt(distance);
}

std::vector<int> KNN::FindKNearest(const Character& character) const {
  std::vector<int> neighbor_indexes;
  std::vector<double> distances;
  double min_distance = DBL_MAX;
  
  for (size_t i = 0; i < k; i++) {
    int neighbor_index;
    for (size_t j = 0; j < training_data.Size(); j++) {
      double distance;
      if (i == 0) {
        distance = CalculateDistance(character, training_data.GetCharacterAt(j));
        distances.push_back(distance);
      } else {
        distance = distances[j];
      }
      if (distance < min_distance && std::find(neighbor_indexes.begin(), neighbor_indexes.end(), j) == neighbor_indexes.end()) {
        min_distance = distance;
        neighbor_index = j;
      }
    }
    neighbor_indexes.push_back(neighbor_index);
    min_distance = DBL_MAX;
  }
  return neighbor_indexes;
}

char KNN::Classify(const Character& character) const {
  vector<int> neighbor_indexes = FindKNearest(character);
  std::map<char, int> map_label_to_count;
  for (int neighbor_index : neighbor_indexes) {
    map_label_to_count[training_data.GetLabelAt(neighbor_index)]++;
  }
  
  int max_count = 0;
  char label;
  for (auto const& map_entry : map_label_to_count) {
    if (map_entry.second > max_count) {
      max_count = map_entry.second;
      label = map_entry.first;
    }  
  }
  return label;
}

}  // namespace ocr

