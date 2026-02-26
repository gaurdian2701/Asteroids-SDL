#include "GameActions/PlayerRespawnAction.h"

#include "Assets/Components/Collider2D.h"
#include "Assets/Components/Renderer2D.h"
#include "Assets/Components/Transform.h"
#include "Scene/GameObject.h"

void Asteroids::GameActions::PlayerRespawnAction::OnBegin(bool isFirstTime)
{
    if (isFirstTime)
    {
        if (m_player != nullptr)
        {
            m_player->GetComponent<Assets::Components::Transform>()->LocalPosition = glm::vec2(0.0f);
            m_player->RemoveComponent<Assets::Components::Collider2D>();
        }
    }
}

void Asteroids::GameActions::PlayerRespawnAction::OnUpdate(float deltaTime)
{
    if (m_toggleCounter == m_numberOfTogglesTillEnd)
    {
        m_actionEnded = true;
        return;
    }

    if (m_player != nullptr)
    {
        if (m_rendererToggleTimer > m_timeTillRendererToggle)
        {
            m_toggleCounter++;

            if (m_playerHasRenderer)
            {
                m_player->RemoveComponent<Assets::Components::Renderer2D>();
                m_playerHasRenderer = false;
            }
            else
            {
                m_player->AddComponent<Assets::Components::Renderer2D>();
                auto renderer = m_player->GetComponent<Assets::Components::Renderer2D>();
                renderer->RenderTexture = m_renderTexture;
                m_playerHasRenderer = true;
            }
            m_rendererToggleTimer = 0.0f;
        }
        m_rendererToggleTimer += deltaTime;
    }
}

void Asteroids::GameActions::PlayerRespawnAction::OnEnd()
{
    if (m_player != nullptr)
    {
        if (!m_playerHasRenderer)
        {
            m_player->AddComponent<Assets::Components::Renderer2D>();
            auto renderer = m_player->GetComponent<Assets::Components::Renderer2D>();
            renderer->RenderTexture = m_renderTexture;
            m_playerHasRenderer = true;
        }

        m_player->AddComponent<Assets::Components::Collider2D>();
        auto collider = m_player->GetComponent<Assets::Components::Collider2D>();

        if (collider != nullptr)
        {
            collider->HalfSize = m_player->GetComponent<Assets::Components::Transform>()->LocalScale * 0.5f;
        }
    }
}




