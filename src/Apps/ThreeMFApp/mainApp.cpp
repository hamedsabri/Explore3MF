#include <mainApp.h>

#include <camera.h>
#include <import3MF.h>
#include <meshLine.h>
#include <meshModel.h>
#include <shaderLoaderGL.h>
#include <texture2D.h>

#include <nfd.h>

using namespace E3D;

namespace
{
    const glm::vec4 kBackgroundColor(0.1f, 0.1f, 0.1f, 1.0f);

    const float kWorldAxisLenght(0.5f);
}

MainApp::MainApp()
{
}

MainApp::~MainApp()
{
}

void 
MainApp::guiSetup()
{
    // window styling
    ImGui::StyleColorsDark();

    ImGuiStyle * style = &ImGui::GetStyle();
    style->WindowRounding = 0.0f;
    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.04f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
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
                nfdchar_t * fileName = NULL;
                nfdresult_t result = NFD_OpenDialog("3mf, 3MF", NULL, &fileName);

                if ( result == NFD_OKAY )
                {
                    std::string path3MfFile(fileName);
                    std::wstring path3MfFileW(path3MfFile.begin(), path3MfFile.end());
                    m_model3MF = std::make_unique<Import3MF>(path3MfFileW);
                }
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    // debug window
    if (m_model3MF)
    {
        ImGui::Begin("Mesh Debug", NULL, ImGuiWindowFlags_AlwaysAutoResize);

        if (m_model3MF->packageIcon())
        {
            uintptr_t pID = static_cast<uintptr_t>(m_model3MF->packageIcon()->id());
            ImTextureID * textureID = reinterpret_cast<ImTextureID*>(pID);

            ImGui::Image(textureID, ImVec2(200, 200));
        }

        for (auto mesh : m_model3MF->meshModels())
        {
            ImGui::Text("Vertex Count: %d", mesh->numVertices());
            ImGui::Text("Triangle Count: %d", mesh->numTriangles());
            ImGui::Separator();
        }

        ImGui::End();
    }
}

void
MainApp::init()
{
    m_camera = std::make_shared<Camera>( glm::vec3(0.0f, 0.0f, 16.0f),
                                         glm::vec3(0.0f, 0.0f, 0.0f), 
                                         width(), height());

    std::string path(RESOURCEDIR_PATH);
    m_vertexShader = std::make_shared<ShaderLoaderGL>(path + "Shaders/vertexColorShader.vert",
                                                      path + "Shaders/vertexColorShader.frag");

    m_facetedShader = std::make_shared<ShaderLoaderGL>(path + "Shaders/facetedShader.vert",
                                                       path + "Shaders/facetedShader.frag");
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

    worldAxisDraw(m_camera, m_vertexShader);

    if (m_model3MF)
    {
        for (auto mesh : m_model3MF->meshModels())
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
MainApp::worldAxisDraw(std::shared_ptr<Camera>& cam, std::shared_ptr<ShaderLoaderGL>& shader)
{
    std::array<Vertex, 2> vertices;

    // X- Red
    {
        vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f) * kWorldAxisLenght;
        vertices[1].position = glm::vec3(1.f, 0.0f, 0.0f) * kWorldAxisLenght;

        vertices[0].setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
        vertices[1].setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

        auto meshLine = std::make_unique<MeshLine>(vertices);
        meshLine->draw(cam, shader);
    }

    // Y- Green
    {
        vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f) * kWorldAxisLenght;
        vertices[1].position = glm::vec3(0.0f, 1.f, 0.0f) * kWorldAxisLenght;

        vertices[0].setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
        vertices[1].setColor(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));

        auto meshLine = std::make_unique<MeshLine>(vertices);
        meshLine->draw(cam, shader);
    }

    // Z-Blue
    {
        vertices[0].position = glm::vec3(0.0f, 0.0f, 0.0f) * kWorldAxisLenght;
        vertices[1].position = glm::vec3(0.0f, 0.0f, 1.f) * kWorldAxisLenght;

        vertices[0].setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
        vertices[1].setColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

        auto meshLine = std::make_unique<MeshLine>(vertices);
        meshLine->draw(cam, shader);
    }
}
