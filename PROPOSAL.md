# OCR++

Author: Karan Sodhi

For my Final Project, I want to create an optical character reader that will continuously display any pieces of text that is brought up to the webcam. The project will differ from Naive Bayes as my application will be able to read both numbers and characters and more than one character will be read at a time. I am also going to use additional classification algorithms like k-Nearest Neighbors to more accurately predict the characters. 

I want to create this project because last semester I worked on a web-app called Secure4Sure that used a computer vision API to parse through identification documents. However, my access to that API is ending soon, so I want to try to create my own OCR software. I am going to be using the OpenCV library <sup>[1](#myfootnote1)</sup> to capture images from my webcam and then process them. 

By the end of week one, I hope to set up the OpenCV library and start extracting features from the images. By week two, I plan on exploring different classification algorithms and getting a working model set up. By week three, I plan on bringing all the pieces together and creating a professional-looking UI. 

If I were to finish the project early, I could work on creating a REST API that would accept a POST request containing image data and then send back the predicted text on the image.

<a name="myfootnote1">1</a>: https://github.com/cinder/Cinder-OpenCV3

---
