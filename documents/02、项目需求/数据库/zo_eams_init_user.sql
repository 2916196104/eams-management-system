-- Change DataBase
USE `zo_eams`;

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

INSERT INTO `advertisement` VALUES (1, '正式上线', 1, '正式上线通知', 'http://erp2.hzb-it.com/static/banner1.png', 1, '2021-10-10 00:43:04', 1, '2022-07-22 22:12:20', 1, 1, 0, NULL);
INSERT INTO `advertisement` VALUES (2, '用户隐私协议', 0, '1', NULL, 1, '2022-06-13 15:18:38', 1, '2022-11-07 16:45:38', 1, 1, 0, 'term');

INSERT INTO `help` VALUES (1, '庆祝测试版本上线', '帮助内容', 'student', 3, '2021-07-26 22:21:29', 0, '2021-07-29 14:53:14', 3, 1, 0);

INSERT INTO `notice` VALUES (1, '新版上线公告', '<p>使用中有任何建议请咨询电话或微信：15666323771</p>\n<p>新版本号v1.0.1012</p>', 0, NULL, NULL, '2021-09-02 12:23:18', '2021-10-12 13:39:58', 0);
INSERT INTO `notice` VALUES (2, '新标题', '<p><img class=\"wscnph\" src=\"http://localhost:8106/app/static/uploads/2021-10-16/f678e32e-cb18-4250-912c-75b00cdeab72.jpg\" /></p>', 0, 1, 1, '2021-10-16 20:14:02', '2021-10-16 20:14:07', 0);

INSERT INTO `org` VALUES (2, 1, '西安路校区', 1, '', 0, 3, '1,2', '学校总部 西安路校区', '', '', '', '', '', 1, 1, '2021-10-09 23:55:23', '2022-04-21 22:35:52', 0, NULL, NULL, NULL, NULL, 6, NULL);
INSERT INTO `org` VALUES (3, 1, '高新园校区', 1, NULL, 0, 2, '1,3', '学校总部 高新园校区', NULL, NULL, NULL, NULL, NULL, 1, 1, '2021-10-09 23:54:55', '2023-06-21 14:41:25', 0, NULL, NULL, NULL, NULL, 0, NULL);

INSERT INTO `position` VALUES (2, '财务总监', NULL, NULL, NULL, NULL, 0);
INSERT INTO `position` VALUES (3, '中级教师', NULL, NULL, NULL, NULL, 0);
INSERT INTO `position` VALUES (4, '初级教师', NULL, NULL, NULL, NULL, 0);
INSERT INTO `position` VALUES (5, '教授', NULL, NULL, NULL, NULL, 0);
INSERT INTO `position` VALUES (6, '助教', NULL, NULL, NULL, NULL, 0);

INSERT INTO `staff` VALUES (2, '张三', 'zhangsan', NULL, NULL, NULL, 1, NULL, '', 0, NULL, 1, 0, NULL, NULL, NULL, '', '2021-10-10 00:45:38', '2022-04-22 16:21:08', 1, 1, 0, '$2a$10$7P43YrmBFLYJKX4donZR9.slZeTVrYpFOkHzCk3y6zhk9A4ruSbWW', NULL, NULL, NULL, 1);
INSERT INTO `staff_orginfo` VALUES (2, 2, 1, NULL, NULL, 1, 4, 0, '2022-04-22 16:21:08', 1, '1');

INSERT INTO `sys_role` VALUES (2, '教务专员', 'jwzy');
INSERT INTO `sys_user_role` VALUES (2, '2', '1');

INSERT INTO `subject` VALUES (1, '美术', NULL, 1, 1, '2022-01-28 16:49:40', '2026-01-17 15:11:47', 0, 1, NULL);
INSERT INTO `subject` VALUES (2, '音乐', NULL, 1, 1, '2022-01-28 16:49:45', '2026-01-17 15:12:14', 0, 1, NULL);
INSERT INTO `subject` VALUES (3, '信息', NULL, 1, 1, '2021-12-04 20:18:23', '2026-01-17 15:11:08', 0, 5, NULL);
INSERT INTO `subject` VALUES (4, '古筝', NULL, 1, 1, '2021-12-05 16:59:33', '2026-01-17 15:08:05', 0, 1, NULL);
INSERT INTO `subject` VALUES (5, '历史', NULL, 1, 1, '2022-01-28 16:49:01', '2026-01-17 15:10:32', 0, 4, NULL);
INSERT INTO `subject` VALUES (6, '英语', NULL, 1, 1, '2021-10-19 12:00:28', '2026-01-17 15:09:10', 0, 2, NULL);
INSERT INTO `subject` VALUES (7, '语文', NULL, 1, 1, '2021-11-02 16:01:50', '2026-01-17 15:09:04', 0, 2, NULL);
INSERT INTO `subject` VALUES (8, '数学', NULL, 1, 1, '2021-12-09 21:23:59', '2026-01-17 15:09:20', 0, 2, NULL);
INSERT INTO `subject` VALUES (9, '体育', NULL, 1, 1, '2022-01-28 16:49:31', '2026-01-17 15:12:50', 0, 1, NULL);
INSERT INTO `subject` VALUES (10, '物理', NULL, 1, 1, '2021-12-09 21:26:34', '2026-01-17 15:09:55', 0, 3, NULL);
INSERT INTO `subject` VALUES (11, '化学', NULL, 1, 1, '2021-12-09 21:26:44', '2026-01-17 15:10:02', 0, 3, NULL);
INSERT INTO `subject` VALUES (12, '政治', NULL, 1, 1, '2021-11-02 16:03:06', '2026-01-17 15:10:52', 0, 4, NULL);
INSERT INTO `subject` VALUES (13, '钢琴', NULL, 1, 1, '2022-05-11 12:22:59', '2026-01-17 15:08:27', 0, 1, NULL);
INSERT INTO `subject` VALUES (14, '劳技', NULL, 1, 1, '2022-01-28 16:49:50', '2026-01-17 15:11:54', 0, 1, NULL);
INSERT INTO `subject` VALUES (15, '生物', NULL, 1, 1, '2022-03-23 09:53:56', '2026-01-17 15:10:13', 0, 3, NULL);
INSERT INTO `subject` VALUES (16, '地理', NULL, 1, 1, '2022-03-23 09:54:05', '2026-01-17 15:10:41', 0, 4, NULL);
INSERT INTO `subject` VALUES (17, '书法', '分为硬笔和软笔', 1, 1, '2022-05-27 14:11:07', '2026-01-17 15:08:41', 0, 1, NULL);
INSERT INTO `subject` VALUES (18, '体能', NULL, 1, 1, '2022-06-30 15:00:17', '2026-01-17 15:11:33', 0, 1, NULL);

SET FOREIGN_KEY_CHECKS = 1;
