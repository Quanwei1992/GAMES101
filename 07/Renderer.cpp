//
// Created by goksu on 2/25/20.
//

#include <fstream>
#include <thread>
#include "Scene.hpp"
#include "Renderer.hpp"
#include <mutex>
#include <vector>


inline float deg2rad(const float& deg) { return deg * M_PI / 180.0; }

const float EPSILON = 0.00001;
int g_complateTotals = 0;
std::mutex g_mutex;

void render_thread(std::vector<Vector3f>& fbuffer, const Scene& scene,int spp, int y0, int y1)
{
	float scale = tan(deg2rad(scene.fov * 0.5));
	float imageAspectRatio = scene.width / (float)scene.height;
	Vector3f eye_pos(278, 273, -800);
	for (int i = y0; i < y1; i++)
	{
		for (int j = 0; j < scene.width; j++)
		{
            int index = i * scene.width + j;
			for (int k = 0; k < spp; k++)
			{
				float x = get_random_float();
				float y = get_random_float();
				float _x = (2 * (j + x) / (float)scene.width - 1) *
					imageAspectRatio * scale;
				float _y = (1 - 2 * (i + y) / (float)scene.height) * scale;
				Vector3f dir = normalize(Vector3f(-_x, _y, 1));
				Ray ray = Ray(eye_pos, dir);
				fbuffer[index] += scene.castRay(ray, 0) / spp;
			}
		}
		g_mutex.lock();
		g_complateTotals++;
        UpdateProgress(g_complateTotals / (float)scene.height);
		g_mutex.unlock();
	}
}

// The main render function. This where we iterate over all pixels in the image,
// generate primary rays and cast these rays into the scene. The content of the
// framebuffer is saved to a file.
void Renderer::Render(const Scene& scene,int spp)
{
    std::vector<Vector3f> framebuffer(scene.width * scene.height);

    float scale = tan(deg2rad(scene.fov * 0.5));
    float imageAspectRatio = scene.width / (float)scene.height;
    Vector3f eye_pos(278, 273, -800);



    int m = 0;
    g_complateTotals = 0;

    std::cout << "SPP: " << spp << "\n";

	int numThreads = std::thread::hardware_concurrency();
	int lines = scene.height / numThreads + 1;
    std::vector<std::thread> wokers;
	for (int i = 0; i < numThreads; i++)
	{
        int y0 = i * lines;
        int y1 = std::min(y0 + lines,scene.height);
        std::cout << "id:" <<i << " " << y0 << "=>" << y1 << std::endl;
        wokers.push_back(std::thread(render_thread,std::ref(framebuffer),std::ref(scene),spp,y0,y1));
	}

    for (int i =0;i<wokers.size();i++)
    {
        wokers[i].join();
    }
   

    UpdateProgress(1.f);

    // save framebuffer to file
    FILE* fp = fopen("binary.ppm", "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", scene.width, scene.height);
    for (auto i = 0; i < scene.height * scene.width; ++i) {
        static unsigned char color[3];
        color[0] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].x), 0.6f));
        color[1] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].y), 0.6f));
        color[2] = (unsigned char)(255 * std::pow(clamp(0, 1, framebuffer[i].z), 0.6f));
        fwrite(color, 1, 3, fp);
    }
    fclose(fp);    
}
