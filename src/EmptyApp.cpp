#include "EmptyApp.h"
#include "Assets/GameObjects/TestGameObject.h"
#include "Scene/GameObject.h"

void EmptyApp::Begin()
{
    InitializeObjects();
    StartScene();
}

void EmptyApp::InitializeObjects()
{
    m_MainScene = new Core::GameScene(100);
    m_MainScene->AddGameObject<Assets::GameObjects::TestGameObject>();
}

void EmptyApp::StartScene()
{
    m_MainScene->Start();
}

void EmptyApp::Update(const float deltaTime)
{
    m_MainScene->Update(deltaTime);
}

void EmptyApp::End()
{

}