#version 430 core

#define objectCount 10
#define materialCount 10


layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
layout (rgba8, binding = 0) uniform image2D imgOutput;

struct Sphere {
    vec4 position;
    float radius;
    uint materialID;
};

struct Ray {
    vec4 origin;
    vec4 direction;
};

struct HitData {
    float distance;
    vec4 point;
    vec4 normal;
    bool front;
    uint materialID;
};

struct Material {
    vec4 color;
};


uniform mat4 inverseView;
uniform mat4 inverseProjection;


uniform Material Materials[materialCount];
uniform Sphere Objects[objectCount];


bool SphereHit(Sphere sphere, Ray ray, out float hitDistance)
{
    vec4 ray_sphere = ray.origin - sphere.position;
    float b = 2.0 * dot(ray.direction, ray_sphere);
    float c = -1.0 * dot(ray_sphere, ray_sphere) - sphere.radius * sphere.radius;

    float discriminant = b*b - 4.0 * c;

    if (discriminant <= 0)
    {
        return false;
    }

    float min_t = 0.000001;
    hitDistance = (-b - sqrt(discriminant)) * 0.5;
    if (hitDistance < min_t)
    {
        hitDistance = (-b - sqrt(discriminant)) * 0.5;
        if (hitDistance < min_t)
        {
            return false;
        }
    }

    return true;
}


void main()
{
    ivec2 texelCoord = ivec2(gl_GlobalInvocationID.xy); // vec2 of which worker we are
    uvec2 dims = gl_NumWorkGroups.xy; // max workers in each dimension
    vec4 value = vec4(0,0,0,1);

    vec4 screenTarget = vec4(vec2(texelCoord)/dims * 2 - 1, 0, 1);
    vec4 worldTarget = inverseProjection * screenTarget;
    vec4 worldDirection = inverseView * vec4(worldTarget.xyz, 0);

    Ray ray = Ray(vec4(0,0,0,0), worldDirection);

    value = vec4(worldDirection.xyz, 1);
    imageStore(imgOutput, texelCoord, value);
}
