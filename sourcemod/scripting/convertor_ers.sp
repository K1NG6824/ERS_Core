
#include <sourcemod>
#pragma newdecls required
#pragma semicolon 1
#pragma tabsize 4

public Plugin myinfo =
{
	name = "Convertor ERS",
	author = "K1NG",
	version = "1.0",
	url = "http://ProjectTM.ru"
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
    RegAdminCmd("sm_convert_ers", UpdateERS, ReadFlagString("z"), "перевести");
}

public int GetWeaponIndexByDefIndex(int iGroup)
{
	for(int i; i < sizeof(g_iWeaponDefIndex); i++)
	{
		if(g_iWeaponDefIndex[i] == iGroup)
		{
			return i;
		}
	}
	
	return -1;
}

public Action UpdateERS(int iClient, int args)
{
  	char configPathR[PLATFORM_MAX_PATH],
         configPathK[PLATFORM_MAX_PATH];
	
	BuildPath(Path_SM, configPathR, sizeof(configPathR),        "configs/k1-ers/modules/random.cfg");
	BuildPath(Path_SM, configPathK,  sizeof(configPathK),       "configs/k1-ers/modules/kills.cfg");

    KeyValues kv = new KeyValues("K1-ERS_Kills");
    if(kv.ImportFromFile(configPathK)) 
    {
        int     iIndex;
        char    szDlBuffer[2][8], 
                index[256];
        kv.Rewind();
        if(kv.JumpToKey("chanse"))
        {
            KvGotoFirstSubKey(kv, false);
            do
            {
                kv.GetString(NULL_STRING, index, sizeof(index));
                int dlen = ExplodeString(index, "-", szDlBuffer, sizeof(szDlBuffer), sizeof(szDlBuffer[]), true);
                if(dlen > 1)
                {
                    iIndex = GetWeaponIndexByDefIndex(StringToInt(szDlBuffer[1]));
                    if(iIndex != -1) 
                    {
                        Format(index, sizeof index, "%s-%i", szDlBuffer[0], iIndex);
                        kv.SetString(NULL_STRING, index);
                    }
                }
            } while (KvGotoNextKey(kv, false));
            kv.Rewind();
            kv.ExportToFile(configPathK);  
            PrintToServer("Успешно прописаны все новые id в модуль Kills, можете удалить плагин convertor");
            CloseHandle(kv);
        }
    }
    kv = new KeyValues("K1-ERS_Random");
    if(kv.ImportFromFile(configPathR)) 
    {
        int iIndex;
        char szDlBuffer[2][8]; 
        char index[256];
        kv.Rewind();
        if(kv.JumpToKey("chanse"))
        {
            KvGotoFirstSubKey(kv, false);
            do
            {
                kv.GetString(NULL_STRING, index, sizeof(index));
                int dlen = ExplodeString(index, "-", szDlBuffer, sizeof(szDlBuffer), sizeof(szDlBuffer[]), true);
                if(dlen > 1)
                {
                    iIndex = GetWeaponIndexByDefIndex(StringToInt(szDlBuffer[1]));
                    if(iIndex != -1) 
                    {
                        Format(index, sizeof index, "%s-%i", szDlBuffer[0], iIndex);
                        kv.SetString(NULL_STRING, index);
                    }
                }
            } while (KvGotoNextKey(kv, false));
            kv.Rewind();
            kv.ExportToFile(configPathR);  
            PrintToServer("Успешно прописаны все новые id в модуль Random, можете удалить плагин convertor");
            CloseHandle(kv);
        }
    }
}