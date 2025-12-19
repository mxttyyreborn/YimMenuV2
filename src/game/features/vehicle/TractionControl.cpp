#include "core/commands/LoopedCommand.hpp"
#include "game/backend/Self.hpp"
#include "game/gta/Natives.hpp"

namespace YimMenu::Features::Vehicle
{
    static LoopedCommand g_TractionControl{
        "tractioncontrol",
        "Traction Control",
        "Extremely increases vehicle grip and removes wheelspin",
        []()
        {
            if (!g_Self || !g_Self->m_Ped)
                return;

            Ped ped = g_Self->m_Ped;

            if (!PED::IS_PED_IN_ANY_VEHICLE(ped, false))
                return;

            Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, false);

            if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(vehicle, -1, false) != ped)
                return;

            // Disable grip reduction (burnouts/drifting)
            VEHICLE::SET_VEHICLE_REDUCE_GRIP(vehicle, false);

            // Massive friction override
            VEHICLE::SET_VEHICLE_FRICTION_OVERRIDE(vehicle, 10.0f);

            // Prevent wheel slip / damage
            VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(vehicle, false);
            VEHICLE::SET_VEHICLE_WHEELS_CAN_BURST(vehicle, false);

            // Eliminate low-speed traction loss
            VEHICLE::SET_VEHICLE_HANDLING_FLOAT(
                vehicle,
                "CHandlingData",
                "fLowSpeedTractionLossMult",
                0.0f
            );

            // High traction curves = glued to road
            VEHICLE::SET_VEHICLE_HANDLING_FLOAT(
                vehicle,
                "CHandlingData",
                "fTractionCurveMin",
                5.0f
            );

            VEHICLE::SET_VEHICLE_HANDLING_FLOAT(
                vehicle,
                "CHandlingData",
                "fTractionCurveMax",
                5.0f
            );
        }
    };
}
