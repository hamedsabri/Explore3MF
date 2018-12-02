#include <mainApp.h>

#include <camera.h>
#include <import3MF.h>
#include <export3MF.h>
#include <meshLine.h>
#include <meshModel.h>
#include <shaderLoaderGL.h>
#include <texture2D.h>
#include <worldGrid.h>

#include <nfd.h>

using namespace E3D;

namespace
{
    const glm::vec4 kBackgroundColor(0.13f, 0.13f, 0.13f, 1.0f);

    const float kWorldAxisLenght(0.5f);
}

MainApp::MainApp()
{
}

MainApp::~MainApp()
{
}

void
MainApp::init()
{
    windowGL()->setWindowIcon(RESOURCEDIR_PATH "Icons/window_icon.png");

    m_camera = std::make_shared<Camera>( glm::vec3(0.0f, 8.0f, 12.0f),
                                         glm::vec3(0.0f, 0.0f, 0.0f), 
                                         width(), height());

    m_vertexShader = std::make_shared<ShaderLoaderGL>(RESOURCEDIR_PATH "Shaders/vertexColorShader.vert",
                                                      RESOURCEDIR_PATH "Shaders/vertexColorShader.frag");

    m_facetedShader = std::make_shared<ShaderLoaderGL>(RESOURCEDIR_PATH "Shaders/facetedShader.vert",
                                                       RESOURCEDIR_PATH "Shaders/facetedShader.frag");

    m_worldGrid = std::make_unique<WorldGrid>();
}

void 
MainApp::preDraw()
{
}

void
MainApp::draw()
{
    glClearColor(kBackgroundColor[0],
                 kBackgroundColor[1],
                 kBackgroundColor[2],
                 kBackgroundColor[3]);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    m_worldGrid->draw(m_camera, m_vertexShader);

    if (m_importModel3MF)
    {
        for (auto mesh : m_importModel3MF->meshModels())
        {
            mesh->draw(m_camera, m_facetedShader);
        }
    }

    windowGL()->setTitle(std::to_string(Timer::getMillSecPerFrame()));
}

void
MainApp::postDraw()
{
}

void
MainApp::onResize(GLFWwindow* window, int width, int height)
{
    m_camera->updateViewSize(width, height);
}

void
MainApp::guiSetup()
{
    // window styling
    ImGuiStyle * style = &ImGui::GetStyle();

    style->WindowRounding = 3.0f;
    style->FrameRounding = 3.0f;

    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.0f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.0f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.0f);
    style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.0f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.0f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.0f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.0f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.0f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.0f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.09f, 0.12f, 1.0f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.0f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.0f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.0f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.0f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.0f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.10f, 0.09f, 0.12f, 1.0f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.10f, 0.09f, 0.12f, 1.0f);
    style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void
