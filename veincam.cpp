// veincam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	// You can change the values and see what happens
	int Y_MIN = 0;
	int Y_MAX = 255;
	int Cr_MIN = 133;
	int Cr_MAX = 173;
	int Cb_MIN = 77;
	int Cb_MAX = 127;
	VideoCapture cap(0);

	if (cap.isOpened() == false)
	{
		cout << " cannot open camera" << endl;
		cin.get();
		return -1;
	}

	double dWidth = cap.get(CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
	double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

	cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;
	string window_name = "My Camera Feed";
	namedWindow(window_name); //create a window called "My Camera Feed"

	while (true)
	{
		Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video 

		cout<< "channels : "<< frame.channels()<<endl;
		//Mat skin;

		//cvtColor(frame, skin, COLOR_BGR2YCrCb);
		//imshow("Ycrcb color space", skin);
		
		Mat RGBSkin = frame.clone();
		
		//RGBSkin.dims = (dWidth, dHeight, 3);
		for (int i = 0; i < dWidth; i++)
		{
			for (int j = 0; j < dHeight; j++)
			{

				//uchar b = frame.at<uchar>(Point(i, j));
				//uchar g = frame.at<uchar>(Point(i+1, j));
				//uchar r = frame.at<uchar>(Point(i+2, j));
				//cout << "BLue : "<< int(rgb[0]) << endl;
				
				uchar b = frame.data[frame.channels()*(frame.cols*j + i) + 0];
				uchar g = frame.data[frame.channels()*(frame.cols*j + i) + 1];
				uchar r = frame.data[frame.channels()*(frame.cols*j + i) + 2];

				
				//cout << "pointx : " << i << " point y : " << j << endl;
				if (( b > 20) && (g > 40) && (r > 95) && (r > g) && (r > b))
				{
					RGBSkin.data[RGBSkin.channels()*(RGBSkin.cols*j + i) + 0] = b;
					RGBSkin.data[RGBSkin.channels()*(RGBSkin.cols*j + i) + 1] = g;
					RGBSkin.data[RGBSkin.channels()*(RGBSkin.cols*j + i) + 2] = r;
				}
				else
				{
					RGBSkin.data[RGBSkin.channels()*(RGBSkin.cols*j + i) + 0] = 0;
					RGBSkin.data[RGBSkin.channels()*(RGBSkin.cols*j + i) + 1] = 0;
					RGBSkin.data[RGBSkin.channels()*(RGBSkin.cols*j + i) + 2] = 0;
				}
				
			}
		}
		//inRange(frame,Scalar(20,40,95), Scalar(200,200,255),RGBSkin);
		//inRange(skin, Scalar(Y_MIN, Cr_MIN, Cb_MIN), Scalar(Y_MAX, Cr_MAX, Cb_MAX), skin);
		imshow("Skin from rgb", RGBSkin);
		imshow("Frame image", frame);
		//Breaking the while loop if the frames cannot be captured
		if (bSuccess == false)
		{
			cout << "Video camera is disconnected" << endl;
			cin.get(); //Wait for any key press
			break;
		}

		//show the frame in the created window
		imshow(window_name, frame);

		//wait for for 10 ms until any key is pressed.  
		//If the 'Esc' key is pressed, break the while loop.
		//If the any other key is pressed, continue the loop 
		//If any key is not pressed withing 10 ms, continue the loop 
		if (waitKey(10) == 27)
		{
			cout << "Esc key is pressed by user. Stoppig the video" << endl;
			break;
		}
	}

	return 0;
	
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
