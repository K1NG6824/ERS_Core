#if defined _k1_exitems_included   
    #endinput 
#endif 
#define _k1_exitems_included    

public SharedPlugin __pl_k1_EXITEMS = 
{
	name = "k1_exitems",
	file = "EXITEMS_Core.smx",

	#if defined REQUIRE_PLUGIN
		required = 1
	#else
		required = 0
	#endif
};

/**
 * weapon_awp                   0 
 * weapon_ak47                  1 
 * weapon_m4a1                  2
 * weapon_m4a1_silencer         3
 * weapon_deagle                4
 * weapon_usp_silencer          5 
 * weapon_hkp2000               6 
 * weapon_glock                 7  
 * weapon_elite                 8 
 * weapon_p250                  9 
 * weapon_cz75a                 10
 * weapon_fiveseven             11
 * weapon_tec9                  12 
 * weapon_revolver              13  
 * weapon_nova                  14 
 * weapon_xm1014                15  
 * weapon_mag7                  16  
 * weapon_sawedoff              17  
 * weapon_m249                  18  
 * weapon_negev                 19  
 * weapon_mp9                   20  
 * weapon_mac10                 21  
 * weapon_mp7                   22
 * weapon_ump45                 23
 * weapon_p90                   24
 * weapon_bizon                 25
 * weapon_famas                 26 
 * weapon_galilar               27
 * weapon_ssg08                 28
 * weapon_aug                   29 
 * weapon_sg556                 30
 * weapon_scar20                31
 * weapon_g3sg1                 32
 * weapon_knife_karambit        33
 * weapon_knife_m9_bayonet      34
 * weapon_bayonet               35
 * weapon_knife_survival_bowie  36
 * weapon_knife_butterfly       37
 * weapon_knife_flip            38
 * weapon_knife_push            39
 * weapon_knife_tactical        40
 * weapon_knife_falchion        41
 * weapon_knife_gut             42
 * weapon_knife_ursus           43
 * weapon_knife_gypsy_jackknife 44
 * weapon_knife_stiletto        45
 * weapon_knife_widowmaker      46
 * weapon_mp5sd                 47
 * weapon_knife_css             48
 * weapon_knife_cord            49
 * weapon_knife_canis           50
 * weapon_knife_outdoor         51
 * weapon_knife_skeleton        52
*/

/**
 *	Вызывается когда EXITEMS Core - загрузился.
 *	-
 * @noparams
 *	-
 * @noreturn
*/
forward void EXITEMS_Started();

/**
 *	Проверка что ядро загружено и готово к регистрации функций.
 *	-
 * @noparams
 *	-
 * @return					true - Ядро загружено.
 * 							false - Ядро не загружено.
*/
native bool EXITEMS_IsStarted();

/**
 *	Получить количество предметов игрока с определенной группой.
 *	-
 * @param iClient			Индекс игрока.
 * @param sCategory			Имя категории предметов
 * @param iGroup			Индекс группы
 *	-
 * @return					Возвращает количество предметов игрока
 *
*/
native int EXITEMS_ClientNumItemsByGroup(int iClient, const char[] sCategory, int iGroup)

/**
 *	Проверить количество предметов игрока.
 *	-
 * @param iClient			Индекс игрока.
 * @param iItem			    Индекс предмета
 * @param iGroup			Индекс группы
 * @param sCategory			Имя категории предметов
 *	-
 * @return					Возвращает количество предметов игрока
 *
*/
native int EXITEMS_ClientHaveItem(int iClient, int iItem = 0, int iGroup = 0, const char[] sCategory); 

/**
 *	Выдать предмет игроку.
 *	-
 * @param iClient			Индекс игрока.
 * @param iItem			    Индекс предмета
 * @param iGroup			Индекс группы
 * @param sCategory			Имя категории предметов
 *	-
 * @return					Возвращает новое количество предметов игрока
 * 							Вернет -1 если что то пошло не так
*/
native int EXITEMS_GiveClientItem(int iClient, int iItem = 0, int iGroup = 0, int iAmount, const char[] sCategory);

