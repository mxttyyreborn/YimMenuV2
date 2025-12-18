#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

#include <algorithm> // std::clamp

namespace YimMenu::Features
{
	class AlwaysOnGround : public LoopedCommand
	{
		using LoopedCommand::LoopedCommand;

		virtual void OnTick() override
		{
			auto veh = Self::GetVehicle();
			if (!veh)
				return;

			const int handle = veh.GetHandle();
			if (handle == 0)
				return;

			const float speed = ENTITY::GET_ENTITY_SPEED(handle);

			// Scale downward force with speed so it doesn't feel crazy at low speed.
			const float downforce = std::clamp(speed * 12.0f, 50.0f, 300.0f);

			ENTITY::APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(
				handle,
				1,          // forceType
				0.0f,       // x
				0.0f,       // y
				-downforce, // z (down)
				false,
				true,
				true,
				false);
		}
	};

	static AlwaysOnGround _AlwaysOnGround{
		"alwaysonground",
		"Always On Ground",
		"Applies downward force to keep vehicle wheels on the ground"
	};
}
