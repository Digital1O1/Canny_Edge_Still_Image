#include <opencv2/opencv.hpp> // Include the main OpenCV header
#include <stdio.h>
int main()
{
    // The JPEG HAS to be grayscaled
    cv::Mat image = cv::imread("E:/Coding Folder/C++/OpenCV_Projects/Image_Thresholding/Still_Image/Screenshot 2023-08-27 202307.jpeg", cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        // Error handling if the image fails to load
        printf("FAILED TO LOAD IMAGE\r\n");
        return -1;
    }

    cv::Mat edges;
    cv::Canny(image, edges, 100, 150);

    // Display the original image and the edges side by side

    /*
        Notes about Mat combinedImage()
            - It's just a cv::Mat 
            - image.rows and image.cols are the parameters being passed to the constructor that specifies the size/data type of the matrix
                - Data type being used : CV_8UC1 --> 9-bit unsigned single-channel matrix 
                - Suitable for grayscale images

        CV_8UC1 suitable for grayscale images for the following reasons 
            - Channel count
                - Gray scales only have ONE channel since they represent a brightness level using a single color channel
            - Bit depth
                - The 8U --> 8-bit unsigned integer
                - Pixels range from 0 - 255
                - Provides 256 levels of gray
            - Memory efficiency
                - Grayscale images only need one channel of information per pixel
                - Using 8-bit data type ensures each pixel only takes up one byte of memory
                    - Efficient in terms of memory usage
            - Compatibility
                - Most processing algorithms/functions in OpenCV use CV_8UC1 for grayscale operations
    */
    cv::Mat combinedImage(image.rows, image.cols * 2, CV_8UC1);
    cv::Mat left(combinedImage, cv::Rect(0, 0, image.cols, image.rows));
    image.copyTo(left);
    cv::Mat right(combinedImage, cv::Rect(image.cols, 0, image.cols, image.rows));
    edges.copyTo(right);

    // Create a window and display the combined image
    cv::namedWindow("Canny Edge Detection", cv::WINDOW_NORMAL);
    cv::imshow("Canny Edge Detection", combinedImage);

    // Wait for a key press
    cv::waitKey(0);
    cv::destroyWindow("Canny Edge Detection");

    return 0;
}
/*
    WINDOWS
        - cd <directory>
        - mkdir build
        - cd build
        - cmake -DCMAKE_BUILD_TYPE=Release ..
        - cmake --build . --config Release

    To build MakeFiles in Windows
        - cmake -G "Unix Makefiles" ..
        - make

    Notes
    - To build : cmake -G "Visual Studio 16 2019" ..
    - To compile : cmake --build . --config Release
    - Exe will be in RELEASE folder

    Linux
        - cd <directory>
        - mkdir build
        - cd build
        - cmake -DCMAKE_BUILD_TYPE=Release ..
        - make
            - cmake --build . --config Release

    Path to JPEG : /home/ctnano/Desktop/Coding_Folder/OpenCV_Cmake_Basic_Example/Cat_Meme_.jpeg
        - use readlink -f new.txt to find file path
*/