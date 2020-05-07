// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <ocr/training_data.h>

using ocr::TrainingData;

ocr::TrainingData training_data("/tests/data/emnist_test.csv");

TEST_CASE("Constructing training data from a file") {
  SECTION("Trying to construct training data from a file that does not exist") {
    REQUIRE_THROWS(TrainingData("does/not/exist"));
  }
  SECTION("Trying to construct training data from an empty file") {
    REQUIRE_THROWS(TrainingData("/tests/data/empty.csv"));
  }
  SECTION("Trying to construct training data from a file with non enough values") {
    REQUIRE_THROWS(TrainingData("/tests/data/not_enough.csv"));
  }
  SECTION("Trying to construct training data from a file with non integer values") {
    REQUIRE_THROWS(TrainingData("/tests/data/non_integer.csv"));
  }
  SECTION("Trying to construct training data from a file with too big and small values") {
    REQUIRE_THROWS(TrainingData("/tests/data/too_big_and_small.csv"));
  }
  SECTION("Trying to construct training data from a valid file") {
    REQUIRE_NOTHROW(TrainingData("/tests/data/emnist_test.csv"));
  }
}

TEST_CASE("Size of training Data") {
  REQUIRE(training_data.Size() == 10000);
}

TEST_CASE("Get Training Samples") {
  ocr::LabeledCharacter labeled_character = training_data.GetTrainingSampleAt(500);
  SECTION("Correct label for Training sample") {
    REQUIRE(labeled_character.label == '0');
  }
  
  SECTION("Correct character for Training sample") {
    SECTION("Correct Pixel Values") {
      REQUIRE(labeled_character.character.PixelValueAt(5, 17) == 254);
    }
    
    SECTION("Correct Printed Representation") {
      std::ostringstream printed_character;
      printed_character << labeled_character.character;
      string printed_text = string("                            ") +
                     '\n' + string("                            ") +
                     '\n' + string("                            ") +
                     '\n' + string("           #######          ") +
                     '\n' + string("          ##########        ") +
                     '\n' + string("        #############       ") +
                     '\n' + string("       ###############      ") +
                     '\n' + string("      ####       ######     ") +
                     '\n' + string("      ###          ####     ") +
                     '\n' + string("     ####          #####    ") +
                     '\n' + string("    ####            ####    ") +
                     '\n' + string("    ###              ###    ") +
                     '\n' + string("    ###              ####   ") +
                     '\n' + string("    ###              ####   ") +
                     '\n' + string("   ####               ###   ") +
                     '\n' + string("   ###                ###   ") +
                     '\n' + string("   ###                ###   ") +
                     '\n' + string("   ####               ###   ") +
                     '\n' + string("   ####               ###   ") +
                     '\n' + string("    ###              ###    ") +
                     '\n' + string("    ####             ###    ") +
                     '\n' + string("     ####         ####      ") +
                     '\n' + string("      ###############       ") +
                     '\n' + string("       ############         ") +
                     '\n' + string("         #######            ") +
                     '\n' + string("                            ") +
                     '\n' + string("                            ") +
                     '\n' + string("                            ") + '\n';
      REQUIRE(printed_character.str() == printed_text);
    }
  }
}