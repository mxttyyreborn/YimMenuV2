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
            if (auto vehicle = Self::GetVehicle())
            {
                // Get raw GTA vehicle handle from wrapper
                const auto handle = vehicle.GetHandle();
                if (!handle)
                    return;

                // Get speed via wrapper
                const float speed = vehicle.GetSpeed();

                // Scale downforce with speed
                const float downforce = std::clamp(speed * 12.0f, 50.0f, 300.0f);

                // Apply downward force using native
                ENTITY::APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(
                    handle,
                    1,          // Force type
                    0.0f,
                    0.0f,
                    -downforce, // Push down
                    false,
                    true,
                    true,
                    false
                );
            }
        }
    };

    // Toggle command (same pattern as RocketBoost)
    static AlwaysOnGround _AlwaysOnGround{
        "alwaysonground",
        "Always On Ground",
        "Applies downward force to keep vehicle wheels on the ground"
    };
}
