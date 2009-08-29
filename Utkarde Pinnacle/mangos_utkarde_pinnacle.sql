-- Instance ScriptName Update
UPDATE `instance_template` SET `script` = 'instance_utgarde_pinnacle' WHERE `map` IN (575);

/* 
################################################
Svala Sorrowgrave

dmg bosa
czar zabijajcy playera
prison
*/
-- map 575

-- Svala Sorrowgrave 26668 30810
-- Normal
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '315000', `maxhealth` = '315000', `minmana` = '15976', `maxmana` = '15976', `faction_A` = '21', `faction_H` = '21', `AIName` = '', `Scriptname` = 'boss_svala' WHERE `entry` IN (26668);
-- Heroic
UPDATE `creature_template` SET `minlevel` = '82', `maxlevel` = '82', `minhealth` = '431392', `maxhealth` = '431392', `minmana` = '15976', `maxmana` = '15976', `faction_A` = '21', `faction_H` = '21' WHERE `entry` IN (30810);

/*
dmg
acid spele
*/

-- Ritual Channeler
UPDATE `creature_template` SET `unit_flags` = '4', `faction_A` = '21', `faction_H` = '21' WHERE `entry` IN (27281,30804);
-- Normal
UPDATE `creature_template` SET `minlevel` = '80', `maxlevel` = '80', `minhealth` = '8121', `maxhealth` = '8121', `minmana` = '15976', `maxmana` = '15976', `AIName` = '', `Scriptname` = 'mob_ritual_channeler' WHERE `entry` IN (27281);
-- Heroic
UPDATE `creature_template` SET `minlevel` = '81', `maxlevel` = '81', `minhealth` = '13033', `maxhealth` = '13033', `minmana` = '16324', `maxmana` = '16324' WHERE `entry` IN (30804);


/*
################################################
Gortok Palehoof 26687
Instance Map ID 575

(26687,26685,26686,26684,26683,30772,30803,30790,30770,30774);

*/
-- Gortok Palehoof 
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_gortok_palehoof' WHERE `entry` IN (26687);

-- Unit Flags Removed From 33554752
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (26687,26685,26686,26684,26683,30772,30803,30790,30770,30774);
-- 72  40 mial boss
UPDATE `creature_template` SET `type_flags` = '0' WHERE `entry` IN (26687,26685,26686,26684,26683,30772,30803,30790,30770,30774);

-- Set Inst Data
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (26685,26686,26684,26683); 
INSERT INTO `creature_ai_scripts` VALUES(NULL, '26685', '6', '0', '100', '6', '0', '0','0','0', '34', '1', '3', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormunger - Set Data On Death');
INSERT INTO `creature_ai_scripts` VALUES(NULL, '26686', '6', '0', '100', '6', '0', '0','0','0', '34', '2', '3', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Set Data On Death');
INSERT INTO `creature_ai_scripts` VALUES(NULL, '26684', '6', '0', '100', '6', '0', '0','0','0', '34', '3', '3', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Furbolg - Set Data On Death');
INSERT INTO `creature_ai_scripts` VALUES(NULL, '26683', '6', '0', '100', '6', '0', '0','0','0', '34', '4', '3', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Worgen - Set Data On Death');



/*
22515,
26861,
28368,
28351,
27327,
26555,
26554,
26553,
26550,
23472,
27309,
27308,
27307,
26536,
27303,
19871,
27273,
15475,
29281,
26696,
26694,
26693,
26687,
2110,
26686,
26685,
26684,
26683,
26672,
26670,
26669,
26667,
14881,
26893);

*/
