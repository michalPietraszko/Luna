#pragma once

#include "Luna/Core.h"
#include "Layer.hpp"
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
		public:
			LayerProxy() = delete;
			LayerProxy(const LayerProxy&) = delete;
			LayerProxy(LayerProxy&& other) : m_Layer{other.m_Layer}, isValid {other.isValid}
			{
				other.isValid = false; 
			}
			LayerProxy& operator=(const LayerProxy&) = delete;
			LayerProxy& operator=(LayerProxy&& other) 
			{
				m_Layer = other.m_Layer; 
				isValid = other.isValid;
				other.isValid = false; 
			}
			~LayerProxy() = default;

		private:
			friend class LayerStack;
			LayerProxy(Layers::iterator layer) : m_Layer{layer} {}
			Layers::iterator m_Layer;
			bool isValid{true};
		};

	private:
		LayerStack() { m_Layers.reserve(initialLayersCapacity);}

	public:
		~LayerStack() = default;
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
		Layers::iterator m_LayerInsert{m_Layers.begin()};
	};

}// namespace Luna