#include <mylibrary/training_data.h>
#include <fstream>

namespace mylibrary {

TrainingData::TrainingData(const string& file_path) {
  std::ifstream data_stream(file_path);
  string line;
  
  while (!data_stream.eof()) {
    int i = 0;
    int row = 0;
    int col = 0;
    Character character;
    while (getline(data_stream, line, ',')) {
      if (i == 0) {
        labels.push_back(atoi(line.c_str()));
        i++;
        continue;
      }
      character.FillPixel(atoi(line.c_str()), row, col);
      row++;
      if (row == kCharacterSize) {
        row = 0;
        col++;
      }
      if (col == kCharacterSize) {
        break;
      }
    }
    characters.push_back(character);
  }
}
void TrainingData::PrintData() {
  for (auto const & character : characters) {
    character.PrintPixels();
    std::cout << "-----------------------------" << std::endl;
  }  
}

int TrainingData::GetNumOfTrainingSamples() { 
  return labels.size(); 
}

}  // namespace mylibrary

