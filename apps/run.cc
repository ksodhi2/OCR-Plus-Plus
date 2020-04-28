// Copyright (c) 2020 [Karan Sodhi]. All rights reserved.

#include "ocr_app.h"
#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

using cinder::app::App;
using cinder::app::RendererGl;

namespace ocr_app {

const int kSamples = 8;
const int kWidth = 800;
const int kHeight = 800;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("OCR++");
}

}  // namespace ocr_app

// This is a macro that runs the application.
CINDER_APP(ocr_app::OCRApp,
           RendererGl(RendererGl::Options().msaa(ocr_app::kSamples)),
           ocr_app::SetUp)
