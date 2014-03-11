/* add rbac permissions to new commands */
DELETE FROM `rbac_permissions` WHERE `id` IN (1002,1003,1004,1005);
INSERT INTO `rbac_permissions` (`id`,`name`) VALUES
(1002,'Command: qc'),
(1003,'Command: qc complete'),
(1004,'Command: qc add'),
(1005,'Command: qc del'),

/* adds qc to players */
DELETE FROM `rbac_linked_permissions` WHERE `id` IN (1002,1003,1004,1005);
INSERT INTO `rbac_linked_permissions` (`id`,`linkedId`) VALUES
(195, 1002),
/* adds qc status to players */
(195, 1003), 
/* adds qc add to GMs */
(192, 1004),
/* adds qc del to GMs */
(192, 1005),
