#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

namespace YimMenu::Features
{
    class AlwaysOnGround : public LoopedCommand
    {
        using LoopedCommand::LoopedCommand;

        void OnTick() override
        {
            if (auto vehicle = Self::GetVehicle())
            {
                vehicle.SetGravity(20.0f);
            }
        }
    };

    // This line is what makes it APPEAR in the Vehicle menu
    static AlwaysOnGround _AlwaysOnGround{"alwaysonground", "Always On Ground", "Keeps vehicle pressed to the ground using extra gravity"};
}
