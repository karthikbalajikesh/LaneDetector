# Lane Detector for Autonomous Vehicles

This is a helper project for a larger project. This project aims at getting the pixel coordinates of the lanes in a cv::Mat image. This could be an image or a video stream. We will transform into world coordinates using Intrinsic Matrix for the purpose of Path Planning. To run this code, you will need OpenCV set up. I used opencv 4 to compile the project. You will need to edit CMakeLists.txt to add OpenCV for your path. 

## Building the Project
After setting up openCV and adding the path to CMakeLists.txt, you will need to change the absolute path of the images in test/example.cpp. After this, run the following:
```bash
chmod +x build.sh
./build.sh
```

## Running the executable
To run the executable generated, just type the following in the terminal. 
```bash
bin/example
```

In case of any questions, send an email to karthikbalaji@vt.edu.
