DROP TABLE IF EXISTS `debugauthhack_reports`;
CREATE TABLE `debugauthhack_reports` (
  `event_time` INT UNSIGNED NOT NULL,
  `author_ip` VARCHAR(16),
  `report` TEXT
);
