// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <catch2/catch.hpp>
#include <ocr/image_transcriber.h>

ocr::TrainingData train_data("/Users/karan/Documents/cinder_0.9.2_mac/my-projects/final-project-ksodhi2/tests/data/emnist_test.csv");
ocr::KNN knn_classifier(train_data, 7);

ocr::ImageTranscriber image_transcriber(knn_classifier);

TEST_CASE("Read Image From File") {
  SECTION("Try to Read image from file that does not exist") {
    REQUIRE_THROWS(image_transcriber.ReadImageFromFile("does/not/exist"));
  }
  
  SECTION("Try to Read Image from a non image file") {
    REQUIRE_THROWS(image_transcriber.ReadImageFromFile("/Users/karan/Documents/cinder_0.9.2_mac/my-projects/final-project-ksodhi2/tests/data/emnist_test.csv"));
  }
  
  SECTION("Try to Read a valid image file") {
    REQUIRE_NOTHROW(image_transcriber.ReadImageFromFile("/Users/karan/Documents/cinder_0.9.2_mac/my-projects/final-project-ksodhi2/tests/assets/letters.png"));
  }
}