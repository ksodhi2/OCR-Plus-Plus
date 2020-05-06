// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <catch2/catch.hpp>
#include <ocr/character.h>

using ocr::Character;
using std::string;

TEST_CASE("Constructing a character from a Image") {
  cv::Mat colored_image = cv::imread("/tests/assets/color.jpg");
  SECTION("Trying to construct a character from a non greyscale image") {
    REQUIRE_THROWS(Character(colored_image));
  }
  cv::Mat greyscale_image;
  cv::cvtColor(colored_image, greyscale_image, cv::COLOR_BGR2GRAY);
  SECTION("Trying to construct from a greyscale image") {
    REQUIRE_NOTHROW(Character(greyscale_image));
  }
}

TEST_CASE("Fill Pixel Value") {
  Character character;
  SECTION("Fill Pixel with an invalid value") {
    REQUIRE_THROWS(character.FillPixel(256, 0, 0));
  }
  SECTION("Fill Pixel with an valid value") {
    REQUIRE_NOTHROW(character.FillPixel(255, 0, 0));
  }
}

TEST_CASE("Get Pixel Value") {
  Character character;
  SECTION("Get Pixel Value from a Character after filling it") {
    character.FillPixel(37, 3, 5);
    REQUIRE(character.PixelValueAt(3, 5) == 37);
  }
  
  cv::Mat image = cv::imread("/tests/assets/A.png");
  cv::resize(image, image, cv::Size(28, 28));
  Character char_from_image(image);
  SECTION("Get Pixel Value from a Character constructed from an image") {
    SECTION("Pixel Value on the Text") {
      REQUIRE(char_from_image.PixelValueAt(13, 25) == 255);
    }
    SECTION("Pixel Value on the Background") {
      REQUIRE(char_from_image.PixelValueAt(20, 20) == 0);
    }
  }
}

TEST_CASE("Print Character") {
  cv::Mat image = cv::imread("/tests/assets/l.png");
  cv::resize(image, image, cv::Size(28, 28));
  Character character(image);
  std::ostringstream printed_character;
  string to_print = string("                            ") +
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
  REQUIRE(printed_character.str() == to_print);
}

