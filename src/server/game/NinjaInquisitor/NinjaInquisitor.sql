

DROP TABLE IF EXISTS `ninja_inquisitor_logs`;

CREATE TABLE `ninja_inquisitor_logs` (
    `time` INT UNSIGNED NOT NULL,
    `instance` INT UNSIGNED NOT NULL,
    `guid` INT UNSIGNED NOT NULL,
    `event` TEXT NOT NULL
) ENGINE=MyISAM;
