-- Drop withcout badges and quest items need to be added soon

DELETE FROM creature_loot_template WHERE entry IN (30510,30532,30529,30540);

-- Nexus::Telestra normal loot id 26731
-- Nexus::Telestra hero loot id 30510
UPDATE creature_template SET `lootid` = '30510' WHERE `entry` IN (30510);
INSERT INTO `creature_loot_template` VALUES ('30510', '43852', '1.4', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30510', '37134', '12', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30510', '37139', '13', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30510', '37138', '13', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30510', '37135', '13', '0', '1', '1', '0', '0', '0');

-- Nexus::Ormorok normal loot id 26794
-- Nexus::Ormorok hero loot id 30532
UPDATE creature_template SET `lootid` = '30532' WHERE `entry` IN (30532);
INSERT INTO `creature_loot_template` VALUES ('30532', '43852', '1.4', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30532', '37153', '12', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30532', '37152', '12', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30532', '37155', '12', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30532', '37151', '13', '0', '1', '1', '0', '0', '0');

-- Nexus::Anomalus normal loot id 26763
-- Nexus::Anomalus hero loot id 30529
UPDATE creature_template SET `lootid` = '30529' WHERE `entry` IN (30529);
INSERT INTO `creature_loot_template` VALUES ('30529', '43852', '1.4', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30529', '37150', '13', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30529', '37149', '13', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30529', '37144', '13', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30529', '37141', '13', '0', '1', '1', '0', '0', '0');

-- Nexus::Kelistrasza normal loot id 26723
-- Nexus::Kelistrasza hero loot id 30540
UPDATE creature_template SET `lootid` = '30540' WHERE `entry` IN (30540);
INSERT INTO `creature_loot_template` VALUES ('30540', '43852', '1.4', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30540', '41794', '6', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30540', '37169', '10', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30540', '37166', '11', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30540', '37167', '11', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30540', '37165', '11', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30540', '37162', '11', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30540', '37170', '11', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30540', '37172', '11', '0', '1', '1', '0', '0', '0');
INSERT INTO `creature_loot_template` VALUES ('30540', '37171', '11', '0', '1', '1', '0', '0', '0');
