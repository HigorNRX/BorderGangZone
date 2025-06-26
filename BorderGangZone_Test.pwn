#include <a_samp>
#include <core>
#include <float>
#include <string>
#include <foreach>
#include <sscanf2>
#include <zcmd>


#include "projects\BorderGangZone.inc"
#pragma tabsize 0
new idborder;


main()
{
	print("\n----------------------------------");
	print("  Border_GangZone\n");
	print("----------------------------------\n");
}

public OnPlayerConnect(playerid)
{
	GameTextForPlayer(playerid,"~w~SA-MP: ~r~Border_GangZone",5000,5);
	return 1;
}

CreateSimpleVehicle(playerid, modelid, Float:x, Float:y, Float:z, Float:angle)
{
    new vehicleid = CreateVehicle(modelid, x, y, z, angle, -1, -1, 600);
    PutPlayerInVehicle(playerid, vehicleid, 0);
    return vehicleid;
}

public OnPlayerCommandText(playerid, cmdtext[])
{
     if (strcmp(cmdtext, "/carro", true) == 0)
    {
        new Float:x, Float:y, Float:z, Float:a;
        GetPlayerPos(playerid, x, y, z);
        GetPlayerFacingAngle(playerid, a);
        CreateSimpleVehicle(playerid, 411, x + 3.0, y, z, a);
        return 1;
    }

    return 0;
}

public OnPlayerSpawn(playerid)
{
	//ShowDelimitedAreaForPlayer(playerid, idmapdel);
	SetPlayerInterior(playerid,0);
	TogglePlayerClock(playerid,0);
	BorderGangZoneShowForPlayer(playerid, idborder, 0xFF0000FF);
	BorderGangZoneFlashForPlayer(playerid, idborder, 0xFFFFFFFF);

	return 1;
}

public OnPlayerDeath(playerid, killerid, reason)
{
   	return 1;
}

SetupPlayerForClassSelection(playerid)
{
 	SetPlayerInterior(playerid,14);
	SetPlayerPos(playerid,258.4893,-41.4008,1002.0234);
	SetPlayerFacingAngle(playerid, 270.0);
	SetPlayerCameraPos(playerid,256.0815,-43.0475,1004.0234);
	SetPlayerCameraLookAt(playerid,258.4893,-41.4008,1002.0234);
}

public OnPlayerRequestClass(playerid, classid)
{
	SetupPlayerForClassSelection(playerid);
	return 1;
}

public OnGameModeInit()
{
	SetGameModeText("Border_GangZone");
	ShowPlayerMarkers(1);
	ShowNameTags(1);
	AddPlayerClass(265,1958.3783,1343.1572,15.3746,270.1425,0,0,0,0,-1,-1);
	UsePlayerPedAnims();
	idborder = BorderGangZoneCreate(2067.3110, 1482.9606, 1773.8752, 1188.3843, 1997.5565, 1385.2053, 1857.7756, 1272.7135);
	return 1;
}

public OnPlayerClickMap(playerid, Float:fX, Float:fY, Float:fZ)
{
    // Verifica se o jogador está logado ou em estado válido, se necessário
    SetPlayerPos(playerid, fX, fY, fZ + 2.0); // Adiciona 2.0 em Z para evitar cair no chão
    SendClientMessage(playerid, -1, "Você foi teleportado para o local clicado no mapa.");
    return 1;
}

CMD:mudarvw(playerid, params[])
{
    new vw;
    if(sscanf(params, "d", vw)) return SendClientMessage(playerid, -1, "Uso: /mudarvw [id do virtual world]");

    SetPlayerVirtualWorld(playerid, vw);
    SendClientMessage(playerid, -1, "Você mudou de Virtual World com sucesso!");
    return 1;
}

CMD:spawnp(playerid)
{
    SpawnPlayer(playerid);
    SendClientMessage(playerid, -1, "Você Spawn com sucesso!");
    return 1;
}