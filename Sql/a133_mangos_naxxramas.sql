-- NAXXRAMAS

-- Set to not working boses NON ATTACKABLE FLAG 
UPDATE `creature_template` SET `unit_flags` = '33554434' WHERE `entry` IN (15954,15936,16011,16061,16060,16064,16065,30549,16063,16028,15931,15932,15928,15989,15990,29448,29373, 29417,29701,29615,29991,30061,29718,29324,29955,29940,30602,30603,30601,30600);
-- North 15954,
-- Heigan 15936,
-- Loatheb 16011,
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


-- NAXXRAMAS LOOT

DELETE FROM creature_loot_template WHERE entry IN (15956,29249,15953,29268,15952,29278);

-- Arachnid Quarter::AnubRekhan 
UPDATE creature_template SET `lootid` = '15956' WHERE `entry` IN (15956);
UPDATE creature_template SET `lootid` = '29249' WHERE `entry` IN (29249);

-- Arachnid Quarter::Faerlina
UPDATE creature_template SET `lootid` = '15953' WHERE `entry` IN (15953);
UPDATE creature_template SET `lootid` = '29268' WHERE `entry` IN (29268);

-- Arachnid Quarter::Maexxna 
UPDATE creature_template SET `lootid` = '15952' WHERE `entry` IN (15952);
UPDATE creature_template SET `lootid` = '29278' WHERE `entry` IN (29278);

INSERT INTO creature_loot_template
(entry, item, ChanceOrQuestChance, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2)
VALUES

-- Arachnid Quarter::AnubRekhan 10ppl
('15956', '39193', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39140', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39139', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39191', '20', '1', '1', '1', '0', '0', '0'),
('15956', '39190', '19', '1', '1', '1', '0', '0', '0'),
('15956', '39189', '19', '1', '1', '1', '0', '0', '0'),
('15956', '39188', '19', '1', '1', '1', '0', '0', '0'),
('15956', '39146', '19', '1', '1', '1', '0', '0', '0'),
('15956', '39141', '19', '1', '1', '1', '0', '0', '0'),
('15956', '39192', '19', '1', '1', '1', '0', '0', '0'),

-- Arachnid Quarter::AnubRekhan 25ppl
('29249', '39712', '24', '1', '1', '1', '0', '0', '0'),
('29249', '39716', '24', '1', '1', '1', '0', '0', '0'),
('29249', '39714', '24', '1', '1', '1', '0', '0', '0'),
('29249', '39717', '23', '1', '1', '1', '0', '0', '0'),
('29249', '39722', '20', '1', '1', '1', '0', '0', '0'),
('29249', '39718', '19', '1', '1', '1', '0', '0', '0'),
('29249', '39701', '19', '1', '1', '1', '0', '0', '0'),
('29249', '39720', '19', '1', '1', '1', '0', '0', '0'),
('29249', '39719', '19', '1', '1', '1', '0', '0', '0'),
('29249', '39704', '19', '1', '1', '1', '0', '0', '0'),
('29249', '39703', '19', '1', '1', '1', '0', '0', '0'),
('29249', '39706', '19', '1', '1', '1', '0', '0', '0'),
('29249', '39721', '19', '1', '1', '1', '0', '0', '0'),
('29249', '39702', '18', '1', '1', '1', '0', '0', '0'),

-- Arachnid Quarter::Faerlina 10ppl
('15953', '39215', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39196', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39200', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39199', '20', '1', '1', '1', '0', '0', '0'),
('15953', '39217', '19', '1', '1', '1', '0', '0', '0'),
('15953', '39195', '19', '1', '1', '1', '0', '0', '0'),
('15953', '39197', '19', '1', '1', '1', '0', '0', '0'),
('15953', '39194', '19', '1', '1', '1', '0', '0', '0'),
('15953', '39198', '19', '1', '1', '1', '0', '0', '0'),
('15953', '39216', '19', '1', '1', '1', '0', '0', '0'),

-- Arachnid Quarter::Faerlina 25ppl
('29268', '39726', '24', '1', '1', '1', '0', '0', '0'),
('29268', '39727', '23', '1', '1', '1', '0', '0', '0'),
('29268', '39725', '23', '1', '1', '1', '0', '0', '0'),
('29268', '39723', '23', '1', '1', '1', '0', '0', '0'),
('29268', '39731', '20', '1', '1', '1', '0', '0', '0'),
('29268', '39734', '19', '1', '1', '1', '0', '0', '0'),
('29268', '39735', '19', '1', '1', '1', '0', '0', '0'),
('29268', '39729', '19', '1', '1', '1', '0', '0', '0'),
('29268', '39733', '19', '1', '1', '1', '0', '0', '0'),
('29268', '39757', '19', '1', '1', '1', '0', '0', '0'),
('29268', '39728', '19', '1', '1', '1', '0', '0', '0'),
('29268', '39756', '19', '1', '1', '1', '0', '0', '0'),
('29268', '39730', '19', '1', '1', '1', '0', '0', '0'),
('29268', '39732', '19', '1', '1', '1', '0', '0', '0'),
('29268', '39724', '2', '1', '1', '1', '0', '0', '0'),

-- Arachnid Quarter::Maexxna 10ppl
('15952', '39229', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39230', '20', '1', '1', '1', '0', '0', '0'),
('15952', '39233', '19', '1', '1', '1', '0', '0', '0'),
('15952', '39225', '19', '1', '1', '1', '0', '0', '0'),
('15952', '39224', '19', '1', '1', '1', '0', '0', '0'),
('15952', '39226', '19', '1', '1', '1', '0', '0', '0'),
('15952', '39232', '19', '1', '1', '1', '0', '0', '0'),
('15952', '39231', '19', '1', '1', '1', '0', '0', '0'),
('15952', '39228', '19', '1', '1', '1', '0', '0', '0'),
('15952', '39221', '19', '1', '1', '1', '0', '0', '0'),

-- Arachnid Quarter::Maexxna 25ppl
('29278', '40062', '20', '1', '1', '1', '0', '0', '0'),
('29278', '40063', '20', '1', '1', '1', '0', '0', '0'),
('29278', '39764', '19', '1', '1', '1', '0', '0', '0'),
('29278', '39768', '19', '1', '1', '1', '0', '0', '0'),
('29278', '40060', '19', '1', '1', '1', '0', '0', '0'),
('29278', '39760', '19', '1', '1', '1', '0', '0', '0'),
('29278', '39766', '19', '1', '1', '1', '0', '0', '0'),
('29278', '40061', '19', '1', '1', '1', '0', '0', '0'),
('29278', '39765', '19', '1', '1', '1', '0', '0', '0'),
('29278', '39758', '19', '1', '1', '1', '0', '0', '0'),
('29278', '39767', '19', '1', '1', '1', '0', '0', '0'),
('29278', '39763', '19', '1', '1', '1', '0', '0', '0'),
('29278', '39759', '19', '1', '1', '1', '0', '0', '0'),
('29278', '39761', '18', '1', '1', '1', '0', '0', '0'),
('29278', '39762', '18', '1', '1', '1', '0', '0', '0');