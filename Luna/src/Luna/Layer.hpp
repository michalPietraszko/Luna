#pragma once

#include "Luna/Core.h"
#include "Luna/Events/Event.h"

namespace Luna 
{
    class LUNA_API Layer
	{
 	public:
 		Layer(std::string name) : m_DebugName {std::move(name)} {} // use short names for SSO
 		virtual ~Layer() {}

  		virtual void OnAttach() {}
 		virtual void OnDetach() {}
 		virtual void OnUpdate() {}
 		virtual void OnEvent(Event& event) {}

  		inline const std::string& GetName() const { return m_DebugName; }
 	protected:
 		std::string m_DebugName{"Default Layer Name"};
 	};
}// namespace Luna
