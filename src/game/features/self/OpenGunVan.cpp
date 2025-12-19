#include "core/commands/Command.hpp"
#include "game/gta/Natives.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
	class OpenGunVan final : public Command
	{
		using Command::Command;

		void OnExecute() override
		{
			const Hash gunVanScript = MISC::GET_HASH_KEY("gunvan_shop");

			if (!SCRIPT::HAS_SCRIPT_LOADED(gunVanScript))
			{
				SCRIPT::REQUEST_SCRIPT(gunVanScript);
				while (!SCRIPT::HAS_SCRIPT_LOADED(gunVanScript))
					WAIT(0);

				SCRIPT::START_NEW_SCRIPT(gunVanScript, 0);
			}

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
