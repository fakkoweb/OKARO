
#include "OpenCVCamera.h"
#include "ImageProbe.hpp"


void frames_per_second(int delay)
{
	static int num_frame = 0;
	static int time = 0;

	num_frame++;
	time += delay;
	if (time >= 1000)
	{
		std::cout << "fps:" << num_frame << std::endl;
		num_frame = 0;
		time = 0;
	}

}

int main()
{	
	int camWidth = 1280;
	int sbsWidth = camWidth / 2;
	int i = 0;
	cv::Mat left;
	cv::Mat right;

	cv::Mat frame = cv::Mat::zeros(1280, 720, CV_8UC3);
	cv::namedWindow("sideleft", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("sideright", cv::WINDOW_AUTOSIZE);
	std::chrono::steady_clock::time_point last_request;
	std::chrono::duration< int, std::milli > delay;

	
	vdt::OpenCVCamera mydevice(0, 100);
	while (1)
	{
		last_request = std::chrono::system_clock::now();
		frame = mydevice.request(1);
		if (frame.data != nullptr)
		{
			right = frame(cv::Range::all(), cv::Range::all());
			//left = frame(cv::Range::all(), cv::Range(0, sbsWidth));

			//cv::imshow("sideleft", left);
			cv::imshow("sideright", right);
			//cv::waitKey(1);

			delay = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_request);
			std::cout << delay.count() << " ciclo " << i++ << std::endl;
			frames_per_second(delay.count());
		}
	}
	
	

	/*
	vdt::OpenCVCamera mydevice(0, 0);
	vdt::ImageProbe myimageprobe(1000, vdt::manual, vdt::none);

	myimageprobe.plug_to(mydevice);

	myimageprobe.get_raw(vdt::async);
	while (1)
	{
		last_request = std::chrono::system_clock::now();

		if (myimageprobe.new_sample_is_ready())
		{
			std::cout << "Grabbing new frame..." << std::endl;
			frame = myimageprobe.get_raw(vdt::sync);
			if (frame.data != nullptr)
			{
				std::cout << "Drawing new frame..." << std::endl;
				right = frame(cv::Range::all(), cv::Range(sbsWidth, camWidth));
				left = frame(cv::Range::all(), cv::Range(0, sbsWidth));

				cv::imshow("sideleft", left);
				cv::waitKey(1);
				cv::imshow("sideright", right);
				cv::waitKey(1);
			}
			myimageprobe.get_raw(vdt::async);
		}
			
		delay = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_request);
		std::cout << delay.count() << " ciclo " << i++ << std::endl;
	}
	*/

	/*
	while (1)
	{
		last_request = std::chrono::system_clock::now();

		if (true)
		{
			std::cout << "Grabbing new frame..." << std::endl;
			frame = myimageprobe.get_raw(vdt::sync);
			if (frame.data != nullptr)
			{
				std::cout << "Drawing new frame..." << std::endl;
				right = frame(cv::Range::all(), cv::Range(sbsWidth, camWidth));
				left = frame(cv::Range::all(), cv::Range(0, sbsWidth));

				cv::imshow("sideleft", left);
				cv::waitKey(1);
				cv::imshow("sideright", right);
				cv::waitKey(1);
			}
		}

		delay = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_request);
		std::cout << delay.count() << " ciclo " << i++ << std::endl;
	}
	*/

	/*
	vdt::OpenCVCamera mydevice(0,130);
	while (1)
	{
		last_request = std::chrono::system_clock::now();
		frame = mydevice.request(1);
		if (frame.data != nullptr)
		{
			right = frame(cv::Range::all(), cv::Range(sbsWidth + 1, camWidth));
			left = frame(cv::Range::all(), cv::Range(0, sbsWidth));

			cv::imshow("sideleft", left);
			cv::waitKey(1);
			cv::imshow("sideright", right);
			cv::waitKey(1);

			delay = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_request);
			std::cout << delay.count() << " ciclo "<< i++ << std::endl;
		}
	}
	*/
	
	

	
	cv::VideoCapture prova(0);
	if (prova.isOpened())
	{
		//prova.set(CV_CAP_PROP_FPS, 60);
		//prova.set(CV_CAP_PROP_FRAME_WIDTH, camWidth);
		//prova.set(CV_CAP_PROP_FRAME_HEIGHT, 720);

		//std::chrono::duration< int, std::micro > time;
		while (prova.isOpened())
		{
			last_request = std::chrono::system_clock::now();
			prova >> frame;

			//right = frame(cv::Range::all(), cv::Range(sbsWidth, camWidth));
			//left = frame(cv::Range::all(), cv::Range(0, sbsWidth));

			cv::imshow("sideleft", frame);
			
			//cv::imshow("sideright", right);
			cv::waitKey(1);

			delay = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - last_request);
			std::cout << delay.count() << " ciclo " << i++ << std::endl;

			frames_per_second(delay.count());
		}
	}
	



	
}