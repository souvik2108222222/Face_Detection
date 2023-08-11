#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main()
{
    CascadeClassifier facedetect;
    facedetect.load("haarcascade_frontalface_default.xml");
    VideoCapture video(0);

    if (!video.isOpened())
    {
        cout << "Failed to open the video camera" << endl;
        return -1;
    }

    while (true)
    {
        Mat frame;
        video.read(frame);

        // Detect faces in the frame
        vector<Rect> faces;
        facedetect.detectMultiScale(frame, faces, 1.5, 5, 0, Size(30, 30));

        // Draw rectangles around the detected faces and count faces
        for (int i = 0; i < faces.size(); i++) {
            rectangle(frame, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 2);
            rectangle(frame, Point(0, 0), Point(400, 60), Scalar(0, 0, 0), FILLED);
            putText(frame, to_string(faces.size()) + " Face Detected", Point(50, 40), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 255, 255), 2);

        }

        imshow("Face Detection", frame);

        // press 'q' to exit the loop
        if (waitKey(1) == 'q')
        {
            break;
        }
    }

    video.release();
    destroyAllWindows();

    return 0;
}