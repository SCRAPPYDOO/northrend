-- Krik Thir 
-- podwyzszyc dmg robakow + dodac aoe chmure z 3 wiekszych
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_krik_thir', `minmana` ='46854', `maxmana` ='46854' WHERE `entry` IN (28684);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `minmana` = '54960', `maxmana` = '54960' WHERE `entry` IN (31612);
-- Krik Thir mini bosy
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_silthik' WHERE `entry` IN (28731);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_gashra' WHERE `entry` IN (28730);
UPDATE creature_template SET `AIName` = '', `Scriptname` = 'mob_narjil' WHERE `entry` IN (28729);
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31616);
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31615);
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31617);
-- Krik Thir summony
-- 59363 heroic hp
UPDATE creature_template SET `minhealth` ='6556', `maxhealth` ='6556', `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` = '31613';
-- 52446
UPDATE creature_template SET `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` = '28736';

-- Anubarak
-- ai scripts dla  2 summonow czy tam jednego :D
-- Trigger Invisible Mode
UPDATE `creature_template` SET `flags_extra` = '128' WHERE `entry` IN (29184);

-- Hadronox
/*
Event Bos  ma  initialize 1  moby
po zabiicu 1  ida 2  i pozneij bos
reszzta eventu nie do zrobienia narazie :D
*/
UPDATE creature_template SET `faction_A` = '14', `faction_H` = '14', `movementId` ='0', `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_hadronox' WHERE `entry` IN (28921);
UPDATE creature_template SET `faction_A` = '14', `faction_H` = '14', `movementId` ='0', `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31611);
-- UPDATE creature SET position_x = '529.157715', position_y = '576.377502', position_z = '733.610474', orientation = '5.295866' WHERE guid = '127401';



-- Trash Creature Template
-- Anub'ar Webspinner Shadowcaster Necromancer venomancer
UPDATE `creature_template` SET `minmana` = '7500', `maxmana` = '7500' WHERE `entry` IN (29335,28733,29098,29064,29217);
UPDATE `creature_template` SET `minmana` = '8979', `maxmana` = '8979' WHERE `entry` IN (31609,31605,31602,31601,31607);
-- Venomncer melee dmg
UPDATE `creature_template` SET `mindmg` = '270', `maxdmg` = '395', `attackpower` = '143' WHERE `entry` IN (29217);
UPDATE `creature_template` SET `mindmg` = '346', `maxdmg` = '499', `attackpower` = '287' WHERE `entry` IN (31607);
-- guardian melee dmg
UPDATE `creature_template` SET `mindmg` = '307', `maxdmg` = '438', `attackpower` = '314', `dmg_multiplier` = '7.5' WHERE `entry` IN (29216);
UPDATE `creature_template` SET `mindmg` = '422', `maxdmg` = '586', `attackpower` = '642', `dmg_multiplier` = '13' WHERE `entry` IN (31599);


-- ACID AZJOL NERUB

-- Do ROBIENIA
-- maski dla  kazdego moba
-- BOSS1 event 
-- Po Smierci zostawia chmure aoe
-- Skittering Infector 28736
-- missing aoe effect after deatch
-- Boss2 event
-- Anub'ar Crusher 28922
-- cpp

-- Azjol Nerub Mobs
-- NORMAL (28732,28733,28734,29062,29063,29064,29096,29097,29098,29117,29118,29128,29335,29340,29217,29216,28922);
-- HEROIC (31608,31605,31606,31589,31594,31601,31590,31595,31602,31591,31596,31604,31609,31587,31607,31599,31592);

-- Update EVENTAI
UPDATE `creature_template` SET `AIName` = 'EventAI', `Scriptname` = '' WHERE `entry` IN (28732,28733,28734,29062,29063,29064,29096,29097,29098,29117,29118,29128,29335,29340,29217,29216,28922);
-- DELETE EventAIScripts
DELETE FROM creature_ai_scripts WHERE creature_id IN 					(28732,28733,28734,29062,29063,29064,29096,29097,29098,29117,29118,29128,29335,29340,29217,29216,28922);

