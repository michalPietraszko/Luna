#include "lnpch.h"
#include "LayerStack.h"

namespace Luna
{
LayerStack& LayerStack::cachedRef = LayerStack::instanceImpl();

LayerStack::const_iterator LayerStack::pushLayer(std::unique_ptr<Layer> layer)
{
    layer->onAttach();
    auto insertPos = m_Layers.insert(m_LayerInsert, std::move(layer));

    m_LayerInsert = std::next(insertPos);
    return insertPos;
}

LayerStack::const_iterator LayerStack::pushOverlay(std::unique_ptr<Layer> overlay)
{
    overlay->onAttach();
    return m_Layers.insert(m_Layers.end(), std::move(overlay));
}

void LayerStack::popLayer(LayerStack::const_iterator layer)
{
    (*layer)->onDetach();
    decLayerInserter();
    m_Layers.erase(layer);
}

void LayerStack::popOverlay(LayerStack::const_iterator overlay)
{
    (*overlay)->onDetach();
    m_Layers.erase(overlay);
}
} // namespace Luna
