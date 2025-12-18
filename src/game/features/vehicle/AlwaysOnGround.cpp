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
                // Get speed using wrapper
                const float speed = vehicle.GetSpeed();

                // Simple downforce scaling
                const float downforce = std::clamp(speed * 10.0f, 40.0f, 250.0f);

                // Apply force using native through handle
                vehicle.ApplyForceToCenterOfMass(
                    0.0f,
                    0.0f,
                    -downforce
                );
            }
        }
    };

    static AlwaysOnGround _AlwaysOnGround{
        "alwaysonground",
        "Always On Ground",
        "Applies downforce to keep vehicle wheels on the ground"
    };
}
