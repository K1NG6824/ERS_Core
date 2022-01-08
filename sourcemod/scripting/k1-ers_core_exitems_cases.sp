#include <cstrike>
#include <sdkhooks>
#include <clientprefs>
#include <k1_ers_core> 
#include <k1_exitems> 
#include <k1_cases> 
bool g_bGiveKnife;
ArrayList g_hArrayWS;

char g_WeaponClasses[][] = 
{
	/* 0*/ "weapon_awp", /* 1*/ "weapon_ak47", /* 2*/ "weapon_m4a1", /* 3*/ "weapon_m4a1_silencer", /* 4*/ "weapon_deagle", /* 5*/ "weapon_usp_silencer", /* 6*/ "weapon_hkp2000", /* 7*/ "weapon_glock", /* 8*/ "weapon_elite", 
	/* 9*/ "weapon_p250", /*10*/ "weapon_cz75a", /*11*/ "weapon_fiveseven", /*12*/ "weapon_tec9", /*13*/ "weapon_revolver", /*14*/ "weapon_nova", /*15*/ "weapon_xm1014", /*16*/ "weapon_mag7", /*17*/ "weapon_sawedoff", 
	/*18*/ "weapon_m249", /*19*/ "weapon_negev", /*20*/ "weapon_mp9", /*21*/ "weapon_mac10", /*22*/ "weapon_mp7", /*23*/ "weapon_ump45", /*24*/ "weapon_p90", /*25*/ "weapon_bizon", /*26*/ "weapon_famas", /*27*/ "weapon_galilar", 
	/*28*/ "weapon_ssg08", /*29*/ "weapon_aug", /*30*/ "weapon_sg556", /*31*/ "weapon_scar20", /*32*/ "weapon_g3sg1", /*33*/ "weapon_knife_karambit", /*34*/ "weapon_knife_m9_bayonet", /*35*/ "weapon_bayonet", 
	/*36*/ "weapon_knife_survival_bowie", /*37*/ "weapon_knife_butterfly", /*38*/ "weapon_knife_flip", /*39*/ "weapon_knife_push", /*40*/ "weapon_knife_tactical", /*41*/ "weapon_knife_falchion", /*42*/ "weapon_knife_gut",
	/*43*/ "weapon_knife_ursus", /*44*/ "weapon_knife_gypsy_jackknife", /*45*/ "weapon_knife_stiletto", /*46*/ "weapon_knife_widowmaker", /*47*/ "weapon_mp5sd", /*48*/ "weapon_knife_css", /*49*/ "weapon_knife_cord", 
	/*50*/ "weapon_knife_canis", /*51*/ "weapon_knife_outdoor", /*52*/ "weapon_knife_skeleton"
};

public Plugin myinfo = 
{
    name = "[K1-ERS] End Round Skin Core (for EXITEMS)",
    author = "K1NG",
    description = "http//projecttm.ru/",
    version = "2.0"
}

public void OnPluginStart()
{
    g_hArrayWS = new ArrayList(2);
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

    g_bGiveKnife = !!hKeyValues.GetNum("give_knife", 0);

    if (hKeyValues.JumpToKey("weapons_skins") && hKeyValues.GotoFirstSubKey(false))
    {
        g_hArrayWS.Clear();
        char sBuffer[8];
        char sTemp[8];
        int idx;
        do
        {
            hKeyValues.GetSectionName(sBuffer, sizeof(sBuffer));
            hKeyValues.GetString(NULL_STRING, sTemp, sizeof sTemp);

            idx = g_hArrayWS.Length;
            g_hArrayWS.Push(StringToInt(sBuffer));
            g_hArrayWS.Set(idx, StringToInt(sTemp), 1);
            //0 ид скина - 1 id оружия 
        } while (hKeyValues.GotoNextKey(false));
    }
    delete hKeyValues;
}

public APLRes AskPluginLoad2(Handle hPlugin, bool bLate, char[] sError, int iLenError)
{
    CreateNative("K1_ERS_GiveClientSkin", Give_WS_GiveClientSkin);
}                   

public int Give_WS_GiveClientSkin(Handle hPlugin, int iArgs)
{
    int iClient = GetNativeCell(1);
    int iItemId = GetNativeCell(2);
    int iWeaponId = GetNativeCell(3);
    if(iWeaponId == -1)
    {
        int iIndex = g_hArrayWS.FindValue(iItemId, 0);
        if(iIndex == -1)
            return 0;

        iWeaponId = g_hArrayWS.Get(iIndex, 1);
    }
    if(!IsClientInGame(iClient) || IsFakeClient(iClient))
        return 0;

    return GiveDrop(iClient, iItemId, iWeaponId);
}

bool IsValidClient(int client)
{
    if (!(1 <= client <= MaxClients) || !IsClientInGame(client) || IsFakeClient(client) || IsClientSourceTV(client) || IsClientReplay(client))
    {
        return false;
    }
    return true;
}

public int GiveDrop(int iClient, int iItemId, int iWeaponId)
{
    if(!IsValidClient(iClient))
		return 0;
    else
    {
        if(iWeaponId == 10000)
        {
            int indexmodel = K1_CasesIdCaseModelById(iItemId);
            if(indexmodel == -1)
                indexmodel = 4001;
                
            K1_CasesGiveCase(iClient, iItemId, 1);
            Protobuf pb = view_as<Protobuf>(StartMessageAll("SendPlayerItemDrops", USERMSG_RELIABLE));
            Protobuf entity_updates = pb.AddMessage("entity_updates");
            int itemId[2];

            itemId[0] = GetRandomInt(0, 1000000);
            itemId[1] = itemId[0];

            entity_updates.SetInt("accountid", GetSteamAccountID(iClient)); 
            entity_updates.SetInt64("itemid", itemId);
            entity_updates.SetInt("defindex", indexmodel);
            entity_updates.SetInt("rarity", 1); 
            EndMessage();
            return 1;
        }
        else
        {
            if(g_bGiveKnife && IsKnifeClass(iWeaponId)) 
                EXITEMS_GiveClientItem(iClient, iWeaponId, _, 1, "EXITEMS_Knife");

            EXITEMS_GiveClientItem(iClient, iItemId, iWeaponId, 1, "EXITEMS_WS");

            WSGK_GiveClientItem(iClient, iItemId, iWeaponId, true);
            Protobuf pb = view_as<Protobuf>(StartMessageAll("SendPlayerItemDrops", USERMSG_RELIABLE));
            Protobuf entity_updates = pb.AddMessage("entity_updates");
            int itemId[2];

            itemId[0] = GetRandomInt(0, 1000000);
            itemId[1] = itemId[0];

            entity_updates.SetInt("accountid", GetSteamAccountID(iClient)); 
            entity_updates.SetInt64("itemid", itemId);
            entity_updates.SetInt("defindex", iWeaponId);
            entity_updates.SetInt("paintindex", iItemId); 
            entity_updates.SetInt("rarity", 1); 
            EndMessage();
            return 1;
        }
    }
    return 0;
}

bool IsKnifeClass(int index)
{
	if ((StrContains(g_WeaponClasses[i], "knife") > -1 && strcmp(g_WeaponClasses[i], "weapon_knifegg") != 0) || StrContains(g_WeaponClasses[i], "bayonet") > -1)
		return true;

	return false;
}