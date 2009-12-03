-- SpectralRift
UPDATE gameobject_template SET `type` = '22', `data0` = '0', `data3` = '1', `data6` = '0', `data10` = '0', `ScriptName` = 'kalecgos_teleporter' WHERE `entry` IN (187055);
-- Scriptnames KalecgosEvent
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_kalecgos' WHERE `entry` IN (24850); 
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_sathrovarr' WHERE `entry` IN  (24892);
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_kalec' WHERE `entry` IN (24891);

UPDATE creature_template SET `minhealth` = '3700000', `maxhealth` = '3700000' WHERE `entry` IN (24850, 24892);

-- Felmyst add immune to taunt
UPDATE creature_template SET `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_felmyst' WHERE `entry` IN (25038); 

UPDATE creature_template SET `minlevel` = '70', `maxlevel` = '70',`ScriptName` = 'mob_felmyst_vapor' WHERE `entry` IN (25265); 

UPDATE creature_template SET `ScriptName` = 'mob_felmyst_trail' WHERE `entry` IN (25267); 

UPDATE creature_template SET `ScriptName` = 'mob_deathcloud' WHERE `entry` IN (25703); 

-- Muru Event
-- Muru and Entropius
UPDATE `creature_template` SET `lootid` = '25840', `mingold` = '2250000', `maxgold` = '2750000', `minhealth` = '5200000', `maxhealth` = '5200000', `mechanic_immune_mask` = '1073463287', `ScriptName` = 'boss_muru' WHERE `entry` IN (25741);

-- Dark Fiend
UPDATE `creature_template` SET `faction_A` = '14', `faction_H` = '14', `speed` = '1', `ScriptName` = 'dark_fiend' WHERE `entry` IN (25744); 

-- Void Sentinel
UPDATE `creature_template` SET `mechanic_immune_mask` = '1073463287', `AIName` = '', `ScriptName` = 'mob_voidsentinel' WHERE `entry` IN (25772); 
UPDATE `creature_template` SET `minmana` = '10000', `maxmana` = '10000' WHERE `entry` IN (25798, 25772);

-- Singularity
UPDATE creature_template SET `faction_A` = '14', `faction_H` = '14', `speed` = '1', `rank` = '1', `AIName` = '', `ScriptName` = 'mob_singularity' WHERE `entry` IN (25855); 
