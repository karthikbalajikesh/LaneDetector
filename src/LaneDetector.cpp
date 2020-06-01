// Lane Detector Class Methods
// Author - Karthik Balaji Keshavamurthi


#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<string>
#include"LaneDetector.h"

using namespace std;
using namespace cv;

LaneDetector::LaneDetector(Mat &Frame):originalFrame(Frame){
// This will be the main function
	cout<<"Lane Detector is created"<<endl;

	// Step 1 - define ROI and warp Image
	setPointsTest();
	calculatePerspectiveMatrices();
	GenerateWarpedImage();
	// Step 2 - Process Warped image
	cvtColor(BirdsEyeView,processedIPM, COLOR_BGR2GRAY);
	// create mask for capturing white
	// Parameter to tune - THreshold VALUES
	inRange(processedIPM,Scalar(150,150,150), Scalar(255,255,255),
							processedIPM);
	// Apply Gaussian Blur
	GaussianBlur(processedIPM,processedIPM,Size(9,9),0,0);
	// We remove noise and close the structures by
	// Morph open and close.
	MorphologyKernel = Mat::ones(5,5, CV_8U);
	morphologyEx(processedIPM, processedIPM, MORPH_OPEN, MorphologyKernel);
  morphologyEx(processedIPM, processedIPM, MORPH_CLOSE, MorphologyKernel);
	// convert to binary
	threshold(processedIPM, processedIPM, 150, 255, THRESH_BINARY);

	// now comes the sliding window search for left
	vector<Point2f> LanePointsleft = slidingWindow(processedIPM,
		Rect(20, 440, 60, 40));
	//  RIght
	vector<Point2f> LanePointsright = slidingWindow(processedIPM,
		Rect(540, 440, 60, 40));

	// Let us append both together
	LanePoints = LanePointsleft;
	LanePoints.insert(LanePoints.end(),LanePointsright.begin()
						, LanePointsright.end());

	// plotting
	string name = "original";
	show(originalFrame,name);

	name = "warped";
	show(BirdsEyeView,name);

	name = "Processed";
	show(processedIPM,name);

}

void LaneDetector::setPoints(){
// Function to set the source and destination points for IPM
	sourceVertices[0] = Point(700,605);
	sourceVertices[1] = Point(890,605);
	sourceVertices[2] = Point(1760, 1030);
	sourceVertices[3] = Point(20, 1030);

//destination will be 640x480 img
	destinationVertices[0] = Point(0,0);
	destinationVertices[1] = Point(640,0);
	destinationVertices[2] = Point(640,480);
	destinationVertices[3] = Point(0,480);
}

void LaneDetector::setPointsTest(){
// Function to set the source and destination points for IPM
	sourceVertices[0] = Point(110,480);
	sourceVertices[1] = Point(260,120);
	sourceVertices[2] = Point(410,120);
	sourceVertices[3] = Point(560,480);


//destination will be 640x480 img
	destinationVertices[0] = Point(0,480);
	destinationVertices[1] = Point(0,0);
	destinationVertices[2] = Point(640,0);
	destinationVertices[3] = Point(640,480);

}

void LaneDetector::show(Mat &frame, string &window_name){
	// Function will create a normal window and display required
	// frame.
	const string wind = window_name;
	namedWindow(wind,WINDOW_NORMAL);
	imshow(wind,frame);
	waitKey(0);
}

void LaneDetector::calculatePerspectiveMatrices(){
	perspectiveMatrix = getPerspectiveTransform(sourceVertices,
		destinationVertices);
	invert(perspectiveMatrix,InversePerspectiveMatrix);
}

void LaneDetector::GenerateWarpedImage(){

	BirdsEyeView = Mat(480,640, CV_8UC3);
	warpPerspective(originalFrame,BirdsEyeView,perspectiveMatrix,
		BirdsEyeView.size(),INTER_LINEAR, BORDER_CONSTANT);
}

vector<Point2f> LaneDetector::slidingWindow(Mat image, Rect window)
{		// code adapted from :
		//https://github.com/JanHalozan/LaneDetector
    vector<Point2f> points;
    const Size imgSize = image.size();
    bool shouldBreak = false;

    while (true)
    {
        float currentX = window.x + window.width * 0.5f;

        Mat roi = image(window); //Extract region of interest
        vector<Point2f> locations;

        findNonZero(roi, locations); //Get all non-black pixels. All are white in our case

        float avgX = 0.0f;

        for (int i = 0; i < locations.size(); ++i) //Calculate average X position
        {
            float x = locations[i].x;
            avgX += window.x + x;
        }

        avgX = locations.empty() ? currentX : avgX / locations.size();

        Point point(avgX, window.y + window.height * 0.5f);
        points.push_back(point);

        //Move the window up
        window.y -= window.height;

        //For the uppermost position
        if (window.y < 0)
        {
            window.y = 0;
            shouldBreak = true;
        }

        //Move x position
        window.x += (point.x - currentX);

        //Make sure the window doesn't overflow, we get an error if we try to get data outside the matrix
        if (window.x < 0)
            window.x = 0;
        if (window.x + window.width >= imgSize.width)
            window.x = imgSize.width - window.width - 1;

        if (shouldBreak)
            break;
    }

    return points;
}
/* Things to add:

1. We need to get the Birds Eye View of a frame by using warpPerspective
   command. - Done

2. We need to threshold the image to get a binary image and apply gaussian blur - Done

3. We need to get the set of points in the IPM using sliding window approach. - Done

4. We need to convert the Point2f into vector<coordinates> using Realsense library

5. These vector of coordinates will be added as obstacles in the grid */
