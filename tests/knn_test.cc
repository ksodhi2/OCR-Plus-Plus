// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <catch2/catch.hpp>
#include <ocr/knn.h>

ocr::TrainingData training_data_set("/Users/karan/Documents/cinder_0.9.2_mac/my-projects/final-project-ksodhi2/data/emnist_training_data.csv");
ocr:: KNN knn(training_data_set, 3);

TEST_CASE("Classifying Characters") {
  SECTION("Classifying 1") {
    cv::Mat one_image = cv::imread("/Users/karan/Documents/cinder_0.9.2_mac/my-projects/final-project-ksodhi2/tests/assets/one.png");
    ocr::Character one(one_image);
    REQUIRE(knn.Classify(one) == '1');
  }
  
  SECTION("Classifying 8") {
    cv::Mat eight_image = cv::imread("/Users/karan/Documents/cinder_0.9.2_mac/my-projects/final-project-ksodhi2/tests/assets/eight.png");
    ocr::Character eight(eight_image);
    REQUIRE(knn.Classify(eight) == '8');
  }
  
  SECTION("Classifying A") {
    cv::Mat A_image = cv::imread("/Users/karan/Documents/cinder_0.9.2_mac/my-projects/final-project-ksodhi2/tests/assets/A.png");
    cv::resize(A_image, A_image, cv::Size(28, 28), cv::INTER_AREA);
    ocr::Character A(A_image);
    REQUIRE(knn.Classify(A) == 'A');
  }
}

