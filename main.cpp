#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <windows.h>
#include <stdio.h>
using namespace std;
#define pi 3.14159265358979323846
#define maxAngle 180

bool intersection(cv::Point2f o1, cv::Point2f o2, cv::Point2f p1, cv::Point2f p2, cv::Point2f &r)
{
	cv::Point2f x = o2 - o1;
	cv::Point2f d1 = p1 - o1;
	cv::Point2f d2 = p2 - o2;

	float cross = d1.x*d2.y - d1.y*d2.x;
	if (abs(cross) < 1e-8)
	{
		return false;
	}

	double t1 = (x.x * d2.y - x.y * d2.x) / cross;
	
	
	r = o1 + d1 * t1;
	printf("\n 1 \n");
	printf("x : %f  y : %f \n", r.x, r.y);
	return true;
}

int main()
{
	//�̹��� �ε�
	cv::Mat image = cv::imread("input.jpg");

	//ĳ�� �˰����� ���� �׷��� ������ �̹����� ��ȯ
	cv::Mat gray;
	cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
	

	// ĳ�� �˰��� ����
	cv::Mat contours;
	cv::Canny(image, contours, 100, 350);	//100, 350�� ���� threshold��.

	//cv::namedWindow("contours");
	//cv::imshow("contours", contours);

	//�̹��� ����, ����, �밢��
	const int width = image.cols;
	const int height = image.rows;
	const int diagonal = sqrt(width * width + height * height);
	double h_height = diagonal * 2;
	int voting_width = maxAngle;
	int voting_height = h_height * 2;
	int voting_size = voting_height * voting_width;

	int *voting = (int*)malloc(sizeof(int)*voting_size);
	memset(voting, 0, sizeof(int)*voting_size);

	int xnum1[360];
	int xnum2[360];
	int ynum1[360];
	int ynum2[360];

	int trueXnum[360];
	int trueYnum[360];

	int allcount = 0;
	cv::Point2f f1[360];
	cv::Point2f f2[360];
	cv::Point2f f3[360];

	cv::Point2f truef[360];

	//�߾��� ��ǥ�� ����
	double a_sin[maxAngle];
	double a_cos[maxAngle];
	float PIPI = pi / maxAngle;


	

	//���� ��ȯ ����
	//����ȯ
	for (int angle = 0; angle < maxAngle; angle++)
	{
		a_sin[angle] = sin(angle*PIPI);
		a_cos[angle] = cos(angle*PIPI);
	}
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (contours.at<uchar>(y, x) > 0)
				for (int angle = 0; angle < maxAngle; angle++)
				{
					int r = (x - (width / 2))*a_cos[angle] + (y - (height/2))*a_sin[angle];

					r = r + h_height;
					voting[r*voting_width + angle] += 1;
				}
		}
	}
	//

	int xcount = 0; //���°����
	int ycount = 0; //���°����

	for (int r = 0; r < voting_height; r++)
		for (int angle = 0; angle < maxAngle; angle++)
		{
			bool what = false;
			
			int max = voting[r * voting_width + angle];
			int x1 = 0;
			int y1 = 0;
			int x2 = width;
			int y2 = height;
			
			

			//������Ȧ�� ���� ����
			if (voting[r * voting_width + angle] > 200)
			{
				
				for (int y = -20; y <= 20; y++)
				{
					for (int x = -20; x <= 20; x++)
					{
						int new_r = r + y;
						int nAngle = angle + x;
						

						if (new_r >= 0 && new_r < voting_height)
						{
							if (voting[new_r * voting_width + nAngle] > max)
							{
								max = voting[new_r * voting_width + nAngle];
								
							}
						}
					}
					
				}
				//�ƽ��� if
				if (max > voting[r * voting_width + angle])
				{
					what = true;
					
				}
				else
				{
					what = false;
				}
				

				
				
				if(what == false)
				{
					if (angle >= 36 && angle <= 144) //���� //3:4�� �������� tan��Ÿ�� 36���̹Ƿ�
					{
						xcount++;

					y1 = ((r - h_height) - (x1 - (width/ 2))*a_cos[angle]) / a_sin[angle] + (height / 2);
					y2 = ((r - h_height) - (x2 - (width / 2))*a_cos[angle]) / a_sin[angle] + (height / 2);

					}
					else //������
					{
						ycount++;

					x1 = ((r - h_height) - (y1 - (height / 2))*a_sin[angle]) / a_cos[angle] + (width / 2);
					x2 = ((r - h_height) - (y2 - (height / 2))*a_sin[angle]) / a_cos[angle] + (width / 2);
					}
	
					printf("qqqqqqqqqqqqqqq  %d,%d \n", x1, y1);
					printf("wwwwwwwwwwwwwww  %d,%d \n", x2, y2);
					
					xnum1[allcount] = x1;
					xnum2[allcount] = x2;
					ynum1[allcount] = y1;
					ynum2[allcount] = y2;
					
					printf("xnum1[%d]  %d,%d \n",allcount, xnum1[allcount], ynum1[allcount]);
					printf("xnum2[%d]  %d,%d \n", allcount, xnum2[allcount], ynum2[allcount]);
					
					//cv::circle(image, cv::Point(634,200), 5, CV_RGB(255, 0, 15), 100);
					//cv::circle(image, cv::Point(x1, y1), 5, CV_RGB(0, 0, 250),100);
					//cv::circle(image, cv::Point(x2, y2), 5, CV_RGB(0, 0, 250),100);

					if (y1 >= y2)
					{
						trueXnum[allcount] = x1;
						trueYnum[allcount] = y1;
						printf("tttttx  %d,%d \n", trueXnum[allcount], trueYnum[allcount]);
						
						cv::circle(image, cv::Point(trueXnum[allcount], trueYnum[allcount]), 5, CV_RGB(0, 255, 0), 50);
					}
					else
					{
						trueXnum[allcount] = x2;
						trueYnum[allcount] = y2;
						printf("ttttty  %d,%d \n", trueXnum[allcount], trueYnum[allcount]);
						cv::circle(image, cv::Point(trueXnum[allcount], trueYnum[allcount]), 5, CV_RGB(0, 255, 0), 50);
						
					}

					allcount++; //��� ���� ����Ǿ�����
					
				//line(image, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(255, 0, 0), 4);
					


				
				}
				
			}

		}

	
	if(allcount>=1)
	{
		for (int i = 0; i <= allcount - 1; i++)
		{
			cv::Point2f o1(xnum1[i], ynum1[i]);
			cv::Point2f o2(xnum2[i], ynum2[i]);
			cv::Point2f q1(xnum1[i + 1], ynum1[i + 1]);
			cv::Point2f q2(xnum2[i + 1], ynum2[i + 1]);
			
			intersection(o1,q1,o2,q2, f3[i]);
			//cv::circle(image, f3[0], 5, CV_RGB(250, 0, 250), 100);
			
			

		}
		cv::Point2f ftrue3[360];
		int k = 0;

		for (int i = 0; i <= allcount - 3; i++)
		{

			if (abs(f3[i].x - (width / 2)) < abs(f3[i].x - (width /2)))
			{
				k = i;
			}
			else
			{
				k = i + 1;
			}

		}

		printf("\n\n k ::  %d", k);
		for (int i = 0; i <= allcount - 1; i++)
		{
			if (i == allcount - 1)
			{
				line(image, cv::Point(trueXnum[i], trueYnum[i]), f3[k], cv::Scalar(255, 0, 0), 4);
			}
			else
			{
				line(image, cv::Point(trueXnum[i], trueYnum[i]), f3[k], cv::Scalar(255, 0, 0), 4);
				line(image, cv::Point(trueXnum[i + 1], trueYnum[i + 1]), f3[k], cv::Scalar(255, 0, 0), 4);
			}
			
		}

		
		printf("%d \n", f3[1]);
		printf("%d \n", f3[2]);
		printf("%d \n", f3[3]);
		
			
			

		
	}
	

	
	//�̹����� line �׸��� ���
	//cv::Point start_point(width / 2, 0);		//line�� ������ 
	//cv::Point end_point(width / 2, height - 1);	//line�� ����	

	// �Ķ��� ������ �׸���. BGR����
	//cv::line(image, start_point, end_point, cv::Scalar(255, 0, 0), 1); 
	
	cv::namedWindow("Result");
	cv::imshow("Result", image);

	//�̹��� ����
	cv::imwrite("Result.jpg", image);

	cv::waitKey(0);

	return 0;
}

