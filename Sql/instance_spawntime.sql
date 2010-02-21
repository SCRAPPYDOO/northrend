-- Instance Boss Spawn Time from 1h to 1d
-- Utgarde Keep
UPDATE creature SET `spawntimesecs` = '86400' WHERE id IN (23953,24200,24201,23954);
-- Nexus
UPDATE creature SET `spawntimesecs` = '86400' WHERE id IN (26731,26763,26794,26723);
-- Azjol Nerub
UPDATE creature SET `spawntimesecs` = '86400' WHERE id IN (28684,28921,29120);
-- AhnKahet
UPDATE creature SET `spawntimesecs` = '86400' WHERE id IN (29309,29308,29310,30258,29311);
-- Halls Of Lighting
UPDATE creature SET `spawntimesecs` = '86400' WHERE id IN (28586,28587,28546,28923);
-- Utgarde Pinnacle
UPDATE creature SET `spawntimesecs` = '86400' WHERE id IN (26668,26687,26693,26861);
