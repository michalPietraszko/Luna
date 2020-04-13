#pragma once

#include "Luna/Core.h"
#include "Layer.h"
#include <list>

namespace Luna
{
/*
 * @Brief: overlays are alwyas pushed on top of layers
 */
class LUNA_API LayerStack
{
    using Layers = std::list<std::unique_ptr<Layer>>;
    // hard to tell how much memory allocation for each node will take on performance without comparing with other
    // data structures, probably some sort of list with preallocated pool would be the best since there's probably gonna
    // be a similar num of layer + overlays throught the life of the application, however overlays/layers can be very
    // quickly discarded/created again due to the nature of hud/menus/levels
    // having a preallocated pool of available nodes solves allocation and deallocation problem also allows to
    // use naked iterators to pop layers

protected:
    LayerStack() : m_LayerInsert{m_Layers.end()} {}

public:
    static LayerStack& instanceImpl()
    {
        static LayerStack stack;
        return stack;
    }

    using const_iterator = Layers::iterator;

    ~LayerStack() = default;
    LayerStack(const LayerStack&) = delete;
    LayerStack& operator=(const LayerStack&) = delete;
    LayerStack& operator=(LayerStack&&) = default;
    LayerStack(LayerStack&&) = default;

    const_iterator pushLayer(std::unique_ptr<Layer> layer);
    const_iterator pushOverlay(std::unique_ptr<Layer> overlay);

    void popLayer(const_iterator layer);
    void popOverlay(const_iterator overlay);

    auto begin() { return m_Layers.begin(); }
    auto end() { return m_Layers.end(); }
    static LayerStack& instance() { return cachedRef; }

private:
    void decLayerInserter()
    {
        m_Layers.size() == 1 ? m_LayerInsert = m_Layers.end() : m_LayerInsert = std::prev(m_LayerInsert);
    }

private:
    static LayerStack& cachedRef;
    Layers m_Layers{};
    const_iterator m_LayerInsert{};
};

} // namespace Luna