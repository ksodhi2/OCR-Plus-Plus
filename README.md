# OCR++

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)

OCR++ is a an application that Transcribes images live from a webcam or from a local file by using a KNN classification Algorithm. The predicted test is overlayed on top of the image and displayed.

## Dependencies
- [Cinder]
- [CMake]
- [OpenCV]
- [ImGui]
- [Portable File Dialogs]
- [Catch2]

OCR++ uses the [EMNIST] data set for training and [TextBoxes] neural network for text recognition.
Files for them are provided in the data folder but feel free to use your own data. 

## Quick Start
### MacOS
1. Download Cinder and extract the downloaded item into a folder. We’ll call this folder ~/Cinder
2. Open the ~/Cinder folder in [CLion] and click the green build button. This will build libcinder.
3. Create a directory, say my-projects in ~/Cinder. Clone the project into this folder.
4. Install OpenCV using these [instructions]
5. Open the project in CLion, set the target to cinder-OCR++ and click the run button.

## Usage
Users can select one of two options, either transcribe an image from a file (.jpg, .jpeg, .png)
or use a webcam to transcribe the video stream live. Both handwritten and typed images can be transcribed.

The ESC key closes out of the image.

![](https://i.imgur.com/xyTetIu.jpg)

## Examples
![](https://i.imgur.com/GH802uJ.png)

![](https://i.imgur.com/sKpKCSp.jpg)

**Author**: Karan Sodhi - [`ksodhi2@illinois.edu`](mailto:ksodhi2@illinois.edu)

[Cinder]: https://github.com/cinder/Cinder
[CMake]: https://cmake.org/
[OpenCV]: https://github.com/opencv/opencv
[ImGui]: https://github.com/simongeilfus/Cinder-ImGui
[Portable File Dialogs]: https://github.com/samhocevar/portable-file-dialogs
[Catch2]: https://github.com/catchorg/Catch2
[EMNIST]: https://www.kaggle.com/crawford/emnist
[TextBoxes]: https://github.com/MhLiao/TextBoxes
[CLion]: https://www.jetbrains.com/clion/
[instructions]: https://blog.zhajor.com/2016/10/install-opencv-and-make-a-test-project-with-clion/