/**
 *	Забрать предмет у игрока.
 *	-
 * @param iClient			Индекс игрока.
 * @param iItem			    Индекс предмета
 * @param iGroup			Индекс группы
 * @param sCategory			Имя категории предметов
 *	-
 * @return					Возвращает новое количество предметов игрока
 * 							Вернет -1 если что то пошло не так
*/
native int EXITEMS_TakeClientItem(int iClient, int iItem = 0, int iGroup = 0, int iAmount, const char[] sCategory);


/**
 *	Установить количество предметов у игрока.
 *	-
 * @param iClient			Индекс игрока.
 * @param iItem			    Индекс предмета
 * @param iGroup			Индекс группы
 * @param sCategory			Имя категории предметов
 *	-
 * @return					Возвращает новое количество предметов игрока
 * 							Вернет -1 если что то пошло не так
*/
native int EXITEMS_SetClientItem(int iClient, int iItem = 0, int iGroup = 0, int iAmount, const char[] sCategory);

/**
 *	Открыть главное меню EXITEMS.
 *	-
 * @param iClient			Индекс игрока.
 *	-
 * @return					true - Меню успешно открыто.
 * 							false - Возникла ошибка.
*/
native bool EXITEMS_ClientOpenMainMenuEXITEMS (int iClient);

/**
 *	Проверить отображается ли игроку в данный момент изображение в Hint
 *	-
 * @param iClient			Индекс игрока.
 *	-
 * @return					true 	- 	Изображение найдено и отображение игроку в Hint
 *							false 	- 	Если не найдено изображение
*/
native bool EXITEMS_CheckShowHint(int iClient);

/**
 *	Обратная функция
 *
*/
typedef RegisterCallback = function void (int iClient);

/**
 *	Зарегистрировать новую категорию предметов
 *	-
 * @param sCategory			Имя категории предметов.
 * @param MainMenu			Функция открытия главного меню плагина
 * @param AdminMenu			Функция открытия админ меню плагина.
 *	-
 * @noreturn
*/
native void EXITEMS_RegisterCategory(const char[] sCategory, 
									RegisterCallback MainMenu = INVALID_FUNCTION, 
									RegisterCallback AdminMenu = INVALID_FUNCTION);

/**
 *	Получить ArrayList id предметов определенной группы в группе ядра
 *	-
 * @param iClient			Индекс игрока.
 * @param sCategory			Имя категории предметов
 * @param iGroup			Индекс группы
 *	-
 * @return					Возвращает ArrayList с предметами;
*/
native ArrayList EXITEMS_GetClientItemsByGroupInGroups(int iClient, const char[] sCategory, int iGroup);

/**
 *	Получить ArrayList id предметов с определенной группой в группе ядра
 *	-
 * @param iClient			Индекс игрока.
 * @param sCategory			Имя категории предметов
 * @param iItems			Индекс предмета
 *	-
 * @return					Возвращает ArrayList с группами;
*/
native ArrayList EXITEMS_GetClientGroupByItemsInGroups(int iClient, const char[] sCategory, int iItem);

/**
 *	Получить ArrayList id предметов определенной группы
 *	-
 * @param iClient			Индекс игрока.
 * @param sCategory			Имя категории предметов
 * @param iGroup			Индекс группы
 *	-
 * @return					Возвращает ArrayList с предметами;
*/
native ArrayList EXITEMS_GetClientItemsByGroup(int iClient, const char[] sCategory, int iGroup);

/**
 *	Получить ArrayList id групп с определенным предметом
 *	-
 * @param iClient			Индекс игрока.
 * @param sCategory			Имя категории предметов
 * @param iItems			Индекс предмета
 *	-
 * @return					Возвращает ArrayList с группами;
*/
native ArrayList EXITEMS_GetClientGroupByItems(int iClient, const char[] sCategory, int iItems);

