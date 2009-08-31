-- Azgalor
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` ='boss_azgalor' WHERE `entry` = '17842';

-- Summon
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = 'EventAI', `Scriptname` ='' WHERE `entry` = '17864';

DELETE FROM creature_ai_scripts WHERE creature_id IN (17864);
INSERT INTO creature_ai_scripts VALUES (NULL, '17864', '0', '0', '100', '3', '5000', '10000','15000','15000', '11', '31408', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Lesser DoomdGuard - Cast WarStomp');
INSERT INTO creature_ai_scripts VALUES (NULL, '17864', '0', '0', '100', '3', '6000', '12000','20000','25000', '11', '31406', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Lesser DoomdGuard - Cast Cripple');



