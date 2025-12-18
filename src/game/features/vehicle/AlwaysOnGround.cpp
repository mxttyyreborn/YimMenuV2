#include "core/commands/LoopedCommand.hpp"
#include "game/gta/Vehicle.hpp"
#include "game/gta/Entity.hpp"
#include "game/gta/Ped.hpp"
#include "game/gta/Player.hpp"

namespace
{
    class AlwaysOnGround : public LoopedCommand
    {
    public:
        AlwaysOnGround()
            : LoopedCommand(
                "alwaysonground",
                "Always On Ground",
                "Applies downforce to keep vehicle wheels on the ground",
                g_vehicle)
        {
        }

        void OnTick() override
        {
            auto ped = PLAYER::PLAYER_PED_ID();
            if (!PED::IS_PED_IN_ANY_VEHICLE(ped, false))
                return;

            auto vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);
            if (!ENTITY::DOES_ENTITY_EXIST(vehicle))
                return;

            float speed = ENTITY::GET_ENTITY_SPEED(vehicle);

            // Scale downforce with speed
            float downforce = std::clamp(speed * 12.0f, 50.0f, 300.0f);

            ENTITY::APPLY_FORCE_TO_ENTITY_CENTER_OF_MASS(
                vehicle,
                1,
                0.0f,
                0.0f,
                -downforce,
                false,
                true,
                true,
                false);
        }
    };

    static AlwaysOnGround _AlwaysOnGround{};
}