-- Anub'ar Crusher
INSERT INTO creature_ai_scripts VALUES (NULL, '28922', '0', '0', '100', '3', '5000', '8000','15000','20000', '11', '53318', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crusher - Cast Smash (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28922', '0', '0', '100', '5', '5000', '8000','15000','20000', '11', '59346', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crusher - Cast Smash (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28922', '0', '0', '100', '6', '10', '10','0','0', '11', '53801', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crusher - Cast Frenzy');

-- Anub'ar Venomancer
INSERT INTO creature_ai_scripts VALUES (NULL, '29217', '0', '0', '100', '3', '500', '500','4000','8000', '11', '53617', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Venomancer - Cast Poison Bolt (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29217', '0', '0', '100', '5', '500', '500','4000','8000', '11', '59359', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Venomancer - Cast Poison Bolt (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29217', '0', '0', '100', '3', '5000', '8000','10000','14000', '11', '53616', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Venomancer - Cast Poison Bolt Volley (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29217', '0', '0', '100', '5', '5000', '8000','10000','14000', '11', '59360', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Venomancer - Cast Poison Bolt Volley (Heroic)');

-- Anub'ar Guardian 
INSERT INTO creature_ai_scripts VALUES (NULL, '29216', '0', '0', '100', '3', '1000', '5000','5000','9000', '11', '53618', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Guardian - Cast SunderArmor (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29216', '0', '0', '100', '5', '1000', '5000','5000','9000', '11', '59350', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Guardian - Cast SunderArmor (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29216', '0', '0', '100', '7', '3000', '4000','4000','8000', '11', '52532', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Guardian - Cast Strike');

-- Anub'ar Warrior 
INSERT INTO creature_ai_scripts VALUES (NULL, '28732', '0', '0', '100', '7', '6000', '6000','11000','11000', '11', '49806', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Warrior - Cast Cleave');
INSERT INTO creature_ai_scripts VALUES (NULL, '28732', '0', '0', '100', '7', '3000', '5000','5000','7000', '11', '52532', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Warrior - Cast Strike');

-- Anub'ar Shadowcaster 
INSERT INTO creature_ai_scripts VALUES (NULL, '28733', '0', '0', '100', '3', '500', '500','2000','4000', '11', '52534', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Shadowcaster - Cast Shadow Bolt (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28733', '0', '0', '100', '5', '500', '500','2000','4000', '11', '59357', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Shadowcaster - Cast Shadow Bolt (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28733', '0', '0', '100', '3', '5000', '8000','11000','17000', '11', '52535', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Shadowcaster - Cast Shadow Nova (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '28733', '0', '0', '100', '5', '5000', '8000','11000','17000', '11', '59358', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Shadowcaster - Cast Shadow Nova (Heroic)');

-- Anub'ar Skirmisher
INSERT INTO creature_ai_scripts VALUES (NULL, '28734', '0', '0', '100', '7', '4000', '4000','8000','12000', '11', '52540', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Skirmisher - Cast Backstab');

-- Anub'ar Champion
INSERT INTO creature_ai_scripts VALUES (NULL, '29062', '0', '0', '100', '3', '8000', '14000','12000','14000', '11', '53394', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29062', '0', '0', '100', '5', '8000', '14000','12000','14000', '11', '59344', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29062', '0', '0', '100', '3', '4000', '6000','4000','6000', '11', '53317', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29062', '0', '0', '100', '5', '4000', '6000','4000','6000', '11', '59343', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Heroic)');

-- Anub'ar Crypt Fiend 
INSERT INTO creature_ai_scripts VALUES (NULL, '29063', '0', '0', '100', '3', '4000', '6000','7000','9000', '11', '53322', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29063', '0', '0', '100', '5', '4000', '6000','7000','9000', '11', '59347', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29063', '0', '0', '100', '3', '2000', '4000','15000','20000', '11', '53330', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29063', '0', '0', '100', '5', '2000', '4000','15000','20000', '11', '59348', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Heroic)');

-- Anub'ar Necromancer
INSERT INTO creature_ai_scripts VALUES (NULL, '29064', '0', '0', '100', '7', '8000', '16000','16000','24000', '11', '53334', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Necromancer - Cast Animate Bones');
INSERT INTO creature_ai_scripts VALUES (NULL, '29064', '0', '0', '100', '7', '500', '500','2000','4000', '11', '53333', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Necromancer - Cast Shadow Bolt');

-- Anub'ar Champion
INSERT INTO creature_ai_scripts VALUES (NULL, '29096', '0', '0', '100', '3', '8000', '14000','12000','14000', '11', '53394', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29096', '0', '0', '100', '5', '8000', '14000','12000','14000', '11', '59344', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29096', '0', '0', '100', '3', '4000', '6000','4000','6000', '11', '53317', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29096', '0', '0', '100', '5', '4000', '6000','4000','6000', '11', '59343', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Heroic)');

-- Anub'ar Crypt Fiend
INSERT INTO creature_ai_scripts VALUES (NULL, '29097', '0', '0', '100', '3', '4000', '6000','7000','9000', '11', '53322', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29097', '0', '0', '100', '5', '4000', '6000','7000','9000', '11', '59347', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29097', '0', '0', '100', '3', '2000', '4000','15000','20000', '11', '53330', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29097', '0', '0', '100', '5', '2000', '4000','15000','20000', '11', '59348', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Heroic)');

-- Anub'ar Necromancer
INSERT INTO creature_ai_scripts VALUES (NULL, '29098', '0', '0', '100', '7', '8000', '16000','16000','24000', '11', '53334', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Necromancer - Cast Animate Bones');
INSERT INTO creature_ai_scripts VALUES (NULL, '29098', '0', '0', '100', '7', '500', '500','2000','4000', '11', '53333', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Necromancer - Cast Shadow Bolt');

-- Anub'ar Champion
INSERT INTO creature_ai_scripts VALUES (NULL, '29117', '0', '0', '100', '3', '8000', '14000','12000','14000', '11', '53394', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29117', '0', '0', '100', '5', '8000', '14000','12000','14000', '11', '59344', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Pummel (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29117', '0', '0', '100', '3', '4000', '6000','4000','6000', '11', '53317', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29117', '0', '0', '100', '5', '4000', '6000','4000','6000', '11', '59343', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Champion - Cast Rend (Heroic)');

-- Anub'ar Crypt Fiend
INSERT INTO creature_ai_scripts VALUES (NULL, '29118', '0', '0', '100', '3', '4000', '6000','7000','9000', '11', '53322', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29118', '0', '0', '100', '5', '4000', '6000','7000','9000', '11', '59347', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Crushing Webs (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29118', '0', '0', '100', '3', '2000', '4000','15000','20000', '11', '53330', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29118', '0', '0', '100', '5', '2000', '4000','15000','20000', '11', '59348', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Crypt Fiend - Cast Infected Wounds (Heroic)');

-- Anub'ar Prime Guard 
INSERT INTO creature_ai_scripts VALUES (NULL, '29128', '0', '0', '100', '3', '3000', '5000','10000','16000', '11', '54314', '0', '3', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Prime Guard - Cast Drain Power (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29128', '0', '0', '100', '5', '3000', '5000','10000','16000', '11', '59354', '0', '3', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Prime Guard - Cast Drain Power (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29128', '0', '0', '100', '3', '6000', '9000','11000','11000', '11', '54309', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Prime Guard - Cast Mark Of Darkness (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29128', '0', '0', '100', '5', '6000', '9000','11000','11000', '11', '59352', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Prime Guard - Cast Mark Of Darkness (Heroic)');

-- Anub'ar Webspinner 
INSERT INTO creature_ai_scripts VALUES (NULL, '29335', '0', '0', '100', '3', '500', '500','2000','4000', '11', '54290', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Webspinner - Cast Web Shot (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29335', '0', '0', '100', '5', '500', '500','2000','4000', '11', '59362', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Webspinner - Cast Web Shot (Heroic)');
INSERT INTO creature_ai_scripts VALUES (NULL, '29335', '0', '0', '100', '7', '9000', '11000','9000','11000', '11', '52086', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Anub\'ar Webspinner - Cast Web Wrap');

-- Anub'ar Brood Keeper
-- 0 abilietes


