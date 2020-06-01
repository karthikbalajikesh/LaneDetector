#include <chrono>
#include"LaneDetector.h"

using namespace cv;
using namespace std::chrono;
using namespace std;

int main(){
	Mat frame;
	string image_name = "/home/karthik/dev/LaneDetector/test/media/lane.jpg";
	frame = imread(image_name);
	auto start = high_resolution_clock::now();
	LaneDetector Help(frame);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << duration.count();
	return 0;

}
