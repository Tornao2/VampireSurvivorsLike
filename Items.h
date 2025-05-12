#pragma once
#include <unordered_map>
#include <string>
#include <SFML/Graphics/Sprite.hpp>
/**
 * @struct ItemInfo
 * Struktura przechowuj¹ca informacje o posiadanym przedmiocie pasywnym.
 */
typedef struct ItemInfo {
	/**
	* Identyfikator typu przedmiotu.
	*/
	int itemId;
	/**
	* Aktualny poziom ulepszenia przedmiotu.
	*/
	int currentLevel;
	/**
	* Maksymalny mo¿liwy poziom ulepszenia przedmiotu.
	*/
	int maxLevel;
} ItemInfo;

/**
* Mapa przechowuj¹ca teksty opisuj¹ce efekty ulepszeñ dla poszczególnych przedmiotów/broni.
* Kluczem jest identyfikator przedmiotu/broni, wartoœci¹ jest wektor opisów dla kolejnych poziomów.
*/
static std::unordered_map<int, std::vector<std::string>> itemMessages = {
	{0, {"Increase HP\nby 20%", "Increase HP\nby further 20%", "Increase HP\nby further 15%", "Increase base\nHP by 20", "Increase HP\nfurther by 30%"}},  
	{1, {"Increase dmg\nby 10%", "Increase dmg\nby further 10%", "Increase dmg\nby further 15%", "Increase dmg\nby further 15%", "Increase dmg\nby further 15%"}}, 
	{2, {"Increase ms\nby 5%", "Increase ms\nby further 10%", "Increase ms\nby further 15%", "Increase base\nms by 0.1", "Increase ms\nfurther by 10%"}},   
	{3, {"Increase armor\nby 1", "Increase armor\nby further 1", "Increase armor\nby further 1", "Increase armor\nby further 1", "Increase armor\nby further 2"}}, 
	{4, {"Increase xp\nby 5%", "Increase xp by\nfurther 5%", "Increase xp by\nfurther 10%", "Increase xp\nby further 5%", "Increase xp\nby further 10%"}},  
	{5, {"Cast blue orbs\ndealing small\ndamage", "Increase damage", "Increase speed", "Increase damage", "Increase fire\nrate"}},                  
	{6, {"Cast red orbs\ndealing huge\ndamage", "Increase speed", "Increase speed", "Increase fire\nrate", "Increase speed"}},                     
	{7, {"Throw knife\nvertically", "Increase damage", "Increase damage", "Increase range", "Increase fire\nrate"}},                                  
	{8, {"Shoot arrow\nhorizontally", "Increase fire\nrate", "Increase fire\nrate", "Increase damage", "Increase damage"}},                            
	{9, {"Shoot gun at\nrandom enemy", "Increase fire\nrate", "Increase range", "Increase range", "Increase damage"}},                           
	{10, {"Combine wands\nand add more\neffects"}},                                                                                              
	{11, {"Throw also a \nknife behind"}},                                                                                                          
	{12, {"Make knifes\nfaster"}},                                                                                                                 
	{13, {"Shoot also\nan arrow behind"}},                                                                                                         
	{14, {"Make bullets\nstronger"}}                                                                                                               
};

/**
 * @brief Zwraca tekst opisuj¹cy efekt ulepszenia danego przedmiotu/broni na okreœlony poziom.
 * @param itemId Identyfikator przedmiotu/broni.
 * @param upgradeToLevel Poziom, na który przedmiot/broñ ma zostaæ ulepszony (lub aktualny poziom dla opisu).
 * @return Tekst opisuj¹cy ulepszenie.
 */
std::string getUpgradeText(int itemId, int upgradeToLevel);