#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{
	//이미지 로드
	cv::Mat image = cv::imread("input.jpg");

	//캐니 알고리즘을 위해 그레이 스케일 이미지로 변환
	cv::Mat gray;
	cv::cvtColor(image, gray, CV_BGR2GRAY);
	
	// 캐니 알고리즘 적용
	cv::Mat contours;
	cv::Canny(image, contours, 100, 350);	//100, 350은 각각 threshold값.

	//cv::namedWindow("contours");
	//cv::imshow("contours", contours);

	//이미지 가로, 세로, 대각선
	const int width = image.cols;
	const int height = image.rows;
	const int diagonal = sqrt(width * width + height * height);

	//허프 변환 구현
	//...
	
	//이미지에 line 그리는 방법
	cv::Point start_point(width / 2, 0);		//line의 시작점 
	cv::Point end_point(width / 2, height - 1);	//line의 끝점	

	// 파랑색 선으로 그리기. BGR순서
	cv::line(image, start_point, end_point, cv::Scalar(255, 0, 0), 1); 
	
	cv::namedWindow("Result");
	cv::imshow("Result", image);

	//이미지 저장
	cv::imwrite("Result.jpg", image);

	cv::waitKey(0);

	return 0;
}
