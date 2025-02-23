// 离散数学展示.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <opencv2\opencv.hpp>
#include <stack>
#define PI 3.1415926

using namespace std;
using namespace cv;

typedef struct Node
{
	int degree;
	int index;
}Node;

Point* points;
Mat image(512, 512, CV_8UC1);
stack<vector<int>> links;  //数组容器（可变长度）


void init(int n)
{
	//初始化点在图中的位置
	Point origin(255, 255);
	double degree = 360.0 / n / 180 * PI;
	int r = 200;
	points = new Point[n];
	for (int i = 0; i < n; i++)
	{
		points[i].x = origin.x + r * cos(degree * i);
		points[i].y = origin.y + r * sin(degree * i);
		circle(image, points[i], 6, (255, 255, 255), -1);
	}
}

void draw()
{
	while (!links.empty())
	{
		vector<int> link = links.top();
		int begin = link[0];
		//cout << begin << " ";
		for (int i = 1; i < link.size(); i++)
		{
			int end = link[i];
			line(image, points[begin], points[end], (255, 255, 255), 2);
			//cout << end << " ";
		}
		//cout << endl;
		links.pop();
	}
	imshow("image", image);
	waitKey(0);
}

/*选择排序*/
void sort(::Node a[], int n) {
	for (int i = 0; i < n; i++)
	{
		int temp = i;
		for (int j = i + 1; j < n; j++)
		{
			if (a[j].degree > a[temp].degree)
			{
				temp = j;
			}
		}
		if (temp != i)
		{
			::Node t = a[i];
			a[i] = a[temp];
			a[temp] = t;
		}
	}
}

int Havel(::Node a[], int n) {
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum = sum + a[i].degree;
	}

	if ((a[0].degree > n - 1) || (sum % 2 != 0))
	{  //第一判断条件
		return -1;
	}
	sum = 0;
	for (int i = 0; i < n; i++)
	{
		sort(a, n);      //排序
		for (int m = 0; m < n; m++)
		{
			cout << a[m].degree << " ";
		}
		cout << endl;

		vector<int> link;
		link.push_back(a[0].index);
		for (int j = 0; j < a[0].degree; j++)
		{  //Havel定理
			a[j + 1].degree--;          //后a[0]个元素都-1
			link.push_back(a[j + 1].index);
		}
		links.push(link);
		a[0].degree = 0;      //第一元素置零

		for (int k = 0; k < n; k++)
		{  //遍历数组查看是否存在负数
			if (a[k].degree < 0)
				return -1;
		}

		for (int h = 0; h < n; h++)
		{  //判断数组是否全为0
			sum = sum + a[h].degree;
		}
		if (sum == 0)     //若全为0，则可简单图化
			return 1;
	}
}

int main() {
	int x = 0;
	::Node a[50];
	char ch;
	int n;
	cout << "Please input the number of points:" << endl;
	cin >> n;
	init(n);
	if (n <= 0)
	{
		cout << "Input error!" << endl;
	}
	else
	{

		cout << "Please input the grades:" << endl;

		int i = 0;
		do
		{
			cin >> a[i].degree;
			a[i].index = i;
			ch = getchar();
			i++;
		} while (ch != '\n');

		if (i != n)
		{
			cout << "Input error" << endl;
		}
		else
		{
			sort(a, n);
			int s = Havel(a, n);         //调用该函数予以判断是否可简单图化
			if (s == -1)
			{
				cout << endl;
				cout << "No!" << endl;
			}
			else {
				cout << endl;
				cout << "Yes!" << endl;
				draw();
			}
		}
	}
	delete[] points;
	return 0;
}