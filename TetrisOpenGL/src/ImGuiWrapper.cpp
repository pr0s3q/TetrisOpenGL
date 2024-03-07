#include "ImGuiWrapper.h"

#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

//---------------------------------------------------------------

ImGuiWrapper::ImGuiWrapper(const ImGuiIO& io, const int width, const int height)
    : m_clear_color(0.45f, 0.55f, 0.60f, 1.00f),
      m_viewMode(Mode::EMenuView),
      m_width(width),
      m_height(height),
      m_score(0),
      m_scoreCombo(1),
      m_playGameClicked(false),
      m_exitClicked(false)
{
    m_jsonWrapper = std::make_shared<JsonWrapper>();
    m_jsonWrapper->LoadFromFile();
    m_font = std::shared_ptr<ImFont>(io.Fonts->AddFontFromFileTTF("OpenSans-Light.ttf", 50.0f));
    io.Fonts->Build();
    IM_ASSERT(m_font != NULL);

    m_exitText = std::shared_ptr<const char>("       Exit       ");
    m_playText = std::shared_ptr<const char>("       Play       ");
    m_scoreboardText = std::shared_ptr<const char>(" Scoreboard ");
    m_scoreText = std::shared_ptr<const char>("Score: ");
    m_saveScore = std::shared_ptr<const char>("Save Score");
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
    ImGui::SetNextWindowSize({static_cast<float>(m_width), static_cast<float>(m_height)});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("TetrisOpenGL", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove);
    ImGui::PushFont(m_font.get());

    ImVec2 label_size = ImGui::CalcTextSize(m_playText.get(), nullptr, true);
    ImGui::SetCursorPos({(static_cast<float>(m_width) - label_size.x) / 2, 100});
    if (ImGui::Button(m_playText.get()))
    {
        m_playGameClicked = true;
        m_viewMode = Mode::EGameScoreView;
    }

    label_size = ImGui::CalcTextSize(m_scoreboardText.get(), nullptr, true);
    ImGui::SetCursorPos({(static_cast<float>(m_width) - label_size.x) / 2, 200});
    if (ImGui::Button(m_scoreboardText.get()))
        m_viewMode = Mode::EScoreboardView;

    label_size = ImGui::CalcTextSize(m_exitText.get(), nullptr, true);
    ImGui::SetCursorPos({(static_cast<float>(m_width) - label_size.x) / 2, 300});
    if (ImGui::Button(m_exitText.get()))
        m_exitClicked = true;
}

//---------------------------------------------------------------

void ImGuiWrapper::ScoreboardView() const
{
    ImGui::SetNextWindowSize({static_cast<float>(m_width), static_cast<float>(m_height)});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("TetrisOpenGL", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove);
    ImGui::PushFont(m_font.get());

    const std::vector<Score>* scores = m_jsonWrapper->GetScores();
    for (size_t i = 0; i < scores->capacity() && i < 10; ++i)
    {
        std::string text = scores->at(i).playerName + " " + std::to_string(scores->at(i).score);
        const ImVec2 label_size = ImGui::CalcTextSize(text.c_str(), nullptr, true);
        ImGui::SetCursorPos({(static_cast<float>(m_width) - label_size.x) / 2, static_cast<float>(50 * i + 100)});
        ImGui::Text("%s", text.c_str());
    }
}

//---------------------------------------------------------------

void ImGuiWrapper::GameScoreGuiView() const
{
    ImGui::SetNextWindowSize({static_cast<float>(m_width) / 3, static_cast<float>(m_height)});
    ImGui::SetNextWindowPos({0, 0});
    ImGui::Begin("TetrisOpenGL", nullptr,
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                 ImGuiWindowFlags_NoMove);
    ImGui::PushFont(m_font.get());

    ImGui::SetCursorPos({10, 10});
    ImGui::Text("%s", m_scoreText.get()); // %s - string data type (format specifier in C )

    const ImVec2 label_size = ImGui::CalcTextSize(m_scoreText.get(), nullptr, true);
    ImGui::SetCursorPos({10 + label_size.x, 10});
    ImGui::Text("%i", m_score); // %i - integer data type (format specifier in C )

    if (ImGui::Button(m_saveScore.get()))
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
