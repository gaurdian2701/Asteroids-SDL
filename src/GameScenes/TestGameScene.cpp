#include "GameScenes/TestGameScene.h"
#include "GameObjects/LoneParticleEmitter.h"
#include "GameObjects/SpaceShip.h"
#include "GameObjects/SimpleChild.h"
#include "Assets/Components/Transform.h"
#include "imgui.h"


void Asteroids::GameScenes::TestGameScene::InitializeGameObjects()
{
    m_spaceShip = AddGameObject<GameObjects::SpaceShip>();
    m_loneEmitter = AddGameObject<GameObjects::LoneParticleEmitter>();
    m_simpleChild = AddGameObject<GameObjects::SimpleChild>();

    GameScene::InitializeGameObjects();
}

void Asteroids::GameScenes::TestGameScene::Update(const float deltaTime)
{
#ifdef _DEBUG
    UpdateImGuiDebugs();
#endif
    GameScene::Update(deltaTime);
}

#ifdef _DEBUG
void Asteroids::GameScenes::TestGameScene::SetDebugNames()
{
    m_spaceShip->m_name = "Space Ship";
    m_loneEmitter->m_name = "Lone Emitter";
    m_simpleChild->m_name = "Simple Child";
}

void Asteroids::GameScenes::TestGameScene::UpdateImGuiDebugs()
{
    ImGui::Begin("Debug");
    ImGui::Text("FRAME RATE:");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)\n",
    1000.0f / ImGui::GetIO().Framerate,
    ImGui::GetIO().Framerate);

    ImGui::Text("CHANGEABLE DEBUGS: ");

    for (auto& gameObject: m_gameObjectsInScene)
    {
        auto& transform = gameObject->GetComponent<Assets::Components::Transform>();

        ImGui::PushID(gameObject->m_name.c_str());
        ImGui::Text(gameObject->m_name.c_str());
        ImGui::SliderFloat2("Local Position", &transform.LocalPosition.x, -1000.0f, 1000.0f);
        ImGui::SliderFloat2("Local Scale", &transform.LocalScale.x, -100.0f, 100.0f);
        ImGui::SliderFloat2("Local Rotation", &transform.LocalRotation, -1000.0f, 1000.0f);
        ImGui::Separator();
        ImGui::PopID();
    }
    ImGui::End();
}
#endif


