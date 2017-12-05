#include <opencv2\opencv.hpp>
#include "KinectHelper.h"
#include "HandEventsHandler.h"

using namespace cv;

int main(int argc, char ** argv)
{
	//KinectHelper::Run();
	KinectHelper k;
	k.init();

	
	GestureEvents * event = new HandEventsHandler;
	k.setGestureEvent(event);
	k.UpdateFrame();
	k.deInit();
	return 0;
}