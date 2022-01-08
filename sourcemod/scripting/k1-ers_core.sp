#include <cstrike>
#include <sdkhooks>
#include <clientprefs>
#include <k1_ers_core> 
 
public Plugin myinfo = 
{
    name = "[K1-ERS] End Round Skin Core",
    author = "K1NG",
    description = "http//projecttm.ru/",
    version = "2.0"
}

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
        entity_updates.SetInt("defindex", iWeaponId);
        entity_updates.SetInt("paintindex", iSkinId); 
        entity_updates.SetInt("rarity", 1); 
        EndMessage();
        return 1;
    }
}