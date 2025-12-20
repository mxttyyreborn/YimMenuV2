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

			const int gunVanBlipSprite = 810;

			int blip = HUD::GET_FIRST_BLIP_INFO_ID(gunVanBlipSprite);
			if (!HUD::DOES_BLIP_EXIST(blip))
				return;

			Vector3 pos = HUD::GET_BLIP_COORDS(blip);

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

	static OpenGunVan _OpenGunVan{ "opengunvan", "Open Gun Van", "Teleport to the Gun Van"};
}
