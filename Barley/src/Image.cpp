#include "Image.h"

#include "imgui.h"

using namespace Barley;

void Image::Resize()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f,0.0f));
    ImGui::Begin(name.c_str());

    int w = ImGui::GetContentRegionAvail().x;
    int h = ImGui::GetContentRegionAvail().y;

    if (w != width || h != height)
    {
        width = w;
        height = h;
        Reset();
    }

    ImGui::PopStyleVar();
    ImGui::End();
}

void Image::Draw()
{

    // window containing our rendered image
    // remove padding
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f,0.0f));
    // 24 (0b1000 + 0b10000) remove scrollbars and scrolling
    ImGui::Begin(name.c_str(), NULL, 24);

    // TODO keep image position correctly and unstrected while moving
    // keep track of the window size
    // width_last = width;
    // height_last = height;

    // our images actual width and height, viewport may have changed size
    ImVec2 imageSize = ImVec2(width, height);

    // tell ImGui how to orient our image
    ImVec2 uv0 = ImVec2(0.0f,1.0f);
    ImVec2 uv1 = ImVec2(1.0f,0.0f);

    // draw the image into the viewport
    ImGui::Image((ImTextureID)(intptr_t)m_texture, imageSize, uv0, uv1);

    ImGui::PopStyleVar();
    ImGui::End();
}

void Image::Set(glm::vec4 *data)
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, data);
}

void Image::Reset()
{
    // Create a OpenGL texture identifier
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Setup filtering parameters for display
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
}
