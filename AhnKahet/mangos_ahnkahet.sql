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


-- Jedoga 29310
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `type_flags` = '0', `unit_flags` = '0', `AIName` = '', `Scriptname` = 'boss_jedoga' WHERE `entry` IN (29310);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `type_flags` = '0', `unit_flags` = '0' WHERE `entry` IN (31465);

-- Volounteer
UPDATE creature_template SET `AIName` = '', `type_flags` = '0', `unit_flags` = '0', `Scriptname` = 'mob_volounteer' WHERE `entry` IN (30385);
UPDATE creature_template SET `type_flags` = '0', `unit_flags` = '0' WHERE `entry` IN (31474);