#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"

#include <algorithm>

namespace YimMenu::Features
{
    class AlwaysOnGround : public LoopedCommand
    {
        using LoopedCommand::LoopedCommand;

        void OnTick() override
        {
            // Get the player's current vehicle safely
            if (auto vehicle = Self::GetVehicle())
            {
                // Current speed (m/s)
                const float speed = vehicle.GetSpeed();

                // Scale downforce with speed
                const float downforce = std::clamp(speed * 12.0f, 50.0f, 300.0f);

                // Apply downward force to keep wheels planted
                vehicle.ApplyForce(
                    { 0.0f, 0.0f, -downforce }, // force vector
                    true                        // center of mass
                );
            }
        }
    };

    // Toggleable command (ON = active every tick, OFF = disabled)
    static AlwaysOnGround _AlwaysOnGround{
        "alwaysonground",
        "Always On Ground",
        "Applies downward force to keep vehicle wheels on the ground"
    };
}
