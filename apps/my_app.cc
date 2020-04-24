// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include <opencv2/opencv.hpp>
#include "my_app.h"
#include <cinder/app/App.h>
#include <mylibrary/image_input.h>
#include <mylibrary/training_data.h>


namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  vector<mylibrary::Character> characters = 
      mylibrary::extractCharactersFromFile("/Users/karan/Documents/cinder_0.9.2_mac/my-projects/final-project-ksodhi2/assets/webcam_img.jpg");
  for (auto const & character : characters) {
    character.PrintPixels();
    std::cout<< "-----------------------------"<<std::endl;
  }
  
  //mylibrary::TrainingData data("/Users/karan/Documents/cinder_0.9.2_mac/my-projects/final-project-ksodhi2/data/emnist_training_set.csv");
  //data.PrintData();
  //std::cout<< data.Size();
  //mylibrary::extractCharactersFromCamera();
}

void MyApp::update() { }

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
