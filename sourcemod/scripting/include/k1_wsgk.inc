#if defined _k1_wsgk_included   
    #endinput 
#endif 
#define _k1_wsgk_included    

/**
 * Если тип считывания ID оружия установлен на false индекс оружия смотрите по первой цифре, если true смотрите повторой цифре
 * Если вы работаете с перчатками у них указывается оригинальный id и bType будет работать как выбор команды перчаток false - T, true - CT
 * weapon_awp                   0   9  
 * weapon_ak47                  1   7  
 * weapon_m4a1                  2   16 
 * weapon_m4a1_silencer         3   60 
 * weapon_deagle                4   1  
 * weapon_usp_silencer          5   61 
 * weapon_hkp2000               6   32  
 * weapon_glock                 7   4  
 * weapon_elite                 8   2 
 * weapon_p250                  9   36 
 * weapon_cz75a                 10  63 
 * weapon_fiveseven             11  3 
 * weapon_tec9                  12  30 
 * weapon_revolver              13  64
 * weapon_nova                  14  35
 * weapon_xm1014                15  25
 * weapon_mag7                  16  27
 * weapon_sawedoff              17  29
 * weapon_m249                  18  14
 * weapon_negev                 19  28
 * weapon_mp9                   20  34
 * weapon_mac10                 21  17
 * weapon_mp7                   22  33
 * weapon_ump45                 23  24 
 * weapon_p90                   24  19
 * weapon_bizon                 25  26
 * weapon_famas                 26  10 
 * weapon_galilar               27  13
 * weapon_ssg08                 28  40
 * weapon_aug                   29  8
 * weapon_sg556                 30  39
 * weapon_scar20                31  38
 * weapon_g3sg1                 32  11
 * weapon_knife_karambit        33  507
 * weapon_knife_m9_bayonet      34  508
 * weapon_bayonet               35  500
 * weapon_knife_survival_bowie  36  514
 * weapon_knife_butterfly       37  515
 * weapon_knife_flip            38  505
 * weapon_knife_push            39  516 
 * weapon_knife_tactical        40  509
 * weapon_knife_falchion        41  512
 * weapon_knife_gut             42  506
 * weapon_knife_ursus           43  519
 * weapon_knife_gypsy_jackknife 44  520
 * weapon_knife_stiletto        45  522
 * weapon_knife_widowmaker      46  523
 * weapon_mp5sd                 47  23
 * weapon_knife_css             48  503
 * weapon_knife_cord            49  517
 * weapon_knife_canis           50  518
 * weapon_knife_outdoor         51  521
 * weapon_knife_skeleton        52  525
*/

/**
 *	Проверка что ядро загружено и готово к регистрации функций.
 *	-
 * @noparams
 *	-
 * @return					true - Ядро загружено.
 * 							false - Ядро не загружено.
*/
native bool WSGK_IsStarted();

/**
 *	Вызывается когда K1_WS-плагин загрузился.
 *	-
 * @noparams
 *	-
 * @noreturn
*/
forward void WSGK_Started();

/**
 *	Получить количество доступных скинов у определенного типа оружия.
 *	-
 * @param iClient			Индекс игрока.
 * @param iSkin			    Индекс скина.
 * @param bType			    Тип считывания ID оружия.
 *	-
 * @return					true - Число доступных скинов.
*/
native int WSGK_ClientNumSkinsHave(int iClient, int iGroup, bool bType = false);

/**
 *	Проверить доступ к предмету.
 *	-
 * @param iClient			Индекс игрока.
 * @param iSkin			    Индекс скина/перчаток/ножа (для стикеров не важно значение)
 * @param iGroup			Индекс оружия/группы перчаток (8000 - нож, 7000 стикеры.)
 * @param bType			    Тип считывания ID оружия.
 *	-
 * @return					true - Игрок имеет скин.
 * 							false - У игрока нет скина.
*/
native bool WSGK_ClientHaveItem (int iClient, int iSkin, int iGroup, bool bType = false); 

/**
 *	Выдать доступ к предмету.
 *	-
 * @param iClient			Индекс игрока.
 * @param iSkin			    Индекс скина/перчаток/ножа (для стикеров не важно значение)
 * @param iGroup			Индекс оружия/группы перчаток (8000 - нож, 7000 стикеры.)
 * @param bType			    Тип считывания ID оружия.
 *	-
 * @return					true - Скин успешно выдан.
 * 							false - У игрока уже есть доступ к скину, либо неверно указан индекс оружия.
*/
native bool WSGK_GiveClientItem (int iClient, int iSkin, int iGroup, bool bType = false);

/**
 *	Забрать доступ к предмету.
 *	-
 * @param iClient			Индекс игрока.
 * @param iSkin			    Индекс скина/перчаток/ножа (для стикеров не важно значение)
 * @param iGroup			Индекс оружия/группы перчаток (8000 - нож, 7000 стикеры.)
 * @param bType			    Тип считывания ID оружия.
 *	-
 * @return					true - Скин успешно изъят.
 * 							false - У игрока нет доступа к скину, либо неверно указан индекс оружия.
*/
native bool WSGK_TakeClientItem (int iClient, int iSkin, int iGroup, bool bType = false);

/**
 *	Проверить является ли оружие ножом.
 *	-
 * @param iGroup			Индекс ножа.
 * @param bType			    Тип считывания ID оружия.
 *	-
 * @return					true - Это нож.
 * 							false - Это не нож :)
*/
native bool WSGK_WeaponIsKnife(int iGroup, bool bType = false);

/**
 *	Сменить текущий нож игроку.
 *	-
 * @param iClient			Индекс игрока.
 * @param iGroup			Индекс ножа.
 * @param bType			    Тип считывания ID оружия.
 * @param iTeam			    Команда 0 - кт 1 - т.
 *	-
 * @return					true - Нож успешно сменен.
 * 							false - Неверно указан индекс ножа.
*/
native bool WSGK_ClientKnifeChange (int iClient, int iGroup, bool bType = false, int iTeam = 0);

/**
 *	Открыть меню WS.
 *	-
 * @param iClient			Индекс игрока.
 *	-
 * @return					true - Меню успешно открыто.
 * 							false - Возникла ошибка.
*/
native bool WSGK_ClientOpenMainMenuWS (int iClient);

/**
 *	Открыть главное меню WSGK.
 *	-
 * @param iClient			Индекс игрока.
 *	-
 * @return					true - Меню успешно открыто.
 * 							false - Возникла ошибка.
*/
native bool WSGK_ClientOpenMainMenuWSGK (int iClient);

/**
 *	Выдать доступ к определенной группе скинов
 *	-
 * @param iClient			Индекс игрока.
 * @param sGroup			Уникальное имя группы. Если установить значение на all выдаст доступ ко всем скинам всех оружий
 *	-
 * @return					true - Группа успешно выдана.
 * 							false - Возникла ошибка.
*/
native bool WSGK_ClientCanUseSkinsGroup(int iClient, char[] sGroup);

/**
 *	Возвращает пользуется ли игрок перчатками или нет
 *	-
 * @param iClient			Индекс игрока.
 *	-
 * @return					true - Да.
 * 							false - Нет.
*/
native bool WSGK_ClientUsingGloves(int iClient);
