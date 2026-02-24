#pragma once
#include "Actions/IAction.h"
#include "SDL3/SDL_render.h"

namespace Scene
{
    class GameObject;
}

namespace Asteroids::GameActions
{
    class PlayerRespawnAction : public Actions::IAction
    {
    public:
        explicit PlayerRespawnAction(Scene::GameObject* somePlayer,
            SDL_Texture* someRenderTexture) : m_player(somePlayer), m_renderTexture(someRenderTexture) {}

        ~PlayerRespawnAction() override
        {
            m_player = nullptr;
        }

        void OnBegin(bool isFirstTime) override;
        void OnUpdate(float deltaTime) override;
        void OnEnd() override;
        bool IsDone() override{ return m_actionEnded; }

    private:
        float m_timeTillRendererToggle = 0.5f;
        float m_rendererToggleTimer = 0.0f;
        uint8_t m_numberOfTogglesTillEnd = 3;
        uint8_t m_toggleCounter = 0;
        bool m_actionEnded = false;
        bool m_playerHasRenderer = true;
        Scene::GameObject* m_player = nullptr;
        SDL_Texture* m_renderTexture = nullptr;
    };

}
