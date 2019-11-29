#pragma once

#include "Luna/Core.h"
#include "Luna/Events/Event.h"

namespace Luna 
{
    class LUNA_API Layer
	{
 	public:
 		Layer(const std::string& name) : m_DebugName {name} {} // use short names for SSO
 		virtual ~Layer() {}

  		virtual void onAttach() {}
 		virtual void onDetach() {}
 		virtual void onUpdate() {}
 		virtual void onEvent(Event& event) {}
		virtual void kupa(const std::string&) = 0;

  		inline const std::string& getName() const { return m_DebugName; }
 	protected:
 		std::string m_DebugName{"Default Layer Name"};
 	};
}// namespace Luna
