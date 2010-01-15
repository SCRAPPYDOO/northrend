-- AHN KAHET

-- Nadox Taldaram Jedoga Volazi Amanitar
-- 29309,29308,29310,29311,30258

-- 31469,31456,31465,31464,31463

-- Taladram norm/hero
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_taldaram', `minmana` ='71220', `maxmana` ='71220' WHERE `entry` IN (29308);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `minmana` = '83380', `maxmana` = '83380' WHERE `entry` IN (31456);

-- Flame Sphere
UPDATE creature_template SET `minlevel` ='80', `maxlevel` = '80', `AIName` = '', `Scriptname` = 'mob_flame_sphere', `minmana` = '5000', `maxmana` = '5000' WHERE `entry` IN (30702);
DELETE FROM creature_ai_scripts WHERE creature_id IN (30702);
INSERT INTO creature_ai_scripts VALUES (NULL, '30702', '0', '0', '100', '3', '500', '500','3000','3000', '11', '57748', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flame Sphere - Cast FireBeam (Normal)');
INSERT INTO creature_ai_scripts VALUES (NULL, '30702', '0', '0', '100', '5', '500', '500','3000','3000', '11', '58938', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flame Sphere - Cast FireBeam (Heroic)');

-- spawn time map mask and other to add
DELETE FROM creature WHERE guid = '131951';
INSERT INTO creature VALUES (131951,29308,619,1,1,0,1780,528.644,-844.815,11.3081,4.9049,25,0,0,212700,71220,0,0);