// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <ocr/training_data.h>

namespace ocr {

TrainingData::TrainingData(const string& file_path) {
  std::ifstream data_stream(file_path);
  if (data_stream.fail() || data_stream.peek() == EOF) {
    throw std::invalid_argument("Must Pass in A Valid Training File");
  }

  string value;
  int values_count = 0;
  while (data_stream.peek() != EOF) {
    bool is_label = true;
    size_t row = 0;
    size_t col = 0;
    LabeledCharacter labeled_character;

    while (getline(data_stream, value, ',')) {
      values_count++;
      if (!IsValueValid(value)) {
        throw std::invalid_argument("Training File Contains Invalid Values");
      } else if (is_label) {
        labeled_character.label = LabelToChar(std::stoi(value));
        is_label = false;
        continue;
      }
      labeled_character.character.FillPixel(std::stoi(value), row, col);
      
      row++;
      if (row == kCharacterSize) {
        row = 0;
        col++;
      }
      if (col == kCharacterSize) {
        break;
      }
    }
    training_samples.push_back(labeled_character);
  }

  if (values_count % (kCharacterSize * kCharacterSize + 1) != 0) {
    throw std::invalid_argument("Training File Contains a Wrong Number of Values");
  }
}

size_t TrainingData::Size() const {
  return training_samples.size();
}

LabeledCharacter TrainingData::GetTrainingSampleAt(size_t index) const {
  return training_samples[index];
}

bool TrainingData::IsValueValid(const string& value) const {
  int value_num;
  try {
    value_num = std::stoi(value);
  } catch (const std::exception& e) {
    return false;
  }
  return value_num >= kMinPixelValue && value_num <= kMaxPixelValue;
}

char TrainingData::LabelToChar(int label) const {
  size_t digit_count = 10;
  if (label < digit_count) {
    return '0' + label;
  } else {
    return 'A' + label - digit_count;
  }
}

}  // namespace ocr
