#if defined _k1_cases_included   
    #endinput 
#endif 
#define _k1_cases_included    

/**
 *	Получить индекс модели по id кейса.
 *	-
 * @param iCase			    Id кейса.
 *	-
 * @return					id item.
 * 							-1 если не найдено.
*/
native int K1_CasesIdCaseModelById(int iCase);

/**
 *	Получить путь до модели кейса по id.
 *	-
 * @param iCase			    Id кейса.
 * @param sModel			Строка для записи.
 * @param iSize			    Размер строки для записи.
 *	-
 * @return					true.
 * 							false.
*/
native bool K1_CasesGetModelCaseById(int iCase, char[] sModel, int iSize);

/**
 *	Получить имя кейса по id.
 *	-
 * @param iCase			    Id кейса.
 * @param sName			Строка для записи.
 * @param iSize			    Размер строки для записи.
 *	-
 * @return					true.
 * 							false.
*/
native bool K1_CasesGetNameCaseById(int iCase, char[] sName, int iSize);


/**
 *	Выдать кейс.
 *	-
 * @param iClient			Индекс игрока.
 * @param iCase			    Индекс кейса
 * @param iNum			    Количество
 *	-
 * @return					true.
 * 							false.
*/

native bool K1_CasesGiveCase (int iClient, int iCase, int iNum); 
/**
 *	Выдать ключ.
 *	-
 * @param iClient			Индекс игрока.
 * @param iCase			    Индекс кейса
 * @param iNum			    Количество
 *	-
 * @return					true.
 * 							false.
*/

native bool K1_CasesGiveKey (int iClient, int iCase, int iNum); 
/**
 *	Забрать кейс.
 *	-
 * @param iClient			Индекс игрока.
 * @param iCase			    Индекс кейса
 * @param iNum			    Количество
 *	-
 * @return					true.
 * 							false.
*/

native bool K1_CasesTakeCase (int iClient, int iCase, int iNum); 
/**
 *	Забрать ключ.
 *	-
 * @param iClient			Индекс игрока.
 * @param iCase			    Индекс кейса
 * @param iNum			    Количество
 *	-
 * @return					true.
 * 							false.
*/
native bool K1_CasesTakeKey (int iClient, int iCase, int iNum); 
