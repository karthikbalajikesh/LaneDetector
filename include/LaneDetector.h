#ifndef LANEDETECTOR_H
#define LANEDETECTOR_H
#endif

#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/opencv.hpp>
#include<string>
#include<vector>

using namespace std;
using namespace cv;

/*This code will contain the methods for sliding window,
  generating the Birds eye view, displaying original picture,
  displaying lane detected picture and displaying IPM */


class LaneDetector{
public:
	// Attributes
	Mat originalFrame;
	Mat BirdsEyeView;
	Mat processedIPM;
	Mat perspectiveMatrix;
	Mat InversePerspectiveMatrix;
	Mat MorphologyKernel;
	Point2f sourceVertices[4];
	Point2f destinationVertices[4];
	vector<Point2f> LanePoints;

	// Methods
	// 1. Constructor with frame
	// This will have hard coded ROI(source,dest pts)
	// will asssign the original frame, perspective matrix,
	// IPM matrix, BirdsEyeview, processedIPM
	LaneDetector(Mat &Frasme);

	// 2. Function to set source and destination Vertices.
	void setPoints();
	void setPointsTest();
	// 3. Function to show window:
	void show(Mat &frame,string &window_name);

	// 4. Function to get Perspective matrices
	void calculatePerspectiveMatrices();

  // 5. Warp Image
	void GenerateWarpedImage();

	// 6. Sliding Window Search
	vector<Point2f> slidingWindow(Mat Image, Rect Window);
};