/**
 *	Выгрузить категорию предметов
 *	-
 * @param sCategory			Имя категории предметов
 *	-
 * @noreturn
*/
native int EXITEMS_UnRegisterCategory(const char[] sCategory);

/**
 *	Открыть Админ меню
 *	-
 * @param iClient			Индекс игрока.
 *	-
 * @return					true - Меню открыто игроку
 * 							false - У игрока недостаточно прав
*/
native bool EXITEMS_ClientOpenAdminMenuEXITEMS(int iClient);

/**
 *	Зарегистрировать изображение.
 *	-
 * @param sCategory			Имя категории предметов
 * @param iItem			    Индекс предмета
 * @param iGroup			Индекс группы
 * @param sImg				Путь до изображения. (некоторые модули имеют встроенный путь)
 *	-
 * @return					true - Изображение для предмета зарегистрировано
 * 							false - Не зарегистрирована категория либо что то пошло не так
*/
native bool EXITEMS_RegisterImg(const char[] sCategory, int iItem, int iGroup = 0, const char[] sImg);

/**
 *	Отобразить изображение игроку.
 *	-
 * @param iClient			Индекс игрока.
 * @param sCategory			Имя категории предметов
 * @param iItem			    Индекс предмета
 * @param iGroup			Индекс группы
 *	-
 * @return					true 	- 	Изображение найдено и отображение игроку в Hint
 *							false 	- 	Если не найдено изображение
*/
native bool EXITEMS_PrintImgItem(int iClient, const char[] sCategory, int iItem, int iGroup = 0);

/**
 *	Получить базу данных ядра.
 *	-
 * @return					Database
*/
native Database EXITEMS_GetDatabase();

/**
 *	Записать лог.
 *	-
 * @param sCategory			Имя категории.
 * @param sInfo				Строка которая будет записана.
 *	-
 * @noreturn
*/
native void EXITEMS_AddLog(const char[] sCategory, const char[] sInfo);

/**
 *	Записать дебаг.
 *	-
 * @param sCategory			Имя категории.
 * @param sInfo				Строка которая будет записана.
 *	-
 * @noreturn
*/
native void EXITEMS_LogDebug(const char[] sCategory, const char[] sInfo);

/**
 *	Получить префикс чата.
 *	-
 * @param sPrefix			Строка в которую будет записано, значение.
 *	-
 * @noreturn
*/
native void EXITEMS_GetPrefix(char[] sPrefix);

/**
 *	Получить через сколько дней происходит очистка базы данных.
 *	-
 * @return					Количество дней.
*/
native int EXITEMS_InactiveDays();

/**
 *	Получить строку для SQL запроса с очисткой от неактивных игроков.
 *	-
 * @param sBufer			Строка в которую будет записан запрос.
 *	-
 * @noreturn
*/
native void EXITEMS_DeleteInactive(char[] sBufer);

/**
 *	Получить префикс базы данных.
 *	-
 * @param sPrefix			Строка в которую будет записан префикс.
 *	-
 * @noreturn
*/
native void EXITEMS_GetPrefixDB(char[] sPrefix);

/**
 *	Добавить предмет в группу ядра. Создает если группа еще не создана.
 *	-
 * @param sGroup			Имя группы ядра.
 * @param sCategory			Имя категории предметов.
 * @param iItemId			Индекс предмета.
 * @param iGroup			Индекс группы.
 *	-
 * @return					true - Успешно зарегистрировано.
 * 							false - Произошла ошибка при регистрации.
 *
*/
native int EXITEMS_GroupRegister(const char[] sGroup, const char[] sCategory, int iItemId, int iGroup = 0);

/**
 *	Удалить группу в ядре. Создает если группа еще не создана.
 *	-
 * @param sGroup			Имя группы ядра. 
 * @param sCategory			Имя категории предметов. Если указать 'all' то очистит все категории в группе
 *	-
 * @return					true - Успешно удалено.
 * 							false - Группа не найдена.
 *
*/
native int EXITEMS_GroupUnRegister(const char[] sGroup, const char[] sCategory = "all");

