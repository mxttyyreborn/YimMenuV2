#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

#include <algorithm>

namespace YimMenu::Features
{
	class TractionControl : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		float m_LastTorqueMult = 1.0f;

		virtual void OnTick() override
		{
			auto veh = Self::GetVehicle();
			if (!veh)
				return;

			auto handle = veh.GetHandle();

			// Vehicle speed (m/s)
			float speed = ENTITY::GET_ENTITY_SPEED(handle);

			// Engine RPM (0.0 - 1.0)
			float rpm = VEHICLE::GET_VEHICLE_CURRENT_RPM(handle);

			// Player accelerating?
			bool accelerating = PAD::IS_CONTROL_PRESSED(0, 71); // W / RT

			float torqueMult = 1.0f;

			// Detect wheel spin:
			// High RPM + low speed + accelerating
			if (accelerating && rpm > 0.65f && speed < 15.0f)
			{
				// Reduce torque to prevent spin
				torqueMult = std::clamp(1.0f - (rpm - 0.6f), 0.55f, 1.0f);
			}

			// Apply torque only if changed (prevents jitter)
			if (torqueMult != m_LastTorqueMult)
			{
				VEHICLE::SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(handle, torqueMult);
				m_LastTorqueMult = torqueMult;
			}

			// Small traction boost (safe & subtle)
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(handle, false);
		}

		virtual void OnDisable() override
		{
			// Restore default behavior
			if (auto veh = Self::GetVehicle())
			{
				auto handle = veh.GetHandle();
				VEHICLE::SET_VEHICLE_ENGINE_TORQUE_MULTIPLIER(handle, 1.0f);
			}

			m_LastTorqueMult = 1.0f;
		}
	};

	static TractionControl _TractionControl{
		"tractioncontrol",
		"Traction Control",
		"Prevents wheel spin and greatly improves grip"
	};
}
