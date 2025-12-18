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
                // Simple constant downward force
                // Keeps wheels planted without doing anything fancy
                vehicle.ApplyForce(
                    { 0.0f, 0.0f, -15.0f }, // Downward force
                    { 0.0f, 0.0f, 0.0f }    // Center of mass
                );
            }
        }
    };

    // THIS is what makes it appear in the Vehicle menu
    static AlwaysOnGround _AlwaysOnGround{
        "alwaysonground",
        "Always On Ground",
        "Keeps the vehicle firmly planted on the ground"
    };
}
