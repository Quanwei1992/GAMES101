

#include<cmath>
#include<Eigen/Core>
#include<Eigen/Dense>
#include<iostream>

#define PI 3.1415926f
#define DEG2RAD (PI/180.0f)

int main()
{

    Eigen::Vector3f P(2,1,1);
    Eigen::Matrix3f M;

    float rad = 45.0f * DEG2RAD;
    M << cos(rad),-sin(rad),1,
         sin(rad),cos(rad) ,2,
         0,0,1;
    
    Eigen::Vector3f P2 = M * P;
    std::cout<<P2<<std::endl;
    return 0;
}