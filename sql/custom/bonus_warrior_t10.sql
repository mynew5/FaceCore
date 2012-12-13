-- Fix [Warrior] T10 4P Bonus.
-- Slam
DELETE FROM spell_script_names WHERE spell_id = 46916;
INSERT INTO spell_script_names VALUES (46916,'spell_warr_slam');
-- Execute
DELETE FROM spell_script_names WHERE spell_id = 52437;
INSERT INTO spell_script_names VALUES (52437,'spell_warr_execute_bonus');