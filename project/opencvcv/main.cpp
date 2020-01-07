#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main()
{
	//�̹��� �ε�
	cv::Mat image = cv::imread("input.jpg");

	//ĳ�� �˰����� ���� �׷��� ������ �̹����� ��ȯ
	cv::Mat gray;
	cv::cvtColor(image, gray, CV_BGR2GRAY);
	
	// ĳ�� �˰��� ����
	cv::Mat contours;
	cv::Canny(image, contours, 100, 350);	//100, 350�� ���� threshold��.

	//cv::namedWindow("contours");
	//cv::imshow("contours", contours);

	//�̹��� ����, ����, �밢��
	const int width = image.cols;
	const int height = image.rows;
	const int diagonal = sqrt(width * width + height * height);

	//���� ��ȯ ����
	//...
	
	//�̹����� line �׸��� ���
	cv::Point start_point(width / 2, 0);		//line�� ������ 
	cv::Point end_point(width / 2, height - 1);	//line�� ����	

	// �Ķ��� ������ �׸���. BGR����
	cv::line(image, start_point, end_point, cv::Scalar(255, 0, 0), 1); 
	
	cv::namedWindow("Result");
	cv::imshow("Result", image);

	//�̹��� ����
	cv::imwrite("Result.jpg", image);

	cv::waitKey(0);

	return 0;
}
