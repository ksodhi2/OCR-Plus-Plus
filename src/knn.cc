// Copyright 2020 [Karan Sodhi]. All rights reserved.

#include <ocr/knn.h>

namespace ocr {

KNN::KNN(const TrainingData& training_data, int k)
    : training_data(training_data), k(k) {}

double KNN::CalculateDistance(const Character& first_char,
                              const Character& second_char) const {
  double distance = 0;
  for (size_t row = 0; row < kCharacterSize; row++) {
    for (size_t col = 0; col < kCharacterSize; col++) {
      distance += pow(first_char.PixelValueAt(row, col)
                  - second_char.PixelValueAt(row, col), 2);
    }
  }
  return sqrt(distance);
}

std::vector<size_t> KNN::FindKNearest(const Character& character) const {
  std::vector<size_t> neighbor_indexes;
  std::priority_queue<pair<double, size_t>> distances;

  for (size_t i = 0; i < training_data.Size(); i++) {
    double distance = CalculateDistance(character,
                      training_data.GetTrainingSampleAt(i).character);
    distances.push(pair<double, size_t>(-distance, i));
  }

  for (size_t i = 0; i < k; i++) {
    neighbor_indexes.push_back(distances.top().second);
    distances.pop();
  }
  return neighbor_indexes;
}

char KNN::Classify(const Character& character) const {
  vector<size_t> neighbor_indexes = FindKNearest(character);
  std::map<char, size_t> map_label_to_count;
  for (size_t neighbor_index : neighbor_indexes) {
    map_label_to_count[training_data.GetTrainingSampleAt(neighbor_index).label]++;
  }

  size_t max_count = 0;
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

