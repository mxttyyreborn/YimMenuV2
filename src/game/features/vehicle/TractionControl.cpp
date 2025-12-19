#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class TractionControl : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		int m_LastVehicleHandle = 0;

		void ResetIfNeeded()
		{
			if (m_LastVehicleHandle == 0)
				return;

			// Reset to sane defaults
			VEHICLE::SET_VEHICLE_FRICTION_OVERRIDE(m_LastVehicleHandle, 1.0f);
			VEHICLE::_SET_OVERRIDE_TRACTION_LOSS_MULTIPLIER(m_LastVehicleHandle, 1.0f);
			VEHICLE::SET_VEHICLE_BURNOUT(m_LastVehicleHandle, false);

			m_LastVehicleHandle = 0;
		}

		void OnDisable() override
		{
			ResetIfNeeded();
		}

		void OnTick() override
		{
			auto veh = Self::GetVehicle();
			if (!veh)
			{
				ResetIfNeeded();
				return;
			}

			const int vehHandle = veh.GetHandle();

			// Only apply if we're the driver
			const int myPedHandle = Self::GetPed().GetHandle();
			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehHandle, -1, false) != myPedHandle)
			{
				// If we were previously modifying a vehicle and we are no longer driving, reset it.
				if (m_LastVehicleHandle == vehHandle)
					ResetIfNeeded();
				return;
			}

			m_LastVehicleHandle = vehHandle;

			// "Glued to the road" settings:
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehHandle, false);                 // ensure grip isn't reduced
			VEHICLE::SET_VEHICLE_BURNOUT(vehHandle, false);                     // no burnouts
			VEHICLE::SET_VEHICLE_FRICTION_OVERRIDE(vehHandle, 10.0f);           // very high friction
			VEHICLE::_SET_OVERRIDE_TRACTION_LOSS_MULTIPLIER(vehHandle, 0.0f);   // minimize traction loss
		}
	};

	static TractionControl _TractionControl{
		"tractioncontrol",
		"Traction Control",
		"Makes driven vehicles extremely grippy (no wheelspin / very high traction)"
	};
}
