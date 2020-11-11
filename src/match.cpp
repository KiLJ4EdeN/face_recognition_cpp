#include <insightface.hpp>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <sys/time.h>

unsigned long getCurTime() {
  struct timeval tv;
  unsigned long ts;
  gettimeofday(&tv, NULL);
  ts = tv.tv_sec * 1000000 + tv.tv_usec;
  return ts;
}

float absoluteDistance(float x, float y) {
  float dist;
  dist = x - y;
  if (dist >= 0) {
  return dist;
  } else {
  return dist * -1;
  }
}

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cout << "[INFO]: you passed " << argc-1 << " arguments." << std::endl;
    // warn the user to pass two image paths.
    std::cout << "[INFO]: two image paths needed for a comparison." << std::endl;
    std::cout << "[INFO]: try again passing two seperate strings." << std::endl;
    return -1;
  }
  // parse image paths.
  std::string image1 = argv[1];
  std::string image2 = argv[2];
  // load the model.
  std::string modelf = "./models/insightface.pb";
  InsightFace iface(modelf);
  if (iface.setup() != 0) {
    // exit if the model was not loaded.
    std::cout << "[WARNING]: model could not be loaded." << std::endl;
    return -1;
  }
  std::cout << "[INFO]: insightface model was loaded." << std::endl;
  // load the face images.
  cv::Mat face1 = cv::imread(image1);
  cv::Mat face2 = cv::imread(image2);
  std::cout << "[INFO]: finieshed reading image files." << std::endl;
  std::vector<float> feat1;
  std::vector<float> feat2;
  if (iface.extract(face1, feat1) != 0) {
    std::cout << "[WARNING]: feature extraction from image1 failed." << std::endl;
    return -1;
  }
  if (iface.extract(face2, feat2) != 0) {
    std::cout << "[WARNING]: feature extraction from image2 failed" << std::endl;
    return -1;
  }
  // for benchmarking purposes uncomment this.
  /* unsigned long start = getCurTime();
  for (int i = 0; i < 10; ++i) {
    if (iface.extract(face, feat) != 0) {
      std::cout << "extract feat fail" << std::endl;
      return -1;
    }
  }
  unsigned long end = getCurTime();
  std::cout << "Average Time: " << (end - start) / 10 / 1000 << " ms" << std::endl;
  */
  
  // compare embeddings.
  float total_distance;
  // enumerate over features and compare distance assuming equal lengths.
  for (int i = 0; i < feat1.size(); ++i) {
    total_distance += absoluteDistance(feat1[i], feat2[i]);
  }
  std::cout << "[INFO]: the distance between faces is: " << total_distance << std::endl;
}





