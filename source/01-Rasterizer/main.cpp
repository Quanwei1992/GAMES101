
/*
* 
*/


#include "WindowsApp.hpp"
#include <cmath>
#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>

#define PI 3.14159265f
#define DEG2RAD(x) ((x)*((PI * 2.0f) / 360.0f))

using namespace Eigen;

class App : public WindowsApplication
{
public:
	App() : WindowsApplication("01-Rasterizer",800,600){}
    virtual  ~App() {};

protected:
	virtual void OnTick(double dt)
	{
		Clear(RGB(0, 0, 0));

		_deg += (float)dt * 100.0f;
		_deg = fmod(_deg, 360.0f);
		float rad = DEG2RAD(_deg);

		Vector3f v(80, 0, 1.0f);

		Matrix3f m;
		m << cos(rad), -sin(rad), 400,
			sin(rad), cos(rad), 300,
			0, 0, 1;

		Vector3f rv = m * v;
		SetPixel((int)rv.x(), (int)rv.y(), RGB(0, 0, 255));
		SwapBuffer();
	}

	float _deg = 0.0f;

};



int main(int argc, const char** argv)
{
	App app;
	app.Run();
}




