#include <ocr/training_data.h>

namespace ocr {

TrainingData::TrainingData(const string& file_path) {
  if (!IsTrainingFileValid(file_path)) {
    throw std::invalid_argument("Must pass in valid training data file");
  }
  
  std::ifstream data_stream(file_path);
  string value;

  while (data_stream.peek() != EOF) {
    bool is_label = true;
    size_t row = 0;
    size_t col = 0;
    LabeledCharacter labeled_character;
    
    while (getline(data_stream, value, ',')) {
      if (is_label) {
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
}

bool TrainingData::IsTrainingFileValid(const string& file_path) {
  std::ifstream data_stream(file_path);

  if (data_stream.fail() || data_stream.peek() == EOF) {
    return false;
  }
  
  string value;
  int values_count = 0;
  while (getline(data_stream, value, ',')) {
    values_count++;
    int value_num;
    
    try {
      value_num = std::stoi(value);
    } catch (const std::exception& e) {
      return false;
    }
    
    if (value_num < 0 || value_num > 255) {
      return false;
    }
  }
  return values_count % (kCharacterSize * kCharacterSize + 1) == 0;
}


size_t TrainingData::Size() const { 
  return training_samples.size(); 
}

LabeledCharacter TrainingData::GetTrainingSampleAt(size_t index) const { 
  return training_samples[index]; 
}

char TrainingData::LabelToChar(int label) const {
  if (label < 10) {
    return label + 48;
  } else {
    return label + 55;
  }
}

}  // namespace ocr

