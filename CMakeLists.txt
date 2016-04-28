cmake_minimum_required(VERSION 2.8)

project( DisplayImage )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++11")

find_package( OpenCV REQUIRED )

add_executable( DisplayImage main.cpp VideoFaceDetector.cpp )

target_link_libraries( DisplayImage ${OpenCV_LIBS} )
