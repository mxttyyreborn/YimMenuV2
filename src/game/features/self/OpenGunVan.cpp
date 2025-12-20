#include "core/commands/Command.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features::Self
{
	struct VehiclePool
	{
		int count;
		int vehicles[1023];
	};

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

			VehiclePool pool{};
			VEHICLE::GET_ALL_VEHICLES(&pool);

			for (int i = 0; i < pool.count; ++i)
			{
				const int veh = pool.vehicles[i];
				if (!ENTITY::DOES_ENTITY_EXIST(veh))
					continue;

				if (ENTITY::GET_ENTITY_MODEL(veh) == gunVanModel)
				{
					Vector3 pos = ENTITY::GET_ENTITY_COORDS(veh, false);

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
					return;
				}
			}

		}
	};

	static OpenGunVan _OpenGunVan{"opengunvan", "Goto Gun Van", "Teleport to the current Gun Van location"};
}
