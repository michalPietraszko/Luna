#pragma once
#include <string>

namespace Luna 
{
class LUNA_API Layer
{
public:
	Layer(std::string name) : m_DebugName{name} {}
	virtual ~Layer() = default;

	virtual void onAttach() {}
	virtual void onDetach() {}
	virtual void onUpdate() {}
	virtual void onEvent() {}

	const std::string& getName() const { return m_DebugName; }

protected:
	std::string m_DebugName;
};
} // namespace Luna