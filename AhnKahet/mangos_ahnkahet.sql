-- AHN KAHET

-- Nadox Taldaram Jedoga Volazi Amanitar
-- 29309,29308,29310,29311,30258
-- 31469,31456,31465,31464,31463


-- Ahn-Kahet::Taladram
UPDATE creature_template SET `AIName` = '', `mechanic_immune_mask` = '1073463287', `Scriptname` = 'boss_taldaram', `minmana` ='71220', `maxmana` ='71220' WHERE `entry` IN (29308);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `minmana` = '83380', `maxmana` = '83380' WHERE `entry` IN (31456);
DELETE FROM creature WHERE guid = '11652222';
INSERT INTO creature VALUES (11652222,29308,619,3,1,0,0,529.114,-848.099,11.3082,1.42479,25,0,0,458354,0,0,0);
-- Flame Sphere
UPDATE creature_template SET `minlevel` ='80', `maxlevel` = '80', `AIName` = '', `Scriptname` = 'mob_flame_sphere', `minmana` = '5000', `maxmana` = '5000' WHERE `entry` IN (30702);
-- DELETE FROM creature_ai_scripts WHERE creature_id IN (30702);
-- INSERT INTO creature_ai_scripts VALUES (NULL, '30702', '0', '0', '100', '3', '500', '500','3000','3000', '11', '57748', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flame Sphere - Cast FireBeam (Normal)');
-- INSERT INTO creature_ai_scripts VALUES (NULL, '30702', '0', '0', '100', '5', '500', '500','3000','3000', '11', '58938', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Flame Sphere - Cast FireBeam (Heroic)');


-- Ahn-Kahet::Jedoga
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `type_flags` = '0', `unit_flags` = '0', `AIName` = '', `Scriptname` = 'boss_jedoga' WHERE `entry` IN (29310);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `type_flags` = '0', `unit_flags` = '0' WHERE `entry` IN (31465);
-- Volounteer
UPDATE creature_template SET `AIName` = '', `type_flags` = '0', `unit_flags` = '0', `Scriptname` = 'mob_volounteer' WHERE `entry` IN (30385);
UPDATE creature_template SET `type_flags` = '0', `unit_flags` = '0' WHERE `entry` IN (31474);


-- Ahn-Kahet::Amanitar
DELETE FROM creature WHERE guid = '11651872';
INSERT INTO creature VALUES (11651872,30258,619,2,1,0,0,345.169,-869.813,-77.6156,6.03587,86400,0,0,431392,0,0,0);
UPDATE creature_template SET `minhealth` = '431392', `maxhealth` = '431392', `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_amanitar' WHERE `entry` IN (30258);
UPDATE creature_template SET `minhealth` = '431392', `maxhealth` = '431392', `mechanic_immune_mask` = '1073463287'  WHERE `entry` IN (31463);
-- Ahn-Kahet::Mushrooms
UPDATE creature_template SET `minhealth` = '150', `maxhealth` = '150', `AIName` = '', `Scriptname` = 'mob_healthymushroom' WHERE `entry` IN (30435);
UPDATE creature_template SET `minhealth` = '150', `maxhealth` = '150', `AIName` = '', `Scriptname` = 'mob_poisonmushroom' WHERE `entry` IN (30391);
UPDATE creature_template SET `minhealth` = '150', `maxhealth` = '150' WHERE `entry` IN (31461,31462);


-- Ahn-Kahet::Volazj2931131464
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `Scriptname` = 'boss_volazj' WHERE `entry` IN (29311);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287' WHERE `entry` IN (31464);
-- Ahn-Kahet::twisted Visage 30625
-- Insert heroic creature?
UPDATE creature_template SET `minhealth` = '4000', `maxhealth` = '4000' WHERE `entry` IN (30625);