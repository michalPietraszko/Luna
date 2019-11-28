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
        using UniqueLayerPtr = std::unique_ptr<Layer>;
        using Layers = std::vector<UniqueLayerPtr>;

	public:
		/*
		* @Brief Movable only class enabling layers poping/disabling/enabling
		*/
		class LayerProxy
		{
			LayerProxy() = delete;
			LayerProxy(const LayerProxy&) = delete;
			LayerProxy(LayerProxy&& other) : m_Layer{std::move(other.m_Layer)}, isValid {other.isValid};
			{
				other.isValid = false; 
			}
			LayerProxy& operator=(const LayerProxy&) = delete;
			LayerProxy& operator=(LayerProxy&&) 
			{
				m_Layer = std::move(other.m_Layer)}; 
				isValid = other.isValid;
				other.isValid = false; 
			}
			~LayerProxy() = default;

		private:
			friend class LayerStack;
			LayerProxy(Layers::const_iterator&& layer) : m_Layer{std::move(layer)} {}
			const Layers::const_iterator m_Layer;
			isValid{true};
		};

	private:
		LayerStack() { m_Layers.reserve(initialLayersCapacity);}

	public:
		~LayerStack();
		static LayerStack& instance() 
		{
			static LayerStack stack;
			return stack;
		}

		LayerProxy pushLayer(UniqueLayerPtr layer);
		LayerProxy pushOverlay(UniqueLayerPtr layer);
		void pop(LayerProxy&& layerProxy);
		
		// future support
		// void enableLayer(const LayerProxy& layerProxy)
		// void disableLayer(const LayerProxy& layerProxy);

		auto begin() { return m_Layers.begin(); }
		auto end() { return m_Layers.end(); }

	private:
		Layers m_Layers{};
		Layers::const_iterator m_LayerInsert{m_Layers.cbegin()};
	};

}// namespace Luna