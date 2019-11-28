#include "lnpch.h"
#include "LayerStack.h"

namespace Luna
{

LayerStack::~LayerStack()
{
    for (auto layer : m_Layers)
        delete layer;
}

LayerProxy LayerStack::PushLayer(UniqueLayerPtr layer)
{
    m_LayerInsert = m_Layers.insert(m_LayerInsert, std::move(layer));
    return std::prev(m_Layers.cend());
}

LayerProxy LayerStack::PushOverlay(UniqueLayerPtr overlay)
{
    m_Layers.push_back(overlay);
}

void pop(LayerProxy&& layerProxy)
{
    if(not layerProxy.isValid) return;

    if(m_LayerStack.end() == m_LayerStack.erase(layerProxy.layer))
    {
        LN_CORE_ERROR("Poping layer that is not in stack!");
    }
}

} // namespace Hazel