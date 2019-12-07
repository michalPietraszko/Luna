#include "lnpch.h"
#include "LayerStack.h"

namespace Luna
{
	LayerStack::LayerProxy LayerStack::pushLayer(std::unique_ptr<Layer> layer)
	{
		LN_CORE_ASSERT(m_LayerInsert < m_Layers.size() || m_LayerInsert == 0u);
		
		const auto insertPos = m_LayerInsert;
		m_Layers.insert(m_Layers.begin() + m_LayerInsert, std::move(layer));

		m_LayerInsert++;
		return { m_Layers.begin() + insertPos };
	}

	LayerStack::LayerProxy LayerStack::pushOverlay(std::unique_ptr<Layer> overlay)
	{
	    m_Layers.push_back(std::move(overlay));
		return { std::prev(m_Layers.end()) };
	}

	void LayerStack::pop(LayerProxy&& layerProxy)
	{
		if(not layerProxy.isValid) return;

		const auto result = 
		std::find_if(m_Layers.cbegin(), m_Layers.cend(), [proxy = std::move(layerProxy)](const std::unique_ptr<Layer>& layer){
			return proxy.m_Layer == layer.get();
			});

		if(result == m_Layers.cend())
		{
			LN_CORE_ERROR("Poping layer that is not in stack!");
			return;
		}

		m_Layers.erase(result);
	}
} // namespace Hazel