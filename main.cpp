#include <opencv2/opencv.hpp> 
#include <stdio.h>
int main()
{
    // The JPEG HAS to be grayscaled
    /*
        Notes about cv::imread()
            - If image can't be read, it'll return an EMPTY matrix
            - Following formats are supported
                - Windows bitmaps - *.bmp, *.dib (always supported)
                - JPEG files - *.jpeg, *.jpg, *.jpe (see the Note section)
                - JPEG 2000 files - *.jp2 (see the Note section)
                - Portable Network Graphics - *.png (see the Note section)
                - WebP - *.webp (see the Note section)
                - Portable image format - *.pbm, *.pgm, *.ppm *.pxm, *.pnm (always supported)
                - Sun rasters - *.sr, *.ras (always supported)
                - TIFF files - *.tiff, *.tif (see the Note section)
                - OpenEXR Image files - *.exr (see the Note section)
                - Radiance HDR - *.hdr, *.pic (always supported)
                - Raster and Vector geospatial data supported by GDAL (see the Note section)
            - For any references towards the note section, refer to OpenCV docs ---> https://docs.opencv.org/3.4/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56
    */
    cv::Mat image = cv::imread("E:/Coding Folder/C++/OpenCV_Projects/Image_Thresholding/Still_Image/Screenshot 2023-08-27 202307.jpeg", cv::IMREAD_GRAYSCALE);
    if (image.empty())
    {
        // Error handling if the image fails to load
        printf("FAILED TO LOAD IMAGE\r\n");
        return -1;
    }

    // Holds the output from the cv::Canny() function
    cv::Mat edges;

    // void cv::Canny(cv::InputArray image, cv::OutputArray edges, double threshold1, double threshold2, int apertureSize = 3, bool L2gradient = false)
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

    // Creates new image that'll 'hold' the original grayscale image and teh edges image side by side
    cv::Mat combinedImage(image.rows, image.cols * 2, CV_8UC1);

    // Creates new MAT image that references a ROI within the `combinedImage`
    // cv::Rect specifies position/dimensions of the ROI that starts at 0,0 adn has the same width/height as 'image'
    cv::Mat left(combinedImage, cv::Rect(0, 0, image.cols, image.rows));

    // Copy original grayscaed image to the left side
    image.copyTo(left);

    // The ROI starts to the RIGHT of `combinedImage`
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