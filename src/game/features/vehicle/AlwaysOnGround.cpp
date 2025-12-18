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
                // Reduce upward velocity to keep wheels planted
                auto velocity = vehicle.GetVelocity();

                // Only dampen upward movement
                if (velocity.z > 0.0f)
                {
                    velocity.z *= 0.25f;
                    vehicle.SetVelocity(velocity);
                }
            }
        }
    };

    static AlwaysOnGround _AlwaysOnGround{
        "alwaysonground",
        "Always On Ground",
        "Keeps vehicle planted by damping upward movement"
    };
}
