#include <ocr/training_data.h>

namespace ocr {

TrainingData::TrainingData(const string& file_path) {
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

size_t TrainingData::Size() const { 
  return training_samples.size(); 
}

Character TrainingData::GetCharacterAt(size_t index) const { 
  return training_samples[index].character; 
}

int TrainingData::GetLabelAt(size_t index) const { 
  return training_samples[index].label; 
}

char TrainingData::LabelToChar(int label) const {
  if (label < 10) {
    return label + 48;
  } else {
    return label + 55;
  }
}

}  // namespace ocr