/**
 *	Проверить доступ к предмету в группе.
 *	-
 * @param iClient			Индекс игрока.
 * @param sCategory			Имя категории предметов.
 * @param iItemId			Индекс предмета.
 * @param iGroup			Индекс группы.
 *	-
 * @return					true - Есть доступ.
 * 							false - Нет доступа.
 *
*/
native bool EXITEMS_ClientCheckItemGroup(int iClient, const char[] sCategory, int iItemId, int iGroup = 0);

/**
 *	Выдать доступ к группе игроку.
 *	-
 * @param iClient			Индекс игрока.
 * @param sGroup			Имя группы ядра. 
 *	-
 * @return					true - Успешно выдано.
 * 							false - Группа не найдена.
 *
*/
native bool EXITEMS_ClientGiveGroup(int iClient, const char[] sGroup);

/**
 *	Забрать доступ к группе у игрока.
 *	-
 * @param iClient			Индекс игрока.
 * @param sGroup			Имя группы ядра. 
 *	-
 * @return					true - Успешно изъято.
 * 							false - Группа у игрока не найдена.
 *
*/
native bool EXITEMS_ClientTakeGroup(int iClient, const char[] sGroup);

#if !defined REQUIRE_PLUGIN
	public void __pl_k1_exitems_SetNTVOptional()
	{
		MarkNativeAsOptional("EXITEMS_IsStarted");
		MarkNativeAsOptional("EXITEMS_ClientHaveItem");
		MarkNativeAsOptional("EXITEMS_GiveClientItem");
		MarkNativeAsOptional("EXITEMS_TakeClientItem");
		MarkNativeAsOptional("EXITEMS_SetClientItem");
		MarkNativeAsOptional("EXITEMS_WeaponIsKnife");
		MarkNativeAsOptional("EXITEMS_ClientKnifeChange");
		MarkNativeAsOptional("EXITEMS_ClientOpenMainMenuWS");
		MarkNativeAsOptional("EXITEMS_ClientOpenMainMenuEXITEMS");
		MarkNativeAsOptional("EXITEMS_ClientUsingGloves");
		MarkNativeAsOptional("EXITEMS_CheckShowHint");
		MarkNativeAsOptional("EXITEMS_RegisterCategory");
		MarkNativeAsOptional("EXITEMS_GetClientItemsByGroup");
		MarkNativeAsOptional("EXITEMS_GetClientGroupByItems");
		MarkNativeAsOptional("EXITEMS_UnRegisterCategory");
		MarkNativeAsOptional("EXITEMS_ClientOpenAdminMenuEXITEMS");
		MarkNativeAsOptional("EXITEMS_RegisterImg");
		MarkNativeAsOptional("EXITEMS_PrintImgItem");
		MarkNativeAsOptional("EXITEMS_GetDatabase");
		MarkNativeAsOptional("EXITEMS_AddLog");
		MarkNativeAsOptional("EXITEMS_LogDebug");
		MarkNativeAsOptional("EXITEMS_GetPrefix");
		MarkNativeAsOptional("EXITEMS_InactiveDays");
		MarkNativeAsOptional("EXITEMS_DeleteInactive");
		MarkNativeAsOptional("EXITEMS_GetPrefixDB");
		MarkNativeAsOptional("EXITEMS_ClientNumItemsByGroup");
		MarkNativeAsOptional("EXITEMS_DeleteInactiveUsers");
		MarkNativeAsOptional("EXITEMS_GroupRegister");
		MarkNativeAsOptional("EXITEMS_GroupUnRegister");
		MarkNativeAsOptional("EXITEMS_ClientCheckItemGroup");
		MarkNativeAsOptional("EXITEMS_ClientGiveGroup");
		MarkNativeAsOptional("EXITEMS_ClientTakeGroup");
		MarkNativeAsOptional("EXITEMS_GetClientItemsByGroupInGroups");
		MarkNativeAsOptional("EXITEMS_GetClientGroupByItemsInGroups");
	}
#endif