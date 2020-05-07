// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <catch2/catch.hpp>
#include <ocr/knn.h>

ocr::TrainingData training_data_set("/data/emnist_training_data.csv");
ocr:: KNN knn(training_data_set, 3);

TEST_CASE("Classifying Characters") {
  SECTION("Classifying 1") {
    cv::Mat one_image = cv::imread("/tests/assets/one.png");
    cv::resize(one_image, one_image, cv::Size(28, 28), cv::INTER_AREA);
    ocr::Character one(one_image);
    REQUIRE(knn.Classify(one) == '1');
  }
  
  SECTION("Classifying 8") {
    cv::Mat eight_image = cv::imread("/tests/assets/eight.png");
    cv::resize(eight_image, eight_image, cv::Size(28, 28), cv::INTER_AREA);
    ocr::Character eight(eight_image);
    REQUIRE(knn.Classify(eight) == '8');
  }

  SECTION("Classifying 5") {
    cv::Mat five_image = cv::imread("/tests/assets/five.png");
    cv::resize(five_image, five_image, cv::Size(28, 28), cv::INTER_AREA);
    ocr::Character five(five_image);
    REQUIRE(knn.Classify(five) == '5');
  }
  
  SECTION("Classifying A") {
    cv::Mat A_image = cv::imread("/tests/assets/A.png");
    cv::resize(A_image, A_image, cv::Size(28, 28), cv::INTER_AREA);
    ocr::Character A(A_image);
    REQUIRE(knn.Classify(A) == 'A');
  }

  SECTION("Classifying F") {
    cv::Mat F_image = cv::imread("/tests/assets/F.png");
    cv::resize(F_image, F_image, cv::Size(28, 28), cv::INTER_AREA);
    ocr::Character F(F_image);
    REQUIRE(knn.Classify(F) == 'F');
  }

  SECTION("Classifying Z") {
    cv::Mat Z_image = cv::imread("/tests/assets/Z.png");
    cv::resize(Z_image, Z_image, cv::Size(28, 28), cv::INTER_AREA);
    ocr::Character Z(Z_image);
    REQUIRE(knn.Classify(Z) == 'Z');
  }
}

