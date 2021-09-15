#pragma once
#include "hittable.h"
#include "material.h"
#include "aabb.h"

namespace ray_tracing
{
    class triangle : public hittable
    {
        vec3 vertices[3];
        std::shared_ptr<material> mat_ptr;
        aabb bbox;

    public:
        triangle(const vec3 &a, const vec3 &b, const vec3 &c, std::shared_ptr<material> mat_ptr_)
            : vertices{a, b, c}, mat_ptr{mat_ptr_}
        {
            for (const vec3 &i : vertices)
                bbox.push_back(i);
        }

        inline vec3 &a() { return vertices[0]; }
        inline vec3 &b() { return vertices[1]; }
        inline vec3 &c() { return vertices[2]; }

        inline const vec3 &a() const { return vertices[0]; }
        inline const vec3 &b() const { return vertices[1]; }
        inline const vec3 &c() const { return vertices[2]; }

        // reference: Fundamental of Computer Graphics, Forth Edition by Marschner,  Steve Shirley, Peter. p.77-79
        virtual bool hit(const ray &r, float t_min, float t_max, hit_record &out_record) const override
        {
            if (!bbox.hit(r, t_min, t_max))
                return false;

            mat3 A{vertices[0] - vertices[1], vertices[0] - vertices[2], r.direction};
            vec3 B{vertices[0] - r.origin()};
            vec3 temp = glm::inverse(A) * B;
            float &beta = temp[0];
            float &gamma = temp[1];
            float &t = temp[2];

            if (t < t_min || t >= t_max)
                return false;
            if (beta < 0 || beta > 1)
                return false;
            if (gamma < 0 || gamma + beta > 1)
                return false;

            out_record.ray_parameter = t;
            out_record.position = r.point_at_parameter(t);
            out_record.normal = unit_vector(cross(vertices[1] - vertices[0], vertices[2] - vertices[0]));
            out_record.front_face = dot(out_record.normal, r.direction) < 0 ? true : false;
            out_record.mat_ptr = mat_ptr ? mat_ptr.get() : nullptr;
            out_record.uv_coord = {beta, gamma};
            return true;
        };

        virtual bool bounding_box(aabb &out_aabb) const override
        {
            out_aabb = bbox;
            return true;
        }
    };
}
