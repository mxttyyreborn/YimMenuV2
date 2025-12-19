#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

#include <algorithm>

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

			auto handle = veh.GetHandle();

			const float speed = ENTITY::GET_ENTITY_SPEED(handle);
			const float downforce = std::clamp(speed * 0.2f, 1.7f, 2.5f);

			ENTITY::APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(
				handle,
				1,
				0.0f,
				0.0f,
				-downforce,
				false,
				true,
				true,
				false);
		}
	};

	static AlwaysOnGround _AlwaysOnGround{
		"alwaysonground",
		"Always On Ground",
		"Keeps the vehicle pinned by applying downward force"
	};
}
