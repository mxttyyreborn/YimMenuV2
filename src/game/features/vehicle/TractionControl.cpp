#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features
{
	class TractionControl final : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		int m_LastVehicle = 0;

		void Reset()
		{
			if (!m_LastVehicle)
				return;

			VEHICLE::SET_VEHICLE_FRICTION_OVERRIDE(m_LastVehicle, 1.0f);
			VEHICLE::_SET_OVERRIDE_TRACTION_LOSS_MULTIPLIER(m_LastVehicle, 1.0f);
			m_LastVehicle = 0;
		}

		void OnDisable() override
		{
			Reset();
		}

		void OnTick() override
		{
			auto ped = Self::GetPed();
			if (!ped)
			{
				Reset();
				return;
			}

			const int pedHandle = ped.GetHandle();

			if (!PED::IS_PED_IN_ANY_VEHICLE(pedHandle, false))
			{
				Reset();
				return;
			}

			const int vehicle = PED::GET_VEHICLE_PED_IS_IN(pedHandle, false);

			// Must be driver
			if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1, false) != pedHandle)
			{
				if (m_LastVehicle == vehicle)
					Reset();
				return;
			}

			m_LastVehicle = vehicle;

			// Aggressive grip enforcement (every tick)
			VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, false);
			VEHICLE::SET_VEHICLE_FRICTION_OVERRIDE(vehicle, 8.0f);
			VEHICLE::_SET_OVERRIDE_TRACTION_LOSS_MULTIPLIER(vehicle, 0.0f);
			VEHICLE::SET_VEHICLE_BURNOUT(vehicle, false);
		}
	};

	static TractionControl _TractionControl{
		"tractioncontrol",
		"Traction Control",
		"Eliminates wheelspin and makes vehicles extremely grippy"
	};
}
