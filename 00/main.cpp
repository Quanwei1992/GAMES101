

#include<cmath>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Dense>
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
    //std::cout<<P2<<std::endl;


    Eigen::Vector3f a(0,1,14);
    Eigen::Vector3f b(1,0,0);
    

    auto d = b.cross(a);

    std::cout<<d.z()<<std::endl;

    return 0;
}