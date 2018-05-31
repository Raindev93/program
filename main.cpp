#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

Mat img; Mat result;
Mat src_gray,detected_edges,dst;

//detekcja krawedzi
void CannyThreshold(int, void*) {
  blur( src_gray, detected_edges, Size(3,3) );
  Canny( detected_edges, detected_edges, 90, 90*3, 3 );
  dst = Scalar::all(0);

  src_gray.copyTo( dst, detected_edges);
}

 //pogrobienie krawedzi
void Erosion( int, void* ) {
  int erosion_type=MORPH_RECT;
  Mat element = getStructuringElement( erosion_type,Size( 2*3 + 1, 2*3+1 ),Point( 3, 3 ) );
  erode( dst, dst, element );
}

//obrot obrazu
Mat rotates(Mat src, double angle) {
    Mat dst;
    Point2f pt(src.cols/2., src.rows/2.);
    Mat r = getRotationMatrix2D(pt, angle, 1.0);
    warpAffine(src, dst, r, Size(src.cols, src.rows));
    return dst;
}

int match_method;
int max_Trackbar = 5;
double res[7];
string tem[7];

double MatchingMethod( int, String nazwa );

/** @function main */
int main( int argc, char** argv )
{
  img = imread( argv[1] );
  double col=200;
  double row=col/img.cols;
  row=round(row*img.rows);
  resize(img, img,Size(col,row) );


  cvtColor( img, src_gray, CV_BGR2GRAY );
  CannyThreshold(0, 0);
  bitwise_not ( dst, dst );
  Erosion(0,0);
  threshold( dst, img, 254, 255, 0);
  bitwise_not ( img, img );

  cout << MatchingMethod( 0, argv[2]);
  waitKey(0);
  return 0;
}

double MatchingMethod( int, String nazwa )
{
  Mat dsts;
  Mat tempp=imread(nazwa,1);
  bitwise_not ( tempp, tempp );
  cvtColor( tempp, tempp, CV_BGR2GRAY );
  Mat scal,rotat;
  resize(tempp, tempp,Size(round(1*img.cols),round(1*img.rows)) );
  double sumas = cv::sum( tempp )[0];
  sumas=sumas;
  double mins, maxs;
  int i=1;
  int i2=0;
  double k=0.8;
  double tab[40];
  for(i;i<7;i++){

    double col=k*img.cols;
    double row=col/img.cols;
    row=row*img.rows;
    resize(tempp, scal,Size(round(col),round(row)) );

    for(double ang=-3;ang<3;ang=ang+1){
      i2++;
      rotat = rotates(scal, ang);
      matchTemplate( img, rotat, result, CV_TM_CCORR);
      minMaxLoc(result, &mins, &maxs);
      tab[i2]=maxs;
    }
    k=k+0.04;
    i2++;
  }
  double mm=0;
  for(int s=0;s<40;s++){
    tab[s]=tab[s]/sumas;
    if(tab[s]>mm){
      mm=tab[s];
    }
  }
  return mm;
}
