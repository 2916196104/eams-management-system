-- Change DataBase
USE `zo_eams`;
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- 员工
INSERT INTO `staff` VALUES (1, '管理员', 'admin', NULL, NULL, NULL, 1, NULL, NULL, 5, NULL, 1, 0, NULL, '2021-07-08', NULL, NULL, NULL, NULL, NULL, NULL, 0, '$2a$10$NEsrNyBIPGELx9DpIbm/x.VwAMOzhmX4cOfO4jzwRJf6XizYrxjI2', 120.00, 60.00, 1, 1);

-- 员工组织
INSERT INTO `staff_orginfo` VALUES (1, 1, 1, NULL, NULL, 1, 1, 0, '2022-04-22 16:19:54', 1, '1');

-- 角色
INSERT INTO `sys_role` VALUES (1, '超级管理员', 'superadmin');

-- 用户角色
INSERT INTO `sys_user_role` VALUES (1, '1', '1');

-- 系统权限
-- TODO 需要开发过程补充初始数据
-- INSERT INTO `sys_permission` VALUES (1, '教室管理', NULL, '/common/classroom/save', 'classroommanage', NULL, 1, '教务管理');

-- 角色权限
-- TODO 需要开发过程补充初始数据
-- INSERT INTO `sys_role_permission` VALUES (1, '1', '1');

SET FOREIGN_KEY_CHECKS = 1;