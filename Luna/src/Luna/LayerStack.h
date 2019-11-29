#pragma once

#include "Luna/Core.h"
#include "Layer.h"
#include <vector>

namespace Luna 
{	
	/*
	 * @Brief: overlays are alwyas pushed on top of layers
	 */ 
	class LUNA_API LayerStack
	{
		static constexpr unsigned int initialLayersCapacity{10};
        using Layers = std::vector<std::unique_ptr<Layer>>;

		LayerStack() 
		{
			m_Layers.reserve(initialLayersCapacity); 
			m_LayerInsert = m_Layers.begin();
		}

	public:
		/*
		* @Brief Movable only class enabling layers poping/disabling/enabling
		*/
		class LUNA_API LayerProxy 
		{
		public:
			LayerProxy(const LayerProxy&) = delete;
			LayerProxy(LayerProxy&& other) noexcept : m_Layer{ other.m_Layer }, isValid{ other.isValid }
			{
				other.isValid = false;
				other.m_Layer = nullptr;
			}
			LayerProxy& operator=(const LayerProxy&) = delete;
			LayerProxy& operator=(LayerProxy&& other) noexcept
			{
				m_Layer = other.m_Layer;
				isValid = other.isValid;
				other.isValid = false;
				other.m_Layer = nullptr;

				return *this;
			}
			~LayerProxy() = default;

		private:
			friend class LayerStack;
			LayerProxy(Layers::iterator layer) : m_Layer{ layer->get() } {}
			const Layer* m_Layer;
			bool isValid{ true };
		};

		LayerStack(const LayerStack &) = delete;
		LayerStack &operator=(const LayerStack &) = delete;
		LayerStack &operator=(LayerStack &&) = default;
		LayerStack(LayerStack &&) = default;
		~LayerStack() = default;

		static LayerStack& instance() 
		{
			static LayerStack stack;
			return stack;
		}

		LayerProxy pushLayer(std::unique_ptr<Layer> layer);
		LayerProxy pushOverlay(std::unique_ptr<Layer> layer);
		void pop(LayerProxy&& layerProxy);
		auto begin() { return m_Layers.begin(); }
		auto end() { return m_Layers.end(); }

	private:
		Layers m_Layers{};
		Layers::iterator m_LayerInsert{};
	};

}// namespace Luna