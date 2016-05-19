#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "VideoFaceDetector.h"

#include <thread>
#include <vector>
#include <mutex>
static std::mutex barrier;

#include <iostream>

const cv::String CASCADE_FILE("haarcascade_frontalface_default.xml");

void FindFace(cv::VideoCapture camera, cv::String WINDOW_NAME, bool allow) {
    cv::Mat frame;
    VideoFaceDetector detector(CASCADE_FILE, camera);
    std::lock_guard<std::mutex> block_threads_until_finish_this_job(barrier);
    detector >> frame;
    int short face_x_position = detector.facePosition().x;
    int short face_y_position = detector.facePosition().y;
    int short rows = frame.rows;
    int short cols = frame.cols;
    unsigned short int width = detector.face().width;
    unsigned short int height = detector.face().height;
    double area = width*height/2.0;

    if (allow) {
        cv::rectangle(frame, detector.face(), cv::Scalar(255, 0, 0));
        cv::circle(frame, detector.facePosition(), 30 , cv::Scalar(0, 255, 0));
        cv::imshow(WINDOW_NAME, frame);
    }
}

int main(int argc, char** argv) {
    // Try opening camera
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        fprintf(stderr, "Error getting camera...\n");
        exit(1);
    }
    int num_threads;
    bool allow = true;
    if (argc == 2) num_threads = atoi(argv[1]);
    else if (argc == 3) {
        num_threads = atoi(argv[1]);
        allow = false;
    }
    else num_threads = 1;
    cv::String WINDOW_NAME[num_threads];
    if (allow) {
        for (int i = 0; i < num_threads; ++i) {
            std::string x = "Camera video ";
            x += std::to_string(i);
            WINDOW_NAME[i] = x;
            cv::namedWindow(WINDOW_NAME[i], cv::WINDOW_KEEPRATIO | cv::WINDOW_NORMAL);
        }
    }
    while (true) {
        std::vector<std::thread> th;
        for (int i = 0; i < num_threads; ++i) {
            th.push_back(std::thread(FindFace, camera, WINDOW_NAME[i], allow));
        }
        for (auto &t : th) {
            t.join();
        }

        if (cv::waitKey(25) == 27) break;
    }
    return 0;
}