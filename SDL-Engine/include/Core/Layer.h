#pragma once
#include <concepts>
#include "Application/Application.h"

namespace Core
{
	class Layer
	{
	public:
		Layer() = default;
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void ProcessInput(){}

		template<std::derived_from<Layer> T, typename ... LayerArguments>
		void TransitionToLayer(LayerArguments&& ... layerArguments)
		{
			std::unique_ptr<Layer> newLayer = std::make_unique<T>(std::forward<LayerArguments>(layerArguments) ...);

			for (auto& layer : Application::GetInstance()->GetLayerList())
			{
				if (layer.get() == this)
				{
					layer->OnDetach();
					layer = std::move(newLayer);
					layer->OnAttach();
				}
			}
		}

		virtual void Update() {}
		virtual void Render() {}
	};
}
