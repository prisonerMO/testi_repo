addMissionEventHandler ["EntityKilled", {
    params ["_unit"];

    if (!(_unit isKindOf "CAManBase") && side (group _unit) isNotEqualTo civilian) exitWith {
        false;
    };
    
    Krzyc_confirmedKills = Krzyc_confirmedKills + 1;
      
    if (Krzyc_corfirmedKills == 5) then {
        Krzyc_corfirmedKills = 0;

        
        //    Run from On Activation in trigger: execVM "script\HuntPlayer.sqf";
        //    Spawn indep units on marker "huntplayer"
        //  LL_huntGroup = [markerPos "huntplayer",  INDEPENDENT, 3] call BIS_fnc_spawnGroup;
        LL_huntGroup = [markerPos "huntplayer", OPFOR,["B_GEN_Soldier_F","B_GEN_Commander_F","B_GEN_Soldier_F","B_GEN_Soldier_F","B_GEN_Offroad_01_comms_F","EC635_Unarmed" ]] call BIS_fnc_spawnGroup;
        LL_huntGroup setCombatMode "RED";
        LL_huntGroup setSpeedMode "FULL";
        LL_huntGroup setFormation "LINE";

        {
            _x addPrimaryWeaponItem "acc_flashlight";
            _x enableGunLights "forceOn";
            _x setSkill ["aimingAccuracy", 0.25];
            _x setSkill ["aimingShake", 0.40];
            _x setSkill ["aimingSpeed", 0.40];
            _x setSkill ["reloadSpeed", 1];
        } forEach (units LL_huntGroup);

        //Tell _huntGroup to stalk / hunt player / players group.
        _isHunting = [LL_huntGroup, group player] spawn BIS_fnc_stalk;
    };
}];
