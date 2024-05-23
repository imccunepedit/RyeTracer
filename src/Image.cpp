#include "Image.h"
#include "imgui.h"

void Image::draw_image() {
    texture_id = (void*)(intptr_t)texture;
    // window containing our rendered image
    // remove padding
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f,0.0f));
    // 24 (8+16) remove scrollbars and scrolling
    ImGui::Begin("Viewport", NULL, 24);
    // keep track of the window size
    window_width = ImGui::GetContentRegionAvail().x;
    window_height = ImGui::GetContentRegionAvail().y;

    // our images actual width and height, viewport may have changed size
    ImVec2 image_size = ImVec2(width, height);

    // tell ImGui how to orient our image
    ImVec2 uv0 = ImVec2(0.0f,0.0f);
    ImVec2 uv1 = ImVec2(1.0f,1.0f);

    // draw the image into the viewport
    ImGui::Image(texture_id, image_size, uv0, uv1);

    if (ImGui::BeginItemTooltip() )
    {
        ImGuiIO& io = ImGui::GetIO();
        ImVec2 region_size = ImVec2(10, 10);
        float region_zoom = 10;
        ImVec2 region0 = {io.MousePos.x, io.MousePos.y};
        ImVec2 region1 = {io.MousePos.x + region_size.x, io.MousePos.y + region_size.y};
        if (region1.x > image_size.x)
        {
            region1.x = image_size.x;
            region0.x = image_size.x - region_size.x;
        }
        if (region1.y > image_size.y)
        {
            region1.y = image_size.y;
            region0.y = image_size.y - region_size.y;
        }
        ImVec2 ttuv0 = ImVec2(region0.x / image_size.x, region0.y/image_size.y);
        ImVec2 ttuv1 = ImVec2(region1.x / image_size.x, region1.y/image_size.y);
        ImGui::Text("Zoom: %.2f", region_zoom);
        ImGui::Text("Min: (%.2f, %.2f)",region0.x, region0.y);
        ImGui::Text("Max: (%.2f, %.2f)",region1.x, region1.y);
        ImGui::Image(texture_id, ImVec2(region_size.x*region_zoom, region_size.y*region_zoom), ttuv0, ttuv1);
        ImGui::EndTooltip();
    }


    ImGui::End();
    ImGui::PopStyleVar();


}



bool Image::set_image(uint32_t* image_data) {
    // Create a OpenGL texture identifier
    GLuint image_texture;
    glGenTextures(1, &image_texture);
    glBindTexture(GL_TEXTURE_2D, image_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, image_data);

    texture = image_texture;

    return true;
}
