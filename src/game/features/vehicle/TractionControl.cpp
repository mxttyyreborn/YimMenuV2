#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class TractionControl : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		float m_OriginalTractionMax{};
		float m_OriginalTractionMin{};
		float m_OriginalLossMult{};
		bool  m_Stored = false;

		void OnTick() override
		{
			auto veh = Self::GetVehicle();
			if (!veh)
				return;

			// Cache original handling once
			if (!m_Stored)
			{
				m_OriginalTractionMax = veh.GetHandlingFloat("CHandlingData", "fTractionCurveMax");
				m_OriginalTractionMin = veh.GetHandlingFloat("CHandlingData", "fTractionCurveMin");
				m_OriginalLossMult   = veh.GetHandlingFloat("CHandlingData", "fLowSpeedTractionLossMult");
				m_Stored = true;
			}

			// High grip values (tuned to still feel drivable)
			veh.SetHandlingFloat("CHandlingData", "fTractionCurveMax", m_OriginalTractionMax * 1.6f);
			veh.SetHandlingFloat("CHandlingData", "fTractionCurveMin", m_OriginalTractionMin * 1.6f);
			veh.SetHandlingFloat("CHandlingData", "fLowSpeedTractionLossMult", 0.0f);
		}

		void OnDisable() override
		{
			auto veh = Self::GetVehicle();
			if (!veh || !m_Stored)
				return;

			// Restore original handling
			veh.SetHandlingFloat("CHandlingData", "fTractionCurveMax", m_OriginalTractionMax);
			veh.SetHandlingFloat("CHandlingData", "fTractionCurveMin", m_OriginalTractionMin);
			veh.SetHandlingFloat("CHandlingData", "fLowSpeedTractionLossMult", m_OriginalLossMult);

			m_Stored = false;
		}
	};

	static TractionControl _TractionControl{
		"tractioncontrol",
		"Traction Control",
		"Greatly increases grip and prevents wheel spin"
	};
}
