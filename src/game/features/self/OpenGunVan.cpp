#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/backend/Entities.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features::Self
{
	class OpenGunVan final : public Command
	{
		using Command::Command;

		void OnCall() override
		{
			auto ped = ::YimMenu::Self::GetPed();
			if (!ped)
				return;

			const int pedHandle = ped.GetHandle();

			const Hash gunVanModel = MISC::GET_HASH_KEY("weapontruck");

			Vehicle gunVan = 0;

			for (auto& veh : Entities::GetVehicles())
			{
				if (!veh)
					continue;

				const int handle = veh.GetHandle();

				if (ENTITY::GET_ENTITY_MODEL(handle) == gunVanModel)
				{
					gunVan = handle;
					break;
				}
			}

			if (!gunVan)
				return;

			Vector3 pos = ENTITY::GET_ENTITY_COORDS(gunVan, false);

			ENTITY::SET_ENTITY_COORDS(
				pedHandle,
				pos.x,
				pos.y,
				pos.z + 1.0f,
				false,
				false,
				false,
				true
			);
		}
	};

	static OpenGunVan _OpenGunVan{"opengunvan", "Goto Gun Van", "Teleport to the current Gun Van location"};
}
