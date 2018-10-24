#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

string face_cascade_name = ".data/haarcascades/haarcascade_frontalface_default.xml";
CascadeClassifier face_cascade;
String window_name = "Capture";

void detect_face(Mat frame)
{
    Mat				frame_gray;
    Mat				faceROI;
    vector<Rect>	faces;
    vector<Rect>	eyes;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    face_cascade.detectMultiScale(frame_gray, faces);
    for (size_t i = 0; i < faces.size(); i++)
    {
        Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
        ellipse(frame, center, Size(faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar(255, 0, 255), 4);
        faceROI = frame_gray(faces[i]);
    }
    imshow("Capture", frame);
}

int main(int ac, const char **av)
{
    VideoCapture	capture;
	Mat				frame;

	if(!face_cascade.load(face_cascade_name))
	{
		cout << "Error loading cascade\n";
		return (-1);
	}
	if (ac != 2)
	{
		cout << "No valid input";
		return (-1);
	}
	frame = imread(av[1]);
	if(frame.empty())
		cout << "No captured frame\n";
	detect_face(frame);
	waitKey(2000);
	return (0);
}
