// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <catch2/catch.hpp>
#include <ocr/character.h>

using ocr::Character;
using std::string;

cv::Mat image = cv::imread("/Users/karan/Documents/cinder_0.9.2_mac/my-projects/final-project-ksodhi2/tests/assets/A.png");

TEST_CASE("Constructing a character from a Image") {
  SECTION("Trying to construct a character from a image not 28x28") {
    REQUIRE_THROWS(Character(image));
  }
  cv::resize(image, image, cv::Size(28, 28));
  SECTION("Trying to construct a character from a 28x28 image") {
    REQUIRE_NOTHROW(Character(image));
  }
}

TEST_CASE("Get Pixel Value") {
  Character character;
  SECTION("Get Pixel Value from a Character after filling it") {
    character.FillPixel(37, 3, 5);
    REQUIRE(character.PixelValueAt(3, 5) == 37);
  }
  cv::resize(image, image, cv::Size(28, 28));
  Character char_from_image(image);
  SECTION("Get Pixel Value from a Character constructed from an image") {
    REQUIRE(char_from_image.PixelValueAt(13, 25) == 255);
    REQUIRE(char_from_image.PixelValueAt(20, 20) == 0);
  }
}

TEST_CASE("Print Character") {
  cv::resize(image, image, cv::Size(28, 28));
  Character character(image);
  std::ostringstream printed_character;
  string solution = string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                           #") +
             '\n' + string("                           #") +
             '\n' + string("                        ####") +
             '\n' + string("                        ####") +
             '\n' + string("                     ###### ") +
             '\n' + string("                     #######") +
             '\n' + string("                  ######    ") +
             '\n' + string("                  ######    ") +
             '\n' + string("               ######       ") +
             '\n' + string("               ######       ") +
             '\n' + string("            ######          ") +
             '\n' + string("            ######          ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") +
             '\n' + string("                            ") + 
             '\n' + string("                            ") +
             '\n' + string("                            ") + '\n';

  printed_character << character;
  REQUIRE(printed_character.str() == solution);
}

