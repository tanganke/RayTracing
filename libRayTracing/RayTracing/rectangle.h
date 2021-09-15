#pragma once
#include "hittable.h"
#include "material.h"

namespace ray_tracing
{
    class xy_rect : public hittable
    {
    public:
        float x0, x1, y0, y1, k;
        std::shared_ptr<material> mat_ptr;

        /**
         * @brief 1 for positive z, -1 for negative z
         * 
         */
        int front_face{1};

    public:
        xy_rect() = default;
        xy_rect(float x0_, float x1_, float y0_, float y1_, float k_, std::shared_ptr<material> mat_ptr_)
            : x0{x0_}, x1{x1_}, y0{y0_}, y1{y1_}, k{k_}, mat_ptr{mat_ptr_}
        {
            assert(x0 <= x1);
            assert(y0 <= y1);
        }

        virtual bool hit(const ray &r, float t_min, float t_max, hit_record &out_record) const override
        {
            float t = (k - r.origin().z) / r.direction.z;
            if (t <= t_min || t >= t_max)
                return false;
            vec3 hit_point = r.point_at_parameter(t);
            float &x = hit_point.x;
            float &y = hit_point.y;
            if (x < x0 || x > x1 || y < y0 || y > y1)
                return false;
            out_record.uv_coord = vec2{(x - x0) / (x1 - x0), (y - y0) / (y1 - y0)};
            out_record.ray_parameter = t;
            out_record.position = hit_point;
            out_record.mat_ptr = mat_ptr ? mat_ptr.get() : nullptr;
            out_record.front_face = true;
            out_record.normal = r.origin().z > k ? vec3{0, 0, 1} : vec3{0, 0, -1};
            return true;
        }

        virtual bool bounding_box(aabb &out_aabb) const override
        {
            out_aabb = aabb{vec3{x0, y0, k - 0.0001}, vec3{x1, y1, k + 0.0001}};
            return true;
        }
    };

    class yz_rect : public hittable
    {
    public:
        float y0, y1, z0, z1, k;
        std::shared_ptr<material> mat_ptr;

        /**
         * @brief 1 for positive x, -1 for negative x
         * 
         */
        int front_face{1};

    public:
        yz_rect() = default;
        yz_rect(float y0_, float y1_, float z0_, float z1_, float k_, std::shared_ptr<material> mat_ptr_)
            : y0{y0_}, y1{y1_}, z0{z0_}, z1{z1_}, k{k_}, mat_ptr{mat_ptr_}
        {
            assert(y0 <= y1);
            assert(z0 <= z1);
        }

        virtual bool hit(const ray &r, float t_min, float t_max, hit_record &out_record) const override
        {
            float t = (k - r.origin().x) / r.direction.x;
            if (t <= t_min || t >= t_max)
                return false;
            vec3 hit_point = r.point_at_parameter(t);
            float &y = hit_point.y;
            float &z = hit_point.z;
            if (y < y0 || y > y1 || z < z0 || z > z1)
                return false;
            out_record.uv_coord = vec2{(y - y0) / (y1 - y0), (z - z0) / (z1 - z0)};
            out_record.ray_parameter = t;
            out_record.position = hit_point;
            out_record.mat_ptr = mat_ptr ? mat_ptr.get() : nullptr;
            out_record.front_face = true;
            out_record.normal = r.origin().x > k ? vec3{1, 0, 0} : vec3{-1, 0, 0};
            return true;
        }

        virtual bool bounding_box(aabb &out_aabb) const override
        {
            out_aabb = aabb{vec3{k - 0.0001, y0, z0}, vec3{k + 0.0001, y1, z1}};
            return true;
        }
    };

    class zx_rect : public hittable
    {
    public:
        float z0, z1, x0, x1, k;
        std::shared_ptr<material> mat_ptr;

        /**
         * @brief 1 for positive y, -1 for negative y
         * 
         */
        int front_face{1};

    public:
        zx_rect() = default;
        zx_rect(float z0_, float z1_, float x0_, float x1_, float k_, std::shared_ptr<material> mat_ptr_)
            : z0{z0_}, z1{z1_}, x0{x0_}, x1{x1_}, k{k_}, mat_ptr{mat_ptr_}
        {
            assert(z0 <= z1);
            assert(x0 <= x1);
        }

        virtual bool hit(const ray &r, float t_min, float t_max, hit_record &out_record) const override
        {
            float t = (k - r.origin().y) / r.direction.y;
            if (t <= t_min || t >= t_max)
                return false;
            vec3 hit_point = r.point_at_parameter(t);
            float &z = hit_point.z;
            float &x = hit_point.x;
            if (z < z0 || z > z1 || x < x0 || x > x1 || t < t_min || t >= t_max)
                return false;
            out_record.uv_coord = vec2{(z - z0) / (z1 - z0), (x - x0) / (x1 - x0)};
            out_record.ray_parameter = t;
            out_record.position = hit_point;
            out_record.mat_ptr = mat_ptr ? mat_ptr.get() : nullptr;
            out_record.front_face = true;
            out_record.normal = r.origin().y > k ? vec3{0, 1, 0} : vec3{0, -1, 0};
            return true;
        }

        virtual bool bounding_box(aabb &out_aabb) const override
        {
            out_aabb = aabb{vec3{x0, k - 0.0001, z0}, vec3{x1, k + 0.0001, z1}};
            return true;
        }
    };
}