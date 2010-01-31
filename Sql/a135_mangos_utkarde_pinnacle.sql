-- UTGARDE PINNACLE instance template

-- Utgarde Pinnacle::Svala
UPDATE `creature_template` SET `InhabitType` = '3', `unit_flags` = '0', `mindmg` = '345', `maxdmg` = '445', `attackpower` = '1500', `dmg_multiplier` = '7.5', `mechanic_immune_mask` = '1073463287', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '315000', `maxhealth` = '315000', `minmana` = '15976', `maxmana` = '15976', `faction_A` = '21', `faction_H` = '21', `AIName` = '', `Scriptname` = 'boss_svala' WHERE `entry` IN (26668);
UPDATE `creature_template` SET `InhabitType` = '3', `unit_flags` = '0', `mindmg` = '345', `maxdmg` = '445', `attackpower` = '1500', `dmg_multiplier` = '13', `mechanic_immune_mask` = '1073463287', `minlevel` = '82', `maxlevel` = '82', `minhealth` = '431392', `maxhealth` = '431392', `minmana` = '15976', `maxmana` = '15976', `faction_A` = '21', `faction_H` = '21' WHERE `entry` IN (30810);
-- Utgarde Pinnacle::svala ritual channelerer
UPDATE `creature_template` SET `faction_A` = '21', `faction_H` = '21', `minlevel` = '80', `maxlevel` = '80', `minhealth` = '8121', `maxhealth` = '8121', `minmana` = '15976', `maxmana` = '15976',`AIName` = '', `Scriptname` = 'npc_svala_channeler' WHERE `entry` IN (27281);
UPDATE `creature_template` SET `faction_A` = '21', `faction_H` = '21', `minlevel` = '81', `maxlevel` = '81', `minhealth` = '13033', `maxhealth` = '13033', `minmana` = '16324', `maxmana` = '16324' WHERE `entry` IN (30804);
-- Utgarde Pinnacle::RitualTarget

-- Utgarde Pinnacle::Gortok
UPDATE `creature_template` SET `unit_flags` = '0', `type_flags` = '0', `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_gortok' WHERE `entry` IN (26687);
UPDATE `creature_template` SET `unit_flags` = '0', `type_flags` = '0', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (30774);
-- Utgarde Pinnacle::Gortok add flags Rhino etc.
UPDATE `creature_template` SET `faction_A` = '35', `faction_H` = '35', `unit_flags` = '0', `type_flags` = '0', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (26684,30803,26683,30772,26685,30790,26686,30770);

-- Utgarde Pinnacle::Skadi

-- Utgarde Pinnacle::Grouf not used in event for  now
DELETE FROM creature WHERE id = '26893';
-- Ymirjar Harpooner
UPDATE `creature_template` SET `minhealth` = '18262', `maxhealth` = '18262', `minlevel` = '80', `maxlevel` = '81' WHERE `entry` IN (26692);
UPDATE `creature_template` SET `minhealth` = '26066', `maxhealth` = '26066', `minlevel` = '80', `maxlevel` = '81' WHERE `entry` IN (30819);

-- King Ymiron
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_ymiron' WHERE `entry` IN (26861);
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (30788);


-- Utgarde Pinnacle::ACID

UPDATE `creature_template` SET `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (26686,26684,26683,26685);

-- DELETE EventAIScripts
DELETE FROM creature_ai_scripts WHERE creature_id IN (26686,26684,26683,26685);

INSERT INTO `creature_ai_scripts`
(`id`, `creature_id`, `event_type`, `event_inverse_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`,
 `action1_type`, `action1_param1`, `action1_param2`, `action1_param3`, `action2_type`, `action2_param1`, `action2_param2`, `action2_param3`, `action3_type`, `action3_param1`, `action3_param2`, `action3_param3`, `comment`) 
VALUES

-- Utgarde Pinnacle::Furoiuces Rhino
(NULL, '26686', '0', '0', '100', '3', '5000', '15000','20000','40000', '11', '48130', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Gore (Normal)'),
(NULL, '26686', '0', '0', '100', '5', '5000', '15000','20000','40000', '11', '59264', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Gore (Heroic)'),
(NULL, '26686', '0', '0', '100', '3', '5000', '10000','15000','20000', '11', '48105', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Grevius Wond (Normal)'),
(NULL, '26686', '0', '0', '100', '5', '5000', '10000','15000','20000', '11', '59263', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Grevius Wond (Heroic)'),
(NULL, '26686', '0', '0', '100', '7', '10000', '15000','15000','30000', '11', '48131', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Rhino - Stomp'),

-- Utgarde Pinnacle::Furbolg
(NULL, '26684', '0', '0', '100', '7', '5000', '15000','20000','40000', '11', '48139', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Furbolg - Crazed'),
(NULL, '26684', '0', '0', '100', '3', '5000', '10000','15000','20000', '11', '48140', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Furbolg - Chain Lighting (Normal)'),
(NULL, '26684', '0', '0', '100', '5', '5000', '10000','15000','20000', '11', '59273', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Furbolg - Chain Lighting (Heroic)'),
(NULL, '26684', '0', '0', '100', '7', '10000', '15000','15000','30000', '11', '48144', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Furbolg - Terrifing Roar'),

-- Utgarde Pinnacle::Worgen
(NULL, '26683', '0', '0', '100', '7', '10000', '15000','15000','30000', '11', '48138', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Worgen - Cast Enrage'),
(NULL, '26683', '2', '0', '100', '7', '30', '0', '0','0', '11', '48142', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Worgen - Cast Enrage Perm'),
(NULL, '26683', '0', '0', '100', '3', '5000', '10000','15000','20000', '11', '48137', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Worgen - Cast Mortal Wound (Normal)'),
(NULL, '26683', '0', '0', '100', '5', '5000', '10000','15000','20000', '11', '59265', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Worgen - Cast Mortal Wound (Heroic)'),

-- Utgarde Pinnacle::Jormungar
(NULL, '26685', '0', '0', '100', '7', '5000', '10000','15000','20000', '11', '48132', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormungar - Cast Acid Split (Heroic)'),
(NULL, '26685', '0', '0', '100', '3', '5000', '15000','30000','50000', '11', '48136', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormungar - Cast Summon (Normal)'),
(NULL, '26685', '0', '0', '100', '5', '5000', '15000','30000','50000', '11', '59272', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormungar - Cast Summon (Heroic)'),
(NULL, '26685', '0', '0', '100', '3', '5000', '15000','10000','15000', '11', '48133', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormungar - Cast Breath (Normal)'),
(NULL, '26685', '0', '0', '100', '5', '5000', '15000','10000','15000', '11', '59271', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Jormungar - Cast Breath (Heroic)');
