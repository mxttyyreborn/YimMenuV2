#include "CustomLabelText.hpp"

namespace YimMenu
{
	void CustomLabelText::InitImpl()
	{
		AddLabelImpl(0x1B2EA75B, "YimMenu Story"); // Title Story Mode
		AddLabelImpl(0xABB00DEB, "YimMenu"); // Title Pause Menu
		AddLabelImpl(Joaat("PM_ENTER_MP"), "Play GTA Online with YimMenuV2");
		AddLabelImpl(Joaat("PM_EXIT_GAME"), "Quit GTA V Enhanced");
		AddLabelImpl(Joaat("PM_GO"), "Play with YimMenuV2");
		AddLabelImpl(Joaat("HUD_MPREENTER"), "Joining a new session with YimMenu");
		AddLabelImpl(Joaat("PM_FRIEND_FM"), "Closed Friend Session with YimMenuV2");
		AddLabelImpl(Joaat("PM_INF_EXIT"), "Quit to desktop with YimMenuV2");
		AddLabelImpl(Joaat("PM_CREWS"), "Join a Crew Only Session with YimMenuV2");
		AddLabelImpl(Joaat("PM_INF_PGOT"), "Online with YimMenuV2");
		AddLabelImpl(Joaat("PM_INVO_FM"), "Join an Invite Only Session with YimMenuV2");
		AddLabelImpl(Joaat("LOADING_SPLAYER_L"), "Loading Story Mode with YimMenuV2");
		AddLabelImpl(Joaat("PM_NCREW_FM"), "Join a Crew Session with YimMenuV2");
		AddLabelImpl(Joaat("PM_CREW_FM"), "Join a Closed Crew Session with YimMenuV2");
		AddLabelImpl(Joaat("PM_SOLO_FM"), "Join a Solo Session with YimMenuV2");
		AddLabelImpl(Joaat("PM_FRESES"), "Join a Friends Only Session with YimMenuV2");
		AddLabelImpl(Joaat("PM_CHOOSE_CHAR"), "Choose your character");
		AddLabelImpl(Joaat("PM_INF_PGOT"), "Online with YimMenuV2");
	}

	bool CustomLabelText::AddLabelImpl(joaat_t hash, const std::string_view text)
	{
		const auto size = text.size() + 1;
		auto buffer = std::make_unique<char[]>(size);
		memcpy(buffer.get(), text.data(), size);
		return m_LabelOverwrites.insert({hash, std::move(buffer)}).second;
	}

	bool CustomLabelText::AddLabelImpl(joaat_t hash, CustomLabelText_t&& cb)
	{
		return m_Labels.insert({hash, std::move(cb)}).second;
	}
}
