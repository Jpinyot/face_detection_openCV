#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

string face_cascade_name = ".data/haarcascades/haarcascade_frontalface_default.xml";
string eyes_cascade_name = ".data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture";

void detect_face_eye(Mat frame)
{
    Mat				frame_gray;
    vector<Rect>	faces;
    vector<Rect>	eyes;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    face_cascade.detectMultiScale(frame_gray, faces);
    for (size_t i = 0; i < faces.size(); i++)
    {
        Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
        ellipse(frame, center, Size(faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar(255, 0, 255), 4);
        Mat faceROI = frame_gray(faces[i]);
        eyes_cascade.detectMultiScale(faceROI, eyes);
        for (size_t j = 0; j < eyes.size(); j++)
        {
            Point eye_center(faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2);
            int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
            circle(frame, eye_center, radius, Scalar(255, 0, 0 , 4));
        }
    }
    imshow("Capture", frame);
}

int main(int argc, const char** argv)
{
    VideoCapture	capture;
	Mat				frame;

	if(!face_cascade.load(face_cascade_name) || !eyes_cascade.load(eyes_cascade_name))
	{
		cout << "Error loading cascade\n";
		return (-1);
	}
	int camera_device = 0;
	capture.open(camera_device);
	if (!capture.isOpened())
	{
		cout << "Error opening video capture\n";
		return -1;
	}
	while (capture.read(frame))
	{
		if(frame.empty())
		{
			cout << "No captured frame\n";
			break;
		}
		detect_face_eye(frame);
		if(waitKey(1) == 27)
			break;
	}
	return (0);
}
