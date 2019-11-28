#include "lnpch.h"
#include "LayerStack.hpp"

namespace Luna
{

LayerStack::LayerProxy LayerStack::pushLayer(UniqueLayerPtr layer)
{
    m_LayerInsert = m_Layers.insert(m_LayerInsert, std::move(layer));
	return  { m_LayerInsert };
}

LayerStack::LayerProxy LayerStack::pushOverlay(UniqueLayerPtr overlay)
{
    m_Layers.push_back(std::move(overlay));
	return { std::prev(m_Layers.end()) };
}

void LayerStack::pop(LayerProxy&& layerProxy)
{
    if(not layerProxy.isValid) return;

    if(m_Layers.end() == m_Layers.erase(layerProxy.m_Layer))
    {
        LN_CORE_ERROR("Poping layer that is not in stack!");
    }
}

} // namespace Hazel