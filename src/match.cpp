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

float cosine_similarity( std::vector<float> A, std::vector<float> B, unsigned int Vector_Length )
{
  float dot = 0.0, denom_a = 0.0, denom_b = 0.0 ;
  float sim ;
  for( unsigned int i = 0u; i < Vector_Length; ++i ) {
    dot += A[i] * B[i] ;
    denom_a += A[i] * A[i] ;
    denom_b += B[i] * B[i] ;
  }
  sim = 1 - ( dot / ( sqrt(denom_a) * sqrt(denom_b) ) ) ;
  if ( sim >= 0 ){
    return sim ;
  }
  else
  {
    return -1 * sim;
  }
}

int main( int argc, char** argv ) {
  if ( argc != 3 ) {
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
  if ( iface.setup() != 0 ) {
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
  for (int i = 0; i < 1000; ++i) {
    if (iface.extract(face1, feat1) != 0) {
      std::cout << "extract feat fail" << std::endl;
      return -1;
    }
  }
  unsigned long end = getCurTime();
  std::cout << "Average Time: " << (end - start) / 1000 / 1000 << " ms" << std::endl;
  */
  
  // compare embeddings.
  float total_distance;
  total_distance = cosine_similarity( feat1, feat2, feat1.size() );
  std::cout << "[INFO]: the cosine distance between faces is: " << total_distance << std::endl;
}





