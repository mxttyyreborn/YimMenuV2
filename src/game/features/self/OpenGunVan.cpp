#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
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

			int vehicles[1024]{};
			const int count = VEHICLE::GET_ALL_VEHICLES(vehicles, 1024);

			int gunVan = 0;

			for (int i = 0; i < count; ++i)
			{
				const int veh = vehicles[i];
				if (!ENTITY::DOES_ENTITY_EXIST(veh))
					continue;

				if (ENTITY::GET_ENTITY_MODEL(veh) == gunVanModel)
				{
					gunVan = veh;
					break;
				}
			}

			if (!gunVan)
				return; // Gun Van not spawned yet

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

	static OpenGunVan _OpenGunVan{"opengunvan", "Open Gun Van", "Teleport to the current Gun Van location"};
}
