
DROP TABLE IF EXISTS `realmd`.`ninja_inquisitor_logs`;

CREATE TABLE `realmd`.`ninja_inquisitor_logs` (
    `time` INT UNSIGNED NOT NULL,
    `instance` INT UNSIGNED NOT NULL,
    `guid` INT UNSIGNED NOT NULL,
    `event` TEXT NOT NULL
) ENGINE=MyISAM;

DROP TRIGGER IF EXISTS `characters`.`ninja_inquisitor_delete`;

DELIMITER $$

CREATE TRIGGER `characters`.`ninja_inquisitor_delete` BEFORE DELETE ON `characters`.`instance` FOR EACH ROW
BEGIN
    DELETE FROM `realmd`.`ninja_inquisitor_logs` WHERE `instance` = `old`.`id`;
END$$

DELIMITER ;
