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


Vector3f Scene::shade(Intersection& p, Vector3f wo) const
{
    if (p.m->hasEmission())
    {
        return p.m->getEmission();
    }

    Vector3f dir2NextObj = p.m->sample(wo, p.normal);
    Intersection nextObj = intersect(Ray(p.coords, dir2NextObj));
    if (!nextObj.happened)
    {
        return {};
    }

	float pdf = p.m->pdf(wo, dir2NextObj, p.normal);
	Vector3f f_r = p.m->eval(wo, dir2NextObj, p.normal); //BRDF

    if (nextObj.m->hasEmission())
    {
        return nextObj.m->getEmission() * f_r * dotProduct(p.normal, dir2NextObj) / pdf;
    }
    else {
		if (get_random_float() > RussianRoulette)
		{
			return {};
		}
        return shade(nextObj, -dir2NextObj) * f_r * dotProduct(p.normal, dir2NextObj) / pdf / RussianRoulette;
    }
}



// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
	auto interObj = intersect(ray);
	if (!interObj.happened) return {};
    return shade(interObj,-ray.direction);
}