MainApp::guiDraw()
{
    // menu bar
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Import"))
            {
                nfdchar_t * fileName = nullptr;
                nfdresult_t result = NFD_OpenDialog("3mf, 3MF", nullptr, &fileName);

                if (result == NFD_OKAY)
                {
                    std::string path3MfFile(fileName);
                    std::wstring path3MfFileW(path3MfFile.begin(), path3MfFile.end());
                    m_importModel3MF = std::make_unique<Import3MF>(path3MfFileW);
                }
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Export"))
            {
                nfdchar_t * fileName = nullptr;
                nfdresult_t result = NFD_SaveDialog("3mf, 3MF", nullptr, &fileName);

                if (result == NFD_OKAY)
                {
                    std::string path3MfFile(fileName);
                    if (m_importModel3MF)
                    {
                        Export3MF exportModel3MF(path3MfFile + ".3mf", m_importModel3MF->meshModels());
                    }
                }
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    // mesh debug
    if (m_importModel3MF)
    {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0, 0.5f, 0.0f, 1.0f));
        ImGui::Begin("Mesh Debug", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::PopStyleColor(1);

        if (m_importModel3MF->packageIcon())
        {
            uintptr_t pID = static_cast<uintptr_t>(m_importModel3MF->packageIcon()->id());
            ImTextureID * textureID = reinterpret_cast<ImTextureID*>(pID);

            ImGui::Image(textureID, ImVec2(200, 200));
        }

        for (auto i = 0; i < m_importModel3MF->meshModels().size(); ++i)
        {
            auto mesh = m_importModel3MF->meshModels()[i];

            ImGui::PushID(i);
            if (ImGui::TreeNode("%s", mesh->getName().c_str()))
            {
                ImGui::PushID(i);
                if (ImGui::CollapsingHeader("Poly Count"))
                {
                    ImGui::Text("Vertex Count: %d", mesh->getNumVertices());
                    ImGui::Text("Triangle Count: %d", mesh->getNumTriangles());
                }

                if (ImGui::CollapsingHeader("Transform"))
                {
                    ImGui::Text("Translate");

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 0.0f, 0.0f, 1.0f));
                    if (ImGui::Button("TX")) { mesh->translate.x = 0.0f; }
                    ImGui::PopStyleColor(1);
                    ImGui::SameLine();
                    ImGui::InputFloat("##tx", (float*)&mesh->translate.x, 0.1f, 10000.0f);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0, 1.0f, 0.0f, 1.0f));
                    if (ImGui::Button("TY")) { mesh->translate.y = 0.0f; }
                    ImGui::PopStyleColor(1);
                    ImGui::SameLine();
                    ImGui::InputFloat("##ty", (float*)&mesh->translate.y, 0.1f, 10000.0f);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0, 0.0f, 1.0f, 1.0f));
                    if (ImGui::Button("TZ")) { mesh->translate.z = 0.0f; }
                    ImGui::PopStyleColor(1);
                    ImGui::SameLine();
                    ImGui::InputFloat("##tz", (float*)&mesh->translate.z, 0.1f, 10000.0f);

                    ImGui::Text("Rotation");

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 0.0f, 0.0f, 1.0f));
                    if (ImGui::Button("RX")) { mesh->rotate.x = 0.0f; }
                    ImGui::PopStyleColor(1);
                    ImGui::SameLine();
                    ImGui::InputFloat("##rx", (float*)&mesh->rotate.x, 0.1f, 360.0f);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0, 1.0f, 0.0f, 1.0f));
                    if (ImGui::Button("RY")) { mesh->rotate.y = 0.0f; }
                    ImGui::PopStyleColor(1);
                    ImGui::SameLine();
                    ImGui::InputFloat("##ry", (float*)&mesh->rotate.y, 0.1f, 360.0f);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0, 0.0f, 1.0f, 1.0f));
                    if (ImGui::Button("RZ")) { mesh->rotate.z = 0.0f; }
                    ImGui::PopStyleColor(1);
                    ImGui::SameLine();
                    ImGui::InputFloat("##rz", (float*)&mesh->rotate.z, 0.1f, 360.0f);

                    ImGui::Text("Scale");

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0, 0.0f, 0.0f, 1.0f));
                    if (ImGui::Button("SX")) { mesh->scale.x = 1.0f; }
                    ImGui::PopStyleColor(1);
                    ImGui::SameLine();
                    ImGui::InputFloat("##sx", (float*)&mesh->scale.x, 0.1f, 10000.0f);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0, 1.0f, 0.0f, 1.0f));
                    if (ImGui::Button("SY")) { mesh->scale.y = 1.0f; }
                    ImGui::PopStyleColor(1);  
                    ImGui::SameLine();          
                    ImGui::InputFloat("##sy", (float*)&mesh->scale.y, 0.1f, 10000.0f);

                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0, 0.0f, 1.0f, 1.0f));
                    if (ImGui::Button("SZ")) { mesh->scale.z = 1.0f; }
                    ImGui::PopStyleColor(1);
                    ImGui::SameLine();
                    ImGui::InputFloat("##sz", (float*)&mesh->scale.z, 0.1f, 10000.0f);
                }
                ImGui::PopID();
                ImGui::TreePop();
            }
            ImGui::PopID();
        }

        ImGui::End();
    }
}