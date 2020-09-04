//
// Created by goksu on 2/25/20.
//

#include <fstream>
#include "Scene.hpp"
#include "Renderer.hpp"


inline float deg2rad(const float& deg) { return deg * M_PI / 180.0; }

const float EPSILON = 0.00001;

// The main render function. This where we iterate over all pixels in the image,
// generate primary rays and cast these rays into the scene. The content of the
// framebuffer is saved to a file.
void Renderer::Render(const Scene& scene)
{
    std::vector<Vector3f> framebuffer(scene.width * scene.height);

    float scale = tan(deg2rad(scene.fov * 0.5));
    float imageAspectRatio = scene.width / (float)scene.height;
    Vector3f eye_pos(-1, 5, 10);
    int m = 0;
    for (uint32_t j = 0; j < scene.height; ++j) {
        for (uint32_t i = 0; i < scene.width; ++i) {
            // generate primary ray direction
            // Screen space to NDC space
            float nx = (i + 0.5f) * 2 / scene.width - 1.0f;
            float ny = (j + 0.5f) * 2 / scene.height - 1.0f;

            // NDC space to world space

            // Project matrix
            /*
            *   [ n/r ,0   ,0       ,0      ]
            *   [ 0   ,n/t ,0       ,0      ]
            *   [ 0   ,0   ,n+f/n-f ,2nf/f-n]
            *   [ 0   ,0   ,1       ,0      ]
            */

            //  
            // 在投影矩阵中 x 的系数为 n/r
            // 在投影矩阵中 y 的系数为 n/t
            // 现在要做一个逆操作，所以我们用 NDC空间的坐标分别除以投影矩阵中的系数
            // x = nx / n / r
            // y = ny / n / t
            // 其中 n(相机到近投影面距离为 默认情况下为1）
            // => 
            // x = nx * r
            // y = ny * t
            // 其中 r = tan(fov/2)*aspect * |n|， t=tan(fov/2) * |n| , |n| = 1
            // 所以可得,世界空间中坐标为
            // x = nx * tan(fov/2)*aspect
            // y = ny * tan(fov/2)*aspect

            float x = nx * scale * imageAspectRatio;
            float y = -ny * scale;


            Vector3f dir = Vector3f(x, y, -1); // Don't forget to normalize this direction!
            dir = normalize(dir);
            Ray ray(eye_pos,dir);      
            framebuffer[m++] = scene.castRay(ray, 0);

        }
        UpdateProgress(j / (float)scene.height);
    }
    UpdateProgress(1.f);

    // save framebuffer to file
    FILE* fp = fopen("binary.ppm", "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", scene.width, scene.height);
    for (auto i = 0; i < scene.height * scene.width; ++i) {
        static unsigned char color[3];
        color[0] = (unsigned char)(255 * clamp(0, 1, framebuffer[i].x));
        color[1] = (unsigned char)(255 * clamp(0, 1, framebuffer[i].y));
        color[2] = (unsigned char)(255 * clamp(0, 1, framebuffer[i].z));
        fwrite(color, 1, 3, fp);
    }
    fclose(fp);    
}
