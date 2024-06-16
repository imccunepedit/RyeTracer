#version 430 core

layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;

layout(rgba8, binding = 0) uniform image2D imgOutput;

void main() {
    vec4 value = vec4(0,0,0,1);
    ivec2 texelCoord = ivec2(gl_GlobalInvocationID.xy); // vec3 of which worker we are

    value.x = float(texelCoord.x)/(gl_NumWorkGroups.x);
    value.y = float(texelCoord.y)/(gl_NumWorkGroups.y);

    imageStore(imgOutput, texelCoord, value);
}
