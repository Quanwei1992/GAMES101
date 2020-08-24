
/*
* 作业描述
    给定一个点 P=(2,1), 将该点绕原点先逆时针旋转 45◦，再平移 (1,2), 计算出
变换后点的坐标（要求用齐次坐标进行计算）。
*/


#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
#include<iostream>

#define PI 3.14159265f
#define DEG2RAD(x) ((x)*((PI * 2.0f) / 360.0f))
using namespace Eigen;

int main(){


	float rad = DEG2RAD(45.0f);

	Vector3f v(1, 0, 1.0f);

	Matrix3f m;
	m << cos(rad), -sin(rad), 0,
		 sin(rad),  cos(rad), 0,
		        0,         0, 1;

	Vector3f rv = m * v;

	std::cout << rv;

    return 0;
}