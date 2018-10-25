#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace cv;

string				face_cascade_name = ".data/haarcascades/haarcascade_frontalface_default.xml";
CascadeClassifier	*face_cascade;
String				window_name = "Capture";
bool				face_detected = false;
vector<Rect>		faces;
Rect				main_face;

void	ft_error(char i)
{
	if (i == 0) cout << "Error loading cascade\n";
	if (i == 1) cout << "Error opening video capture\n";
	if (i == 2) cout << "No captured frame\n";
	exit (1);
}

void	frame_in_window(Mat frame)
{
	if (face_detected) rectangle(frame, main_face, 0, 10, 0);
	imshow(window_name, frame);
	if (waitKey(25) == 27) exit (1);
}

void	detect_main_face(void)
{
	int		cnt = 0;

	for (int i = 0; i < faces.size(); i++)
		if (faces[i].area() > faces[cnt].area())
			cnt = i;
	main_face = faces[cnt];
}

bool	non_detected_face(Mat frame)
{
    Mat				frame_gray;

    face_cascade->detectMultiScale(frame, faces, 1.2, 3, 0,
        Size(frame.rows / 5, frame.rows / 5),
        Size(frame.rows * 2 / 3, frame.rows * 2 / 3));
	if (faces.empty()) return(false);
	detect_main_face();
	return (true);
}

bool	detected_face(Mat frame)
{
	face_cascade->detectMultiScale(frame, faces, 1.2, 3, 0,
		Size(main_face.width * 8 /10, main_face.height * 8 / 10),
		Size(main_face.width * 12 / 10, main_face.width * 12 / 10));
	if (faces.empty()) return (false);
	detect_main_face();
	return (true);
}

int main(int argc, const char** argv)
{
    VideoCapture	capture;
	Mat				frame;

	face_cascade = new CascadeClassifier(face_cascade_name);
	if(face_cascade->empty())
		ft_error(0);
	int camera_device = 0;
	capture.open(camera_device);
	if (!capture.isOpened())
		ft_error(2);
	while (!face_detected)
	{
		if(!capture.read(frame))
			ft_error(3);
		if (non_detected_face(frame))
			face_detected = true;
		frame_in_window(frame);
		while (face_detected)
		{
			cout << "Face detected." << '\n';
			if(!capture.read(frame))
				ft_error(3);
			if (!detected_face(frame))
				face_detected = false;
			frame_in_window(frame);
		}
		cout << "No face detected." << '\n';
	}
	return (0);
}
