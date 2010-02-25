-- NAXXRAMAS

-- Set to not working boses NON ATTACKABLE FLAG 
UPDATE `creature_template` SET `unit_flags` = '33554434' WHERE `entry` IN (15954,15936,16011,16061,16060,16064,16065,30549,16063,16028,15931,15932,15928,15989,15990,29448,29373, 29417,29701,29615,29991,30061,29718,29324,29955,29940,30602,30603,30601,30600);
-- North 15954,
-- Heigan 15936,
-- Loatheb 16011, 29718
-- Instructor 16061,
-- Gothik 16060,
-- Horsameni 16064, 16065, 30549, 16063,
-- Patchewrk 16028,
-- Grobulus 15931,
-- Gluth 15932,
-- Tadius 15928,
-- Saphiron 15989,
-- Kelthuzad 15990
-- 25ppl ids
-- 29448,29373, 29417,29701,29615,29991,30061,29718,29324,29955,29940,30602,30603,30601,30600,

-- DOORS
UPDATE `gameobject_template` SET `flags` = '34' WHERE `entry` IN (194022);

-- Arachnid Quarter::AnubRekhan
UPDATE creature_template SET `ScriptName` = 'boss_anubrekhan', `AIName` = '' WHERE `entry` IN (15956);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15956,29249);
-- Arachnid Quarter::Crypt Guard
UPDATE creature_template SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` IN (16573);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `minlevel` = '81', `maxlevel` = '81', `minmana` = '5000', `maxmana` = '5000' WHERE `entry` IN (16573, 29256);
UPDATE creature_template SET `armor` = '9729', `faction_A` = '21', `faction_H` = '21', `mindmg` = '422', `maxdmg` = '586', `attackpower` = '1000', `dmg_multiplier` = '7.5', `baseattacktime` = '1000' WHERE `entry` IN (27943);

-- Arachnid Quarter::Faerlina
UPDATE creature_template SET `ScriptName` = 'boss_faerlina', `AIName` = '' WHERE `entry` IN (15953);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15953,29268);
-- Arachnid Quarter::Worshippers and folowers
DELETE FROM `creature` WHERE `id` IN (16506);
UPDATE creature_template SET `AIName` = 'EventAI', `ScriptName` = '' WHERE `entry` IN (16506,16505);
UPDATE creature_template SET `minmana` ='58750', `maxmana` = '58750' WHERE `entry` IN (29273);

-- Arachnid Quarter::Maexna
UPDATE creature_template SET `ScriptName` = 'boss_maexxna', `AIName` = '' WHERE `entry` IN (15952);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15952,29278);
-- Arachnid Quarter::WebWrap
UPDATE `creature_template` SET `minhealth` = '5040', `maxhealth` = '5040' WHERE `entry` IN (16486);
UPDATE `creature_template` SET `minhealth` = '12600', `maxhealth` = '12600' WHERE `entry` IN (30183);

-- Plagued Quarter::Noth
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (15954,29615);
UPDATE creature_template SET `ScriptName` = 'boss_noth', `AIName` = '' WHERE `entry` IN (15954);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15954,29615);

-- Plagued Quarter::Heigan
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (15936,29701);
UPDATE creature_template SET `ScriptName` = 'boss_heigan', `AIName` = '' WHERE `entry` IN (15936);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15936,29701);

-- Plagued Quarter::Loatheb
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (16011,29718);
UPDATE creature_template SET `ScriptName` = 'boss_loatheb', `AIName` = '' WHERE `entry` IN (16011);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (16011,29718);
UPDATE creature_template SET `ScriptName` = 'mob_fungalspore', `AIName` = '' WHERE `entry` IN (16286);

-- Military Quarter::Razovius
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (16061,29940);
UPDATE creature_template SET `ScriptName` = 'boss_razuvious', `AIName` = '' WHERE `entry` IN (16061);
UPDATE creature_template SET `ScriptName` = 'mob_understudies', `AIName` = '' WHERE `entry` IN (16803);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (16061,29940);
DELETE FROM creature_loot_template WHERE entry IN (16061,29940);
UPDATE creature_template SET `lootid` = '16061' WHERE `entry` IN (16061);
UPDATE creature_template SET `lootid` = '29940' WHERE `entry` IN (29940);

-- Military Quarter::Gothik
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (16060,29955);
UPDATE creature_template SET `ScriptName` = 'boss_gothik', `AIName` = '' WHERE `entry` IN (16060);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (16060,29955);
DELETE FROM creature_loot_template WHERE entry IN (16060,29955);
UPDATE creature_template SET `lootid` = '16060' WHERE `entry` IN (16060);
UPDATE creature_template SET `lootid` = '29955' WHERE `entry` IN (29955);

-- Military Quarter::Horseman
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (16064,16065,30549,16063,30602,30603,30601,30600);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (16064,16065,30549,16063,30602,30603,30601,30600);
DELETE FROM creature_loot_template WHERE entry IN (16064,16065,30549,16063,30602,30603,30601,30600);

-- Construct Quarter::Grobbulus
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (15931,29373);
UPDATE creature_template SET `ScriptName` = 'boss_grobbulus', `AIName` = '' WHERE `entry` IN (15931);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15931,29373);
DELETE FROM creature_loot_template WHERE entry IN (15931,29373);
UPDATE creature_template SET `lootid` = '15931' WHERE `entry` IN (15931);
UPDATE creature_template SET `lootid` = '29373' WHERE `entry` IN (29373);
-- cload id 16363 29379

-- Construct Quarter::Thaddius
UPDATE creature_template SET `unit_flags` = '0' WHERE `entry` IN (15928,29448);
UPDATE creature_template SET `ScriptName` = 'boss_thaddius', `AIName` = '' WHERE `entry` IN (15928);
UPDATE creature_template SET `ScriptName` = 'boss_feugen', `AIName` = '' WHERE `entry` IN (15930);
UPDATE creature_template SET `ScriptName` = 'boss_stalagg', `AIName` = '' WHERE `entry` IN (15929);
UPDATE creature_template SET `ScriptName` = 'mob_teslacoil', `AIName` = '' WHERE `entry` IN (16218);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15928,29448);
DELETE FROM creature_loot_template WHERE entry IN (15928,29448);
UPDATE creature_template SET `lootid` = '15931' WHERE `entry` IN (15928);
UPDATE creature_template SET `lootid` = '29373' WHERE `entry` IN (29448);

-- FrostWyrmLair::Sapphiron
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (15989,29991);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15989,29991);
DELETE FROM creature_loot_template WHERE entry IN (15989,29991);
UPDATE creature_template SET `lootid` = '15931' WHERE `entry` IN (15989);
UPDATE creature_template SET `lootid` = '29373' WHERE `entry` IN (29991);
-- FrostWyrmLair::Spell Blizzard
UPDATE creature_template SET `faction_A` = '14', `faction_H` ='14', `ScriptName` = 'mob_blizzard', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (16474);

-- FrostWyrmLair::Kelthuzad
UPDATE `creature_template` SET `unit_flags` = '0' WHERE `entry` IN (15990,30061);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (15990,30061);
DELETE FROM creature_loot_template WHERE entry IN (15990,30061);
UPDATE creature_template SET `lootid` = '15931' WHERE `entry` IN (15990);
UPDATE creature_template SET `lootid` = '29373' WHERE `entry` IN (30061);
-- FrostWyrmLair::Kheltuzad Shadow Fissure Spell
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_shadowfissure', `minlevel` = '81', `maxlevel` = '81', `faction_A` = '14', `faction_H` = '14' WHERE `entry` IN (16129);
-- FrostWyrmLair::Adds Speed
UPDATE creature_template SET `minlevel` = '80', `maxlevel` = '80', `speed` = '1' WHERE entry IN (16429,16428,16427,30015,30048,30018);

-- Naxxramas ACID

UPDATE `creature_template` SET `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (16981,16363);
-- DELETE EventAIScripts
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (16981,16363);
INSERT INTO `creature_ai_scripts`
(`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`,
 `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) 
VALUES

-- Plagued Guardian
(1698101, '16981', '0', '0', '100', '3', '5000', '15000','5000','10000', '11', '54890', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Plagued Guardian - Cast Explosion (Normal)'),
(1698102, '16981', '0', '0', '100', '5', '5000', '15000','5000','10000', '11', '54891', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Plagued Guardian - Cast Explosion (Heroic)'),
-- Grobulus Poison Cloud
(1636301, '16363', '0', '0', '100', '7', '500', '500','3500','3500', '11', '28137', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Poison Cloud - Cast AOE Cloud'),

-- NAXXRAMAS LOOT

DELETE FROM creature_loot_template WHERE entry IN (15956,29249,15953,29268,15952,29278,15954,29615,16011,29718,15936,29701);

-- Arachnid Quarter::AnubRekhan 
UPDATE creature_template SET `lootid` = '15956' WHERE `entry` IN (15956);
UPDATE creature_template SET `lootid` = '29249' WHERE `entry` IN (29249);

-- Arachnid Quarter::Faerlina
UPDATE creature_template SET `lootid` = '15953' WHERE `entry` IN (15953);
UPDATE creature_template SET `lootid` = '29268' WHERE `entry` IN (29268);

-- Arachnid Quarter::Maexxna 
UPDATE creature_template SET `lootid` = '15952' WHERE `entry` IN (15952);
UPDATE creature_template SET `lootid` = '29278' WHERE `entry` IN (29278);

-- Plagued Quarter::Noth
UPDATE creature_template SET `lootid` = '15954' WHERE `entry` IN (15954);
UPDATE creature_template SET `lootid` = '29615' WHERE `entry` IN (29615);

-- Plagued Quarter::Heigan
UPDATE creature_template SET `lootid` = '15954' WHERE `entry` IN (15936);
UPDATE creature_template SET `lootid` = '29615' WHERE `entry` IN (29701);

-- Plagued Quarter::Loatheb
UPDATE creature_template SET `lootid` = '15954' WHERE `entry` IN (16011);
UPDATE creature_template SET `lootid` = '29615' WHERE `entry` IN (29718);

INSERT INTO creature_loot_template
(entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2)
VALUES

-- Arachnid Quarter::AnubRekhan 10ppl
('15956', '39193', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39140', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39139', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39191', '20', '2', '1', '1', '0', '0', '0'),
('15956', '39190', '20', '2', '1', '1', '0', '0', '0'),
('15956', '39189', '20', '2', '1', '1', '0', '0', '0'),
('15956', '39188', '20', '2', '1', '1', '0', '0', '0'),
('15956', '39146', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39141', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39192', '20', '2', '1', '1', '0', '0', '0'),
-- Arachnid Quarter::AnubRekhan 25ppl
('29249', '39712', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39716', '20', '2', '1', '1', '0', '0', '0'),
('29249', '39714', '20', '2', '1', '1', '0', '0', '0'),
('29249', '39717', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39722', '20', '3', '1', '1', '0', '0', '0'),
('29249', '39718', '20', '3', '1', '1', '0', '0', '0'),
('29249', '39701', '20', '3', '1', '1', '0', '0', '0'),
('29249', '39720', '20', '2', '1', '1', '0', '0', '0'),
('29249', '39719', '20', '2', '1', '1', '0', '0', '0'),
('29249', '39704', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39703', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39706', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39721', '20', '2', '1', '1', '0', '0', '0'),
('29249', '39702', '20', '3', '1', '1', '0', '0', '0'),
-- Arachnid Quarter::Faerlina 10ppl
('15953', '39215', '20', '2', '1', '1', '0', '0', '0'),
('15953', '39196', '20', '2', '1', '1', '0', '0', '0'),
('15953', '39200', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39199', '20', '2', '1', '1', '0', '0', '0'),
('15953', '39217', '20', '2', '1', '1', '0', '0', '0'),
('15953', '39195', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39197', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39194', '20', '2', '1', '1', '0', '0', '0'),
('15953', '39198', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39216', '20', '1', '1', '1', '0', '0', '0'),
-- Arachnid Quarter::Faerlina 25ppl
('29268', '39726', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39727', '24.5', '3', '1', '1', '0', '0', '0'),
('29268', '39725', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39723', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39731', '20', '2', '1', '1', '0', '0', '0'),
('29268', '39734', '24.5', '3', '1', '1', '0', '0', '0'),
('29268', '39735', '20', '2', '1', '1', '0', '0', '0'),
('29268', '39729', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39733', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39757', '20', '2', '1', '1', '0', '0', '0'),
('29268', '39728', '24.5', '3', '1', '1', '0', '0', '0'),
('29268', '39756', '24.5', '3', '1', '1', '0', '0', '0'),
('29268', '39730', '20', '2', '1', '1', '0', '0', '0'),
('29268', '39732', '20', '2', '1', '1', '0', '0', '0'),
('29268', '39724', '2', '3', '1', '1', '0', '0', '0'),
-- Arachnid Quarter::Maexxna 10ppl
('15952', '39229', '20', '2', '1', '1', '0', '0', '0'),
('15952', '39230', '20', '2', '1', '1', '0', '0', '0'),
('15952', '39233', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39225', '20', '2', '1', '1', '0', '0', '0'),
('15952', '39224', '20', '2', '1', '1', '0', '0', '0'),
('15952', '39226', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39232', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39231', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39228', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39221', '20', '2', '1', '1', '0', '0', '0'),
-- Arachnid Quarter::Maexxna 25ppl
('29278', '40062', '20', '2', '1', '1', '0', '0', '0'),
('29278', '40063', '20', '3', '1', '1', '0', '0', '0'),
('29278', '39764', '20', '3', '1', '1', '0', '0', '0'),
('29278', '39768', '20', '3', '1', '1', '0', '0', '0'),
('29278', '40060', '20', '2', '1', '1', '0', '0', '0'),
('29278', '39760', '20', '3', '1', '1', '0', '0', '0'),
('29278', '39766', '20', '1', '1', '1', '0', '0', '0'),
('29278', '40061', '20', '2', '1', '1', '0', '0', '0'),
('29278', '39765', '20', '1', '1', '1', '0', '0', '0'),
('29278', '39758', '20', '1', '1', '1', '0', '0', '0'),
('29278', '39767', '20', '1', '1', '1', '0', '0', '0'),
('29278', '39763', '20', '2', '1', '1', '0', '0', '0'),
('29278', '39759', '20', '3', '1', '1', '0', '0', '0'),
('29278', '39761', '20', '1', '1', '1', '0', '0', '0'),
('29278', '39762', '20', '2', '1', '1', '0', '0', '0'),
-- Emblem Heroism
('15956', '40752', '100', '0', '1', '1', '0', '0', '0'),
('15953', '40752', '100', '0', '1', '1', '0', '0', '0'),
('15952', '40752', '100', '0', '1', '1', '0', '0', '0'),
-- Emblem Valor
('29249', '40753', '100', '0', '1', '1', '0', '0', '0'),
('29268', '40753', '100', '0', '1', '1', '0', '0', '0'),
('29278', '40753', '100', '0', '1', '1', '0', '0', '0'),

-- The Plague Quarter::Noth the Plaguebringer 10ppl
('15954', '39239', '20', '2', '1', '1', '0', '0', '0'),
('15954', '39235', '20', '2', '1', '1', '0', '0', '0'),
('15954', '39234', '20', '2', '1', '1', '0', '0', '0'),
('15954', '39236', '20', '2', '1', '1', '0', '0', '0'),
('15954', '39243', '20', '1', '1', '1', '0', '0', '0'),
('15954', '39237', '20', '1', '1', '1', '0', '0', '0'),
('15954', '39240', '20', '1', '1', '1', '0', '0', '0'),
('15954', '39242', '20', '1', '1', '1', '0', '0', '0'),
('15954', '39241', '20', '1', '1', '1', '0', '0', '0'),
('15954', '39244', '20', '2', '1', '1', '0', '0', '0'),
-- The Plague Quarter::Noth the Plaguebringer 25ppl
('29615', '40200', '20', '2', '1', '1', '0', '0', '0'),
('29615', '40197', '20', '3', '1', '1', '0', '0', '0'),
('29615', '40193', '20', '2', '1', '1', '0', '0', '0'),
('29615', '40192', '20', '3', '1', '1', '0', '0', '0'),
('29615', '40189', '20', '1', '1', '1', '0', '0', '0'),
('29615', '40198', '20', '3', '1', '1', '0', '0', '0'),
('29615', '40184', '20', '2', '1', '1', '0', '0', '0'),
('29615', '40196', '20', '3', '1', '1', '0', '0', '0'),
('29615', '40187', '20', '2', '1', '1', '0', '0', '0'),
('29615', '40602', '20', '3', '1', '1', '0', '0', '0'),
('29615', '40185', '20', '1', '1', '1', '0', '0', '0'),
('29615', '40186', '20', '1', '1', '1', '0', '0', '0'),
('29615', '40188', '20', '2', '1', '1', '0', '0', '0'),
('29615', '40190', '20', '1', '1', '1', '0', '0', '0'),
-- The Plague Quarter::Loatheb 10ppl
('16011', '40624', '33.3', '2', '1', '1', '0', '0', '0'),
('16011', '40623', '33.3', '2', '1', '1', '0', '0', '0'),
('16011', '40622', '33.3', '2', '1', '1', '0', '0', '0'),
('16011', '39259', '20', '1', '1', '1', '0', '0', '0'),
('16011', '39260', '20', '1', '1', '1', '0', '0', '0'),
('16011', '39258', '20', '1', '1', '1', '0', '0', '0'),
('16011', '39257', '20', '1', '1', '1', '0', '0', '0'),
('16011', '39256', '20', '1', '1', '1', '0', '0', '0'),
-- The Plague Quarter::Loatheb 25ppl
('29718', '40246', '20', '2', '1', '1', '0', '0', '0'),
('29718', '40247', '20', '2', '1', '1', '0', '0', '0'),
('29718', '40245', '20', '2', '1', '1', '0', '0', '0'),
('29718', '40243', '20', '1', '1', '1', '0', '0', '0'),
('29718', '40241', '20', '1', '1', '1', '0', '0', '0'),
('29718', '40240', '20', '1', '1', '1', '0', '0', '0'),
('29718', '40242', '20', '1', '1', '1', '0', '0', '0'),
('29718', '40637', '33.3', '3', '1', '1', '0', '0', '0'),
('29718', '40638', '33.3', '3', '1', '1', '0', '0', '0'),
('29718', '40639', '33.3', '3', '1', '1', '0', '0', '0'),
('29718', '40239', '20', '1', '1', '1', '0', '0', '0'),
('29718', '40244', '20', '2', '1', '1', '0', '0', '0'),
('29718', '40249', '20', '2', '1', '1', '0', '0', '0');

