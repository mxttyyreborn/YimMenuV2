#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features::Self
{
	class OpenGunVan final : public Command
	{
		using Command::Command;

		void OnCall() override
		{
			HUD::SET_FRONTEND_ACTIVE(true);

			HUD::ACTIVATE_FRONTEND_MENU(
				MISC::GET_HASH_KEY("FE_MENU_VERSION_GUNVAN"),
				false,
				-1
			);
		}
	};

	static OpenGunVan _OpenGunVan{"opengunvan", "Open Gun Van", "Open the Gun Van shop remotely"};
}
