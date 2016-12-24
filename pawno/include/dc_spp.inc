/*=============================================================================
		SetPlayerPos objects fix
			by Daniel_Cortez

		www.pro-pawn.ru

This code is licensed under the terms of zlib/libpng license.

Copyright (c) 2013 Daniel_Cortez
This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the
use of this software. Permission is granted to anyone to use this software for
any purpose, including commercial applications, and to alter it and
redistribute it freely, subject to the following restrictions:
    1.	The origin of this software must not be misrepresented; you must not
		claim that you wrote the original software. If you use this software in
		a product, an acknowledgment in the product documentation would be
		appreciated but is not required.
    2.	Altered source versions must be plainly marked as such, and must not be
		misrepresented as being the original software.
    3. This notice may not be removed or altered from any source distribution.
=============================================================================*/
#include <a_samp>
#if	!defined	Streamer_IncludeFileVersion
	#include <streamer>
#endif


#if	!defined	DC_SPP__FREEZE_TIME
	#define	DC_SPP__FREEZE_TIME	500
#endif


static	dc_spp__control[MAX_PLAYERS char];


@__dc_spp__unfreeze(playerid);
@__dc_spp__unfreeze(playerid)
	return Streamer_ToggleIdleUpdate(playerid, 0), TogglePlayerControllable(playerid, 1);


stock SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, interior=cellmin, world=cellmin, tpcar=1)
{
	Streamer_ToggleIdleUpdate(playerid, 1);
	if(dc_spp__control{playerid})
	{
		TogglePlayerControllable(playerid, 0);
		SetTimerEx("@__dc_spp__unfreeze", DC_SPP__FREEZE_TIME, 0, "d", playerid);
	}
	Streamer_UpdateEx(playerid, x, y, z, world, interior);
	if(interior != cellmin)
		SetPlayerInterior(playerid, interior);
	if(world != cellmin)
		SetPlayerVirtualWorld(playerid, world);
	if(tpcar && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		new veh = GetPlayerVehicleID(playerid);
		if(world != cellmin)
			SetVehicleVirtualWorld(veh, world);
		SetVehiclePos(veh, x, y, z);
	}
	else
		SetPlayerPos(playerid, x, y, z);
}


stock dc_spp__tpc(playerid, toggle)
	return dc_spp__control{playerid}=toggle%charmax, TogglePlayerControllable(playerid, toggle);
#if	defined	_ALS_TogglePlayerControllable
	#undef	TogglePlayerControllable
#else
	#define	_ALS_TogglePlayerControllable
#endif
#define	TogglePlayerControllable	dc_spp__tpc

public OnPlayerConnect(playerid)
{
	dc_spp__control{playerid} = 1;
	#if defined dc_spp__OnPlayerConnect
	dc_spp__OnPlayerConnect(playerid);
	#endif
	return 1;
}
#if	defined	_ALS_OnPlayerConnect
	#undef	OnPlayerConnect
#else
	#define	_ALS_OnPlayerConnect
#endif
#define OnPlayerConnect dc_spp__OnPlayerConnect
#if	defined	dc_spp__OnPlayerConnect
	forward	dc_spp__OnPlayerConnect(playerid);
#endif