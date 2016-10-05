# MotionDetection

Traffic motion detection

## Getting Started

Right click on project, click Properties
Click Configuration Manager, create new configure for x64

### Prerequisities

OpenCV2.4.11, VisualStudio 2013
Under Configuration Properties, select VC++ Directories
In the right side:
Include Directories: browse to opencv include folder
e.g: C:\opencv\build\include 
Library Directories: browse to opencv library folder
e.g: C:\opencv\build\x64\vc12\lib

On the left side, click Linker>Input
Add these libraries for OpenCV2.4.11
    opencv_calib3d2411d.lib
    opencv_contrib2411d.lib
    opencv_core2411d.lib
    opencv_features2d2411d.lib
    opencv_flann2411d.lib
    opencv_gpu2411d.lib
    opencv_highgui2411d.lib
    opencv_imgproc2411d.lib
    opencv_legacy2411d.lib
    opencv_ml2411d.lib
    opencv_nonfree2411d.lib
    opencv_objdetect2411d.lib
    opencv_ocl2411d.lib
    opencv_photo2411d.lib
    opencv_stitching2411d.lib
    opencv_superres2411d.lib
    opencv_ts2411d.lib
    opencv_video2411d.lib
    opencv_videostab2411d.lib

Done.


### Installing
