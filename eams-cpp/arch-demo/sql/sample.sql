SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for sample
-- ----------------------------
DROP TABLE IF EXISTS `sample`;
CREATE TABLE `sample`  (
  `id` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '唯一标识',
  #`name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '姓名',
  #`sex` char(1) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '性别',
 # `age` int NULL DEFAULT NULL COMMENT '年龄',
  #`create_by` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '创建人',
  #`create_time` datetime NULL DEFAULT NULL COMMENT '创建时间',
  `update_by` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '修改人',
  `update_time` datetime NULL DEFAULT NULL COMMENT '修改时间',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '演示示例表' ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Table structure for sample_address
-- ----------------------------
DROP TABLE IF EXISTS `sample_address`;
CREATE TABLE `sample_address`  (
  `id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '唯一标识',
  `user_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '用户唯一标识',
  #`contact` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '联系人',
  #`phone` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '联系电话',
  #`province` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '省份',
#  `city` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '城市',
  #`country` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '区县',
  #`address` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '详细地址',
 # `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '备注信息',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci COMMENT = '用户收货地址' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for sample_file
-- ----------------------------
DROP TABLE IF EXISTS `sample_file`;
CREATE TABLE `sample_file`  (
  `id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '唯一标识',
#  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '文件名称',
 # `file_type` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '文件类型编码，存储字典项表中的code',
 # `save_type` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '文件存储方式编码，存储字典项表中的code',
 # `save_path` varchar(5000) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '文件存储路径，不要将服务器域名和端口存储到数据库',
 # `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '备注',
 # `status` int NOT NULL DEFAULT 1 COMMENT '数据状态 0 未使用 1使用中',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci COMMENT = '示例文件' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for sample_user
-- ----------------------------
DROP TABLE IF EXISTS `sample_user`;
CREATE TABLE `sample_user`  (
  `id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '唯一标识',
  #`nickname` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '昵称',
 # `age` int NULL DEFAULT NULL COMMENT '年龄',
#  `id_card` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '身份证号',
 # `avatar` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '头像，存储文件表的文件唯一ID',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci COMMENT = '示例用户表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Table structure for sample_dict
-- ----------------------------
DROP TABLE IF EXISTS `sample_dict`;
CREATE TABLE `sample_dict`  (
  `id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '唯一标识',
 # `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '字典类型名称',
 # `code` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '字典类型编码',
 # `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '备注',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `uq_code`(`code` ASC) USING BTREE COMMENT '字段类型编码唯一约束'
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci COMMENT = '示例字典类型' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of sample_dict
-- ----------------------------
INSERT INTO `sample_dict` VALUES ('61f3bbc90b904b51890448968afc106f', '文件类型', 'file_type', NULL);
INSERT INTO `sample_dict` VALUES ('f42afd7d846248528fe72d62c01e9d1e', '文件存储方式', 'save_way', NULL);

-- ----------------------------
-- Table structure for sample_dict_item
-- ----------------------------
DROP TABLE IF EXISTS `sample_dict_item`;
CREATE TABLE `sample_dict_item`  (
  `id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '唯一标识',
  #`dict_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '所属字典类型编号',
  #`name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '字典项名称',
  #`code` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '字典项编码',
  #`remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '备注',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci COMMENT = '示例字典项' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of sample_dict_item
-- ----------------------------
INSERT INTO `sample_dict_item` VALUES ('029f4d8bbb014530bbc18df89ae1bc36', '61f3bbc90b904b51890448968afc106f', '用户头像', '10002', NULL);
INSERT INTO `sample_dict_item` VALUES ('07cd9e35e50746c4817523c8d4cc046a', 'f42afd7d846248528fe72d62c01e9d1e', 'fastdfs', '10002', 'FastDfs分布式存储');
INSERT INTO `sample_dict_item` VALUES ('2e2f4fd8dbe64bdc96b879c8f5d927e5', 'f42afd7d846248528fe72d62c01e9d1e', 'disk', '10004', '业务服务器磁盘存储');
INSERT INTO `sample_dict_item` VALUES ('4b8891f629c24b099bb11f3b444ae82c', 'f42afd7d846248528fe72d62c01e9d1e', 'oss', '10003', '阿里云对象存储');
INSERT INTO `sample_dict_item` VALUES ('b9112f5abc544150a32f19767f8c0816', 'f42afd7d846248528fe72d62c01e9d1e', 'ftp', '10001', '普通文件服务器');
INSERT INTO `sample_dict_item` VALUES ('e3b89e8b9bea4ea2bf501b8e932ab29c', '61f3bbc90b904b51890448968afc106f', '合同附件', '10003', NULL);
INSERT INTO `sample_dict_item` VALUES ('e4d9a2ff1fbb4d8e86060e7e4374bba4', '61f3bbc90b904b51890448968afc106f', '用户照片', '10001', NULL);

-- ----------------------------
-- Table structure for sample_menu
-- ----------------------------
DROP TABLE IF EXISTS `sample_menu`;
CREATE TABLE `sample_menu`  (
  `id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '唯一标识',
  `text` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '菜单名称',
  `icon` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '菜单图标',
  `href` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '路由地址',
  `parent_id` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL COMMENT '父菜单编号',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci COMMENT = '示例菜单表' ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of sample_menu
-- ----------------------------
INSERT INTO `sample_menu` VALUES ('0a4283fa0cbe4eeab5c4506a10d500e5', '出库订单', 'om', '/om/om', 'b18725e6dcaf45dd9a7e5585f6a5c2fd');
INSERT INTO `sample_menu` VALUES ('1cf1ad84951f4f4fbb38511136815b64', '订单报表', 'om', '/om/sm/t2', '5048defa193a40688ca66cbf189f84e5');
INSERT INTO `sample_menu` VALUES ('5048defa193a40688ca66cbf189f84e5', '销售订单', 'om', '/om/sm', 'b18725e6dcaf45dd9a7e5585f6a5c2fd');
INSERT INTO `sample_menu` VALUES ('52836d0e08c0460fa10105366f76b38b', '角色管理', 'sm', '/sm/rm', '543e3df57cfa459a8c24e83e023c47f7');
INSERT INTO `sample_menu` VALUES ('543e3df57cfa459a8c24e83e023c47f7', '系统管理', 'sm', '/sm', NULL);
INSERT INTO `sample_menu` VALUES ('8001741829cd402fb7045401f71c46da', '用户管理', 'sm', '/sm/um', '543e3df57cfa459a8c24e83e023c47f7');
INSERT INTO `sample_menu` VALUES ('96b285d470be4402b8467f21aee0c3ff', '入库订单', 'om', '/om/em', 'b18725e6dcaf45dd9a7e5585f6a5c2fd');
INSERT INTO `sample_menu` VALUES ('b18725e6dcaf45dd9a7e5585f6a5c2fd', '订单管理', 'om', '/om', NULL);
INSERT INTO `sample_menu` VALUES ('e01b2ceea43a41e1bd9d3af4a8f655a7', '订单统计', 'om', '/om/sm/t1', '5048defa193a40688ca66cbf189f84e5');
INSERT INTO `sample_menu` VALUES ('f21704cf254142f3a8e7a742a8df50da', '菜单管理', 'sm', '/sm/mm', '543e3df57cfa459a8c24e83e023c47f7');

SET FOREIGN_KEY_CHECKS = 1;
