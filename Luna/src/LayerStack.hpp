#include <Layer.h>
#include <Luna/Core.h>
#include <vector>

namespace Luna
{
    class LUNA_API LayerStack
    {
        constexpr static unsigned int initialLayerStackSize{5};        
    public:
        using Layers = std::vector<Layer*>;

        static LayerStack& create 
        {
            static LayerStack stack;
            return stack;
        }

        ~LayerStack() 
        {
            for(const auto layer : mLayerStack)
            {
                delete layer;
            }
        }

        void pushLayer(Layer* layer)
        {   
            ASSERT(topLayerIndex < m_LayerStack.size() || topLayerIndex == 0u);
            m_LayerStack.insert(m_LayerStack.cbein() + topLayerIndex, layer);

            topLayerIndex++;
        }

        void pushOverlay(Layer* layer)
        {
            m_LayerStack.pushBack(layer);
        }

        void popLayer(const Layer* layer)
        {
            auto result = std::find(begin(), end(), layer);
            if(result == m_LayerStack.end())
            {
                LN_CORE_ERROR("Layer to pop not found in stack!");
            }
            m_LayerStack.erase(result);
        }

        void popOverlay(const Layer* overlay)
        {
            auto result = std::find(begin(), end(), overlay);
            if(result == m_LayerStack.end())
            {
                LN_CORE_ERROR("Overlay to pop not found in stack!");
            }
            m_LayerStack.erase(result);
            topLayerIndex--;
        }

        Layers::iterator begin() { return m_LayerStack.begin(); }
        Layers::iterator end() { return m_LayerStack.end(); }
        Layers::iterator cbegin() const { return m_LayerStack.cbegin(); }
        Layers::iterator cend() const { return m_LayerStack.cend(); }
        Layers::iterator rbegin() { return m_LayerStack.rbegin(); }
        Layers::iterator rbegin() { return m_LayerStack.rend(); }

    private:
        LayerStack() { m_LayerStack.reserve(initialLayerStackSize); };
        void propagateEventDownLayerStack(Event& event);

    private:
        Layers m_LayerStack{};
        unsigned int topLayerIndex{0u};
    };
} // namespace Luna