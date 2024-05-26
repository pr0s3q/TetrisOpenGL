#include "ImGuiWrapper.h"

#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include "JsonWrapper.h"

//---------------------------------------------------------------

ImGuiWrapper::ImGuiWrapper(const ImGuiIO& io, const int width, const int height)
    : m_viewMode(Mode::EMenuView)
    , m_width(width)
    , m_height(height)
    , m_score(0)
    , m_scoreCombo(1)
    , m_playGameClicked(false)
    , m_exitClicked(false)
{
    m_jsonWrapper = std::make_shared<JsonWrapper>();
    m_jsonWrapper->LoadFromFile();
    m_font = io.Fonts->AddFontFromFileTTF("OpenSans-Light.ttf", 50.0f);
    io.Fonts->Build();
    IM_ASSERT(m_font != NULL);
}

//---------------------------------------------------------------

void ImGuiWrapper::AddScore()
{
    m_score += m_scoreCombo * 100;
    ++m_scoreCombo;
}

//---------------------------------------------------------------

bool ImGuiWrapper::Exit() const
{
    return m_exitClicked;
}

//---------------------------------------------------------------

void ImGuiWrapper::Frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    switch (m_viewMode)
    {
        case Mode::EMenuView:
        {
            MenuGuiView();
            break;
        }
        case Mode::EGameScoreView:
        {
            GameScoreGuiView();
            break;
        }
        case Mode::EScoreboardView:
        {
            ScoreboardView();
            break;
        }
    }

    ImGui::PopFont();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

//---------------------------------------------------------------

void ImGuiWrapper::MenuGuiView()
{
    ImGui::SetNextWindowSize({ static_cast<float>(m_width), static_cast<float>(m_height) });
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::Begin(
        "TetrisOpenGL",
        nullptr,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove);
    ImGui::PushFont(m_font);

    ImVec2 label_size = ImGui::CalcTextSize(m_playText, nullptr, true);
    ImGui::SetCursorPos({ (static_cast<float>(m_width) - label_size.x) / 2, 100 });
    if (ImGui::Button(m_playText))
    {
        m_playGameClicked = true;
        m_viewMode = Mode::EGameScoreView;
    }

    label_size = ImGui::CalcTextSize(m_scoreboardText, nullptr, true);
    ImGui::SetCursorPos({ (static_cast<float>(m_width) - label_size.x) / 2, 200 });
    if (ImGui::Button(m_scoreboardText))
        m_viewMode = Mode::EScoreboardView;

    label_size = ImGui::CalcTextSize(m_exitText, nullptr, true);
    ImGui::SetCursorPos({ (static_cast<float>(m_width) - label_size.x) / 2, 300 });
    if (ImGui::Button(m_exitText))
        m_exitClicked = true;
}

//---------------------------------------------------------------

void ImGuiWrapper::ScoreboardView() const
{
    ImGui::SetNextWindowSize({ static_cast<float>(m_width), static_cast<float>(m_height) });
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::Begin(
        "TetrisOpenGL",
        nullptr,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove);
    ImGui::PushFont(m_font);

    const std::vector<Score>* scores = m_jsonWrapper->GetScores();
    for (size_t i = 0; i < scores->size() && i < 10; ++i)
    {
        std::string text = scores->at(i).playerName + " " + std::to_string(scores->at(i).score);
        const ImVec2 label_size = ImGui::CalcTextSize(text.c_str(), nullptr, true);
        ImGui::SetCursorPos({ (static_cast<float>(m_width) - label_size.x) / 2, static_cast<float>(50 * i + 100) });
        ImGui::Text("%s", text.c_str());
    }
}

//---------------------------------------------------------------

void ImGuiWrapper::GameScoreGuiView() const
{
    ImGui::SetNextWindowSize({ static_cast<float>(m_width) / 3, static_cast<float>(m_height) });
    ImGui::SetNextWindowPos({ 0, 0 });
    ImGui::Begin(
        "TetrisOpenGL",
        nullptr,
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove);
    ImGui::PushFont(m_font);

    ImGui::SetCursorPos({ 10, 10 });
    ImGui::Text("%s", m_scoreText); // %s - string data type (format specifier in C )

    const ImVec2 label_size = ImGui::CalcTextSize(m_scoreText, nullptr, true);
    ImGui::SetCursorPos({ 10 + label_size.x, 10 });
    ImGui::Text("%i", m_score); // %i - integer data type (format specifier in C )

    if (ImGui::Button(m_saveScore))
    {
        m_jsonWrapper->SaveToFile("Cris", m_score); // TODO: Create UI for username input (currently name is hardcoded)
                                                    // TODO: Reset game upon saving score
    }
}

//---------------------------------------------------------------

bool ImGuiWrapper::PlayGame() const
{
    return m_playGameClicked;
}

//---------------------------------------------------------------

void ImGuiWrapper::ResetCombo()
{
    m_scoreCombo = 1;
}

//---------------------------------------------------------------

void ImGuiWrapper::ShowMenu()
{
    m_playGameClicked = false;
    m_viewMode = Mode::EMenuView;
}

//---------------------------------------------------------------
