//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;//[0~1]*13650    
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){//random get the first area > p light,return                
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
	Vector3f l_o;

	const auto& interObj = intersect(ray);
	if (!interObj.happened) return {};
	if (interObj.m->hasEmission())
	{
		return l_o;
	}


	const Vector3f& obj2lightDir = interObj.m->sample(ray.direction, interObj.normal);

	float pdf = interObj.m->pdf(ray.direction, obj2lightDir, interObj.normal);


	const auto& interLight = intersect(Ray(interObj.coords, obj2lightDir));
	if (!interLight.happened) return l_o;
	if (!interLight.m->hasEmission()) return l_o;

	
	Vector3f f_r = interObj.m->eval(ray.direction, obj2lightDir, interObj.normal);
	l_o = interLight.m->getEmission() * std::max(.0f,dotProduct(interObj.normal, obj2lightDir)) * f_r / pdf;
	return l_o;



		// TO DO Implement Path Tracing Algorithm here
	//Intersection objectInter = intersect(ray);
	//if (!objectInter.happened)
	//	return {};

	//if (objectInter.m->hasEmission())
	//	return objectInter.m->getEmission();

	//Vector3f L_dir;
	//Intersection interLight;
	//float pdf_light;
	//sampleLight(interLight, pdf_light);

	//Vector3f p = objectInter.coords;
	//Vector3f x = interLight.coords;
	//Vector3f obj2light = x - p;
	//Vector3f obj2lightdir = obj2light.normalized();
	//Vector3f N = objectInter.normal;
	//Vector3f NN = interLight.normal;

	//Intersection t = intersect(Ray(p, obj2lightdir));
	//if (t.distance - obj2light.norm() > -EPSILON)
	//{
	//	float NL = dotProduct(obj2lightdir, N);
	//	float NNL = dotProduct(-obj2lightdir, NN);
	//	float r2 = dotProduct(obj2light, obj2light);
	//	Vector3f eval = objectInter.m->eval(ray.direction, obj2lightdir, N);
	//	L_dir = interLight.emit * eval * NL * NNL / (r2 * pdf_light);
	//}


	//if (get_random_float() > RussianRoulette)
	//{
	//	return L_dir;
	//}

	//Vector3f L_indir;
	//Vector3f obj2nextobjdir = objectInter.m->sample(ray.direction, objectInter.normal).normalized();
	//Ray obj2nextobjray = { objectInter.coords, obj2nextobjdir };
	//Intersection nextobjInter = intersect(obj2nextobjray);
	//if (nextobjInter.happened && !nextobjInter.m->hasEmission())
	//{
	//	float pdf = objectInter.m->pdf(ray.direction, obj2nextobjdir, objectInter.normal);
	//	L_indir = castRay(obj2nextobjray, depth + 1) * objectInter.m->eval(ray.direction, obj2nextobjdir, objectInter.normal) * dotProduct(obj2nextobjdir, objectInter.normal) / pdf / RussianRoulette;
	//}


	//return L_dir + L_indir;

}