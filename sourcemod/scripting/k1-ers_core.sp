#include <cstrike>
#include <sdkhooks>
#include <clientprefs>
#include <k1_ers_core> 
 
public Plugin myinfo = 
{
    name = "[K1-ERS] End Round Skin Core",
    author = "K1NG",
    description = "http//projecttm.ru/",
    version = "2.2"
}

int g_iWeaponDefIndex[] = 
{
	/* 0*/ 9, /* 1*/ 7, /* 2*/ 16, /* 3*/ 60, /* 4*/ 1, /* 5*/ 61, /* 6*/ 32, /* 7*/ 4, /* 8*/ 2, 
	/* 9*/ 36, /*10*/ 63, /*11*/ 3, /*12*/ 30, /*13*/ 64, /*14*/ 35, /*15*/ 25, /*16*/ 27, /*17*/ 29, 
	/*18*/ 14, /*19*/ 28, /*20*/ 34, /*21*/ 17, /*22*/ 33, /*23*/ 24, /*24*/ 19, /*25*/ 26, /*26*/ 10, /*27*/ 13, 
	/*28*/ 40, /*29*/ 8, /*30*/ 39, /*31*/ 38, /*32*/ 11, /*33*/ 507, /*34*/ 508, /*35*/ 500, 
	/*36*/ 514, /*37*/ 515, /*38*/ 505, /*39*/ 516, /*40*/ 509, /*41*/ 512, /*42*/ 506,
	/*43*/ 519, /*44*/ 520, /*45*/ 522, /*46*/ 523, /*47*/ 23, /*48*/ 503, /*49*/ 517,
	/*50*/ 518, /*51*/ 521, /*52*/ 525
};

public void OnPluginStart()
{
    LoadConfig();
}

public void LoadConfig()
{
    char szBuffer[PLATFORM_MAX_PATH]; 
    BuildPath(Path_SM, szBuffer, sizeof(szBuffer), "configs/k1-ers/core.cfg");

    KeyValues hKeyValues = new KeyValues("K1-ERS");

    if (!hKeyValues.ImportFromFile(szBuffer))
    {
        SetFailState("Не удалось открыть файл %s", szBuffer);
        return;
    }
}

public APLRes AskPluginLoad2(Handle hPlugin, bool bLate, char[] sError, int iLenError)
{
    CreateNative("K1_ERS_GiveClientSkin", Give_WS_GiveClientSkin);
}                   

public int Give_WS_GiveClientSkin(Handle hPlugin, int iArgs)
{
    int iClient = GetNativeCell(1);
    int iSkinId = GetNativeCell(2);
    int iWeaponId = GetNativeCell(3);
    if(iWeaponId == -1)
        return 0;
    if(!IsClientInGame(iClient) || IsFakeClient(iClient))
        return 0;

    return GiveDrop(iClient, iSkinId, iWeaponId);
}

bool IsValidClient(int client)
{
    if (!(1 <= client <= MaxClients) || !IsClientInGame(client) || IsFakeClient(client) || IsClientSourceTV(client) || IsClientReplay(client))
    {
        return false;
    }
    return true;
}

public int GiveDrop(int iClient, int iSkinId, int iWeaponId)
{
    if(!IsValidClient(iClient))
		return 0;
    else
    {
        Protobuf pb = view_as<Protobuf>(StartMessageAll("SendPlayerItemDrops", USERMSG_RELIABLE));
        Protobuf entity_updates = pb.AddMessage("entity_updates");
        int itemId[2];

        itemId[0] = GetRandomInt(0, 1000000);
        itemId[1] = itemId[0];

        entity_updates.SetInt("accountid", GetSteamAccountID(iClient)); 
        entity_updates.SetInt64("itemid", itemId);
        if(iWeaponId <= 52)
            entity_updates.SetInt("defindex", g_iWeaponDefIndex[iWeaponId]);
        else
            entity_updates.SetInt("defindex", iWeaponId);
        entity_updates.SetInt("paintindex", iSkinId); 
        entity_updates.SetInt("rarity", 1); 
        EndMessage();
        return 1;
    }
}