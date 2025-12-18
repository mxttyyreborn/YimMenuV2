#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class AlwaysOnGround : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		void OnTick() override
		{
			auto vehicle = Self::GetVehicle();
			if (!vehicle)
				return;

			// If vehicle is already touching ground, do nothing
			if (vehicle.IsOnAllWheels())
				return;

			// Apply a small downward force ONLY when airborne
			// Keep this subtle or the car becomes undrivable
			vehicle.SetGravity(1.15f);
		}
	};

	// This is what makes it appear in the Vehicle menu
	static AlwaysOnGround _AlwaysOnGround{
		"alwaysonground",
		"Always On Ground",
		"Helps keep vehicle wheels planted without affecting handling"
	};
}
