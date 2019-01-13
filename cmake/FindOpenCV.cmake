
set(LIBRARY_NAME "opencv")
set(SUB_LIBRARY_NAMES
  "opencv_calib3d"
  "opencv_contrib"
  "opencv_core"
  "opencv_features2d"
  "opencv_flann"
  "opencv_gpu"
  "opencv_highgui"
  "opencv_imgproc"
  "opencv_legacy"
  "opencv_ml"
  "opencv_nonfree"
  "opencv_objdetect"
  "opencv_ocl"
  "opencv_photo"
  "opencv_stitching"
  "opencv_superres"
  "opencv_ts"
  "opencv_video"
  "opencv_videostab"
  )

set(PACKAGE_PATHS
    "/usr/local/opt/opencv@2/"
    )

set(INCLUDE_FILE "opencv/cv.h")

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/FindLibrary.cmake")
