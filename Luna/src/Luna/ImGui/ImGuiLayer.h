#pragma once

#include "Luna/Layer.h"

namespace Luna 
{

	class LUNA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach() override;
		void onDetach() override;
		void onUpdate() override;
		void onEvent(Event& event) override;

	private:
		float m_Time = 0.0f;
	};

}// namespace Luna