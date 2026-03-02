-- Change DataBase
USE `zo_eams`;
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- dict type
INSERT INTO `dict` VALUES (1, '客户来源', 'customer_source', '录入学员时的选项', 1);
INSERT INTO `dict` VALUES (2, '请款类型', 'cashout_type', '请款申请时的选项', 2);
INSERT INTO `dict` VALUES (3, '退款类型', 'refund_type', '退款类型选项', 3);
INSERT INTO `dict` VALUES (4, '积分商城分类', 'credit_mall_category', '积分商城礼品分类', 4);
INSERT INTO `dict` VALUES (5, '物料分类', 'material_category', '物料分类', 5);

-- dict item
INSERT INTO `dict_item` VALUES (1, 1, '微信登记', NULL, 0);
INSERT INTO `dict_item` VALUES (2, 1, '活动报名', NULL, 0);
INSERT INTO `dict_item` VALUES (3, 1, '主动咨询', NULL, 0);
INSERT INTO `dict_item` VALUES (4, 1, '抖音平台', NULL, 0);
INSERT INTO `dict_item` VALUES (5, 2, '广告宣传', NULL, 0);
INSERT INTO `dict_item` VALUES (6, 2, '物业费', NULL, 0);
INSERT INTO `dict_item` VALUES (7, 2, '办公耗材', NULL, 0);
INSERT INTO `dict_item` VALUES (8, 2, '水费', NULL, 0);
INSERT INTO `dict_item` VALUES (9, 2, '差旅费', NULL, 0);
INSERT INTO `dict_item` VALUES (10, 2, '其他', NULL, 0);
INSERT INTO `dict_item` VALUES (11, 3, '课程选错买错', NULL, 1);
INSERT INTO `dict_item` VALUES (12, 3, '买多了', NULL, 0);
INSERT INTO `dict_item` VALUES (13, 3, '性价比不好', NULL, 0);
INSERT INTO `dict_item` VALUES (14, 3, '其他原因', NULL, 0);
INSERT INTO `dict_item` VALUES (15, 4, '学习用品', NULL, 0);
INSERT INTO `dict_item` VALUES (16, 4, '玩具', NULL, 0);
INSERT INTO `dict_item` VALUES (17, 4, '书籍', NULL, 0);
INSERT INTO `dict_item` VALUES (18, 4, '花', NULL, 0);
INSERT INTO `dict_item` VALUES (19, 5, '办公耗材', '非常耐造', 0);
INSERT INTO `dict_item` VALUES (20, 5, '电脑', '非常耐造', 0);
INSERT INTO `dict_item` VALUES (21, 5, '办公桌椅', NULL, 0);

SET FOREIGN_KEY_CHECKS = 1;