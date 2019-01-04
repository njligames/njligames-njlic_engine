
set(LIBRARY_NAME "opencv")
set(SUB_LIBRARY_NAMES
  "opencv_calib3d"
  "opencv_core"
  "opencv_features2d"
  "opencv_flann"
  "opencv_imgcodecs"
  "opencv_imgproc"
  "opencv_ml"
  "opencv_objdetect"
  "opencv_photo"
  "opencv_shape"
  "opencv_stitching"
  "opencv_superres"
  "opencv_video"
  "opencv_videostab"
  )

set(INCLUDE_FILE "opencv/cv.h")

include("${${CMAKE_PROJECT_NAME}_REPO_DIRECTORY}/cmake/FindLibrary.cmake")
