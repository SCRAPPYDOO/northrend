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