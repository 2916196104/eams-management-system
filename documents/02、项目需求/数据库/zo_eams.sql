-- Create DataBase
DROP DATABASE IF EXISTS `zo_eams`;
CREATE DATABASE `zo_eams`;

-- Change DataBase
USE `zo_eams`;
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

CREATE TABLE `advertisement`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '发送标题',
  `type` tinyint(4) NOT NULL DEFAULT 1 COMMENT '类型 学生端首页Banner  学生端首页提示  学生端首页弹窗',
  `content` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '发送内容',
  `cover` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '逻辑删除',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑者',
  `state` tinyint(1) NULL DEFAULT 1 COMMENT '状态',
  `sort_num` int(11) NULL DEFAULT 0,
  `code` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '唯一码',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `code`(`code`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '通知管理' ;

CREATE TABLE `appointment`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `lesson_id` bigint(20) UNSIGNED NOT NULL COMMENT '试听课次',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学员id',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '预约时间',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `verify_state` tinyint(2) NULL DEFAULT 1 COMMENT '审核状态',
  `verify_time` datetime(0) NULL DEFAULT NULL COMMENT '审核时间',
  `verify_staff` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '审核人',
  `verify_remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '审核内容',
  `course_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属课程',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生所属学校ID',
  `counselor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生的顾问',
  `trial_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '体验卡id 来自于体验卡的预约有',
  `trial_record_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '消费体验卡领取记录id',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE,
  INDEX `lesson_id`(`lesson_id`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '预约记录' ;

CREATE TABLE `attachment`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `file_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '文件原名',
  `file_size` int(11) NOT NULL COMMENT '附件大小',
  `file_type` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '附件类型',
  `name` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '附件名称',
  `url` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '附件地址',
  `save_path` varchar(200) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '保存路径',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建时间',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `url`(`url`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '附件管理表' ;

CREATE TABLE `cashout`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '请款项目名',
  `type` tinyint(4) NOT NULL COMMENT '请款类型',
  `amount` decimal(11, 2) NOT NULL COMMENT '请款金额',
  `payee_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '收款人',
  `account` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '收款账号',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '请款信息',
  `verify_state` tinyint(4) NULL DEFAULT NULL COMMENT '审批状态',
  `verify_staff` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '审核人',
  `verify_time` datetime(0) NULL DEFAULT NULL COMMENT '审核时间',
  `verify_remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '审核备注',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '申请人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `attach_file` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '附件id列表',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '样本' ;

CREATE TABLE `class`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '班级名',
  `course_id` bigint(20) UNSIGNED NOT NULL COMMENT '课程',
  `classroom_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '教室',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑者',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `teacher_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '班级负责人',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '排课备注',
  `be_over` tinyint(1) NULL DEFAULT 0 COMMENT '是否完结',
  `over_time` datetime(0) NULL DEFAULT NULL COMMENT '完结时间',
  `over_operator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '完结操作人',
  `start_date` date NULL DEFAULT NULL COMMENT '计划开班日期',
  `end_date` date NULL DEFAULT NULL COMMENT '计划结业日期',
  `planned_student_count` int(11) NULL DEFAULT 0 COMMENT '预招人数',
  `planned_lesson_count` int(11) NULL DEFAULT NULL COMMENT '预排课次数',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属学校id',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  `grade_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '年级ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `course_id`(`course_id`) USING BTREE,
  INDEX `teacher_id`(`teacher_id`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '班级' ;

CREATE TABLE `class_grade`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '年级名称',
  `year` int(4) NOT NULL COMMENT '入学年份',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `sort_num` int(11) NULL DEFAULT 0 COMMENT '排序',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '年级表' ;

CREATE TABLE `class_student`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `class_id` bigint(20) UNSIGNED NOT NULL COMMENT '班级id',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生id',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `reason` tinyint(4) NULL DEFAULT NULL COMMENT '加入原因',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注信息',
  `consume_course_id` bigint(20) UNSIGNED NOT NULL COMMENT '默认消费课程',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `class_id`(`class_id`, `student_id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '班级学员表' ;

CREATE TABLE `classroom`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '教室名',
  `address` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '位置',
  `area` int(10) NULL DEFAULT NULL COMMENT '面积平方米',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑者',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属学校ID',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '教室' ;

CREATE TABLE `contact_record`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生id',
  `info` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '跟进记录',
  `contact_time` datetime(0) NOT NULL COMMENT '联系时间',
  `contact_next_time` datetime(0) NULL DEFAULT NULL COMMENT '下次联系时间',
  `contact_type` tinyint(4) NULL DEFAULT NULL COMMENT '联系方式',
  `contact_phone` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '联系电话',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '时间',
  `stage` tinyint(4) NOT NULL COMMENT '进展阶段',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE,
  INDEX `stage`(`stage`, `deleted`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '学员跟进表' ;

CREATE TABLE `course`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `subject_id` bigint(11) UNSIGNED NOT NULL COMMENT '科目id',
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '课程名',
  `state` tinyint(4) NULL DEFAULT 1 COMMENT '启用状态',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '提示信息',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑者',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
  `expire_months` tinyint(4) UNSIGNED NULL DEFAULT 12 COMMENT '有效期月数',
  `unit_price` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '单价',
  `price` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '总价 销售价',
  `unit_name` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT '次' COMMENT '单位名称',
  `discount` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '优惠金额 取绝对值',
  `lesson_count` int(11) UNSIGNED NULL DEFAULT NULL COMMENT '课次数',
  `lesson_type` tinyint(4) NULL DEFAULT NULL COMMENT '课堂类型1 大课  2 小班课 3 1v1',
  `description` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '描述',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `bookable` tinyint(1) NULL DEFAULT 0 COMMENT '是否可以预约',
  `for_sale` tinyint(1) NULL DEFAULT 0 COMMENT '是否上架中',
  `recommend` tinyint(1) NULL DEFAULT 0 COMMENT '是否推荐',
  `cover` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '封面',
  `close_date` date NULL DEFAULT NULL COMMENT '报名截止日期',
  `teacher_info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '师资信息',
  `service_info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '服务说明',
  `storage` int(11) NULL DEFAULT 0 COMMENT '库存名额',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  `salary` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '消课课酬(元/课)',
  `grade_ids` varchar(500) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '适用年级',
  `grade_names` varchar(500) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '适用年级名',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `subject_id`(`subject_id`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '课程套餐表' ;

CREATE TABLE `course_comment`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `course_id` bigint(20) UNSIGNED NOT NULL COMMENT '所属课程',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生id',
  `order_id` bigint(20) NULL DEFAULT NULL COMMENT '订单id',
  `content` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '章节标题',
  `score` tinyint(4) NULL DEFAULT 5 COMMENT '打分',
  `state` tinyint(1) NULL DEFAULT 0 COMMENT '发布状态',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `course_id`(`course_id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '课程评价' ;

CREATE TABLE `course_image`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `course_id` bigint(20) UNSIGNED NOT NULL COMMENT '所属课程',
  `image_url` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '图片地址',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '课程介绍图片' ;

CREATE TABLE `course_link`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `course_id` bigint(20) UNSIGNED NOT NULL COMMENT '课程id',
  `linked_id` bigint(20) UNSIGNED NOT NULL COMMENT '关联课程id',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `course_id`(`course_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '课程关联表' ;

CREATE TABLE `course_section`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `course_id` bigint(20) UNSIGNED NOT NULL COMMENT '所属课程',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '章节标题',
  `lesson_count` int(10) NOT NULL COMMENT '计划课时数',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '课程大纲' ;

CREATE TABLE `course_trial`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `course_id` bigint(20) UNSIGNED NOT NULL COMMENT '课程',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '名称',
  `quantity` int(11) NOT NULL DEFAULT 0 COMMENT '发行数量',
  `remaining_quantity` int(11) NULL DEFAULT NULL COMMENT '剩余数量',
  `lesson_count` int(11) UNSIGNED NOT NULL DEFAULT 0 COMMENT '课时数',
  `expire_days` int(11) NOT NULL COMMENT '领取后有效天数',
  `end_date` date NOT NULL COMMENT '发行结束日期',
  `state` tinyint(1) NULL DEFAULT 1 COMMENT '启用状态',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `course_id`(`course_id`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '课程体验卡' ;

CREATE TABLE `course_trial_record`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `trial_id` bigint(20) UNSIGNED NOT NULL COMMENT '卡ID',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生ID',
  `course_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '课程ID',
  `user_id` bigint(20) NULL DEFAULT NULL COMMENT '学生账号id',
  `student_course_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '生成的学生课程关联ID',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '领取时间',
  `expired_date` date NULL DEFAULT NULL COMMENT '到期时间',
  `lesson_count` int(11) NULL DEFAULT NULL COMMENT '领取到数量预约后减少',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生所属学校ID',
  `counselor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生的顾问',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '课程体验卡领取记录' ;

CREATE TABLE `credit_exchange`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `credit_mall_id` bigint(20) UNSIGNED NOT NULL COMMENT '积分商城礼品id',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学校id',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生id',
  `user_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生账号id',
  `num` int(11) NOT NULL COMMENT '兑换数量',
  `credit` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '花费积分',
  `verify_state` tinyint(4) NULL DEFAULT 1 COMMENT '审核状态',
  `verify_staff` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '审核人',
  `verify_time` datetime(0) NULL DEFAULT NULL COMMENT '审核时间',
  `verify_remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '审核备注',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE,
  INDEX `credit_mall_id`(`credit_mall_id`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '积分商城兑换记录' ;

CREATE TABLE `credit_mall`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属学校',
  `material_id` bigint(20) UNSIGNED NOT NULL COMMENT '物料分类',
  `category_id` bigint(20) UNSIGNED NOT NULL COMMENT '礼品分类ID',
  `category_name` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '分类名称',
  `name` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '礼品名称',
  `credit` int(11) NULL DEFAULT NULL COMMENT '兑换积分',
  `state` tinyint(1) NULL DEFAULT 1 COMMENT '是否可以兑换',
  `sale_num` int(10) UNSIGNED NULL DEFAULT 0 COMMENT '历史兑换数量',
  `view_num` int(10) UNSIGNED NULL DEFAULT 0 COMMENT '预览次数',
  `cover` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  `content` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '详情内容',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `material_id`(`material_id`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '积分商城礼品表' ;

CREATE TABLE `data_permission`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `position_id` bigint(20) UNSIGNED NOT NULL COMMENT '岗位id',
  `scope_type` tinyint(4) NULL DEFAULT 0 COMMENT '权限类型',
  `entity_name` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '表名(可重复)',
  `owner_field` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL DEFAULT 'creator' COMMENT '数据所有人字段名',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `owner_org_field` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '数据所有组织字段名',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `table_name`(`position_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '数据权限' ;

CREATE TABLE `data_permission_custom`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `permission_id` bigint(20) UNSIGNED NOT NULL COMMENT '权限id',
  `position_id` bigint(20) UNSIGNED NOT NULL COMMENT '岗位id',
  `org_id` bigint(20) UNSIGNED NOT NULL DEFAULT 0 COMMENT '机构id',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `table_name`(`permission_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '数据权限自定义设置' ;

CREATE TABLE `dict`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '组名',
  `code` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '编码',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '信息',
  `sort_num` int(11) NULL DEFAULT 0 COMMENT '排序',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `code`(`code`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '系统设置表' ;

CREATE TABLE `dict_item`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `dict_id` bigint(20) UNSIGNED NOT NULL COMMENT '组id',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '名称',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '说明',
  `sort_num` int(11) NULL DEFAULT 0 COMMENT '排序',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `dict_id`(`dict_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '系统设置表' ;

CREATE TABLE `finance_record`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '标题',
  `amount` decimal(11, 2) NULL DEFAULT NULL COMMENT '金额,退款为负数',
  `item_type` tinyint(4) NULL DEFAULT NULL COMMENT '收入项类型',
  `item_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '项目id',
  `operator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '经办人id',
  `payer` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '付款人id',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '款项备注',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '经办日期',
  `verify_state` tinyint(4) NULL DEFAULT NULL COMMENT '审核确认状态',
  `verify_staff` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '审核人',
  `verify_time` datetime(0) NULL DEFAULT NULL COMMENT '审核时间',
  `verify_remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '审核备注',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `operator`(`operator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '财务记录表' ;

CREATE TABLE `grade`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '成绩项目标题',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '成绩项目说明',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '逻辑删除',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑者',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '成绩单' ;

CREATE TABLE `grade_record`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `grade_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '考核项id',
  `student_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生id',
  `score` tinyint(4) NULL DEFAULT 0 COMMENT '分数',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '添加人',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE,
  INDEX `grade_id`(`grade_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '成绩单学生分数' ;

CREATE TABLE `help`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '发送标题',
  `content` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '发送内容',
  `type` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '类型',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '逻辑删除',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑者',
  `state` tinyint(1) NULL DEFAULT 1 COMMENT '状态',
  `sort_num` int(11) NULL DEFAULT 0 COMMENT '排序',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '使用帮助' ;

CREATE TABLE `holiday`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `date` date NOT NULL,
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '节假日设置' ;

CREATE TABLE `homework`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `class_id` bigint(20) UNSIGNED NOT NULL COMMENT '班级ID',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '标题',
  `content` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '内容',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `class_id`(`class_id`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '作业' ;

CREATE TABLE `homework_record`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `homework_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属作业',
  `student_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生名',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '时间',
  `content` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '内容',
  `score` tinyint(4) NULL DEFAULT 0 COMMENT '点评分数',
  `comment` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '点评',
  `comment_time` datetime(0) NULL DEFAULT NULL COMMENT '点评时间',
  `comment_teacher` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '点评老师',
  `images` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `homework_id`(`homework_id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '作业提交记录' ;

CREATE TABLE `lesson`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '课程标题',
  `sn` int(10) NULL DEFAULT 1 COMMENT '课节数 第几节课',
  `course_id` bigint(20) UNSIGNED NOT NULL COMMENT '课程id',
  `schedule_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编排计划id',
  `class_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '班级id',
  `room_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '教室id',
  `date` date NULL DEFAULT NULL COMMENT '上课日期',
  `start_time` time(0) NULL DEFAULT NULL COMMENT '开始时间',
  `end_time` time(0) NULL DEFAULT NULL COMMENT '结束时间',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑者',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `dec_count` tinyint(4) UNSIGNED NULL DEFAULT 1 COMMENT '应扣课次数',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `teach_type` tinyint(2) NULL DEFAULT 1 COMMENT '授课方式',
  `on_trial` tinyint(1) NULL DEFAULT 0 COMMENT '是否开启试听',
  `trial_result` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '试听结果',
  `state` tinyint(2) NULL DEFAULT 1 COMMENT '课次状态',
  `close_time` datetime(0) NULL DEFAULT NULL COMMENT '结课时间',
  `close_operator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '结课人',
  `teacher_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '主讲人(只用于数据权限)',
  `bookable` tinyint(1) NULL DEFAULT 0 COMMENT '是否开放预约',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '老师所属学校ID',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `course_id`(`course_id`, `deleted`) USING BTREE,
  INDEX `class_id`(`class_id`, `deleted`) USING BTREE,
  INDEX `date`(`date`, `start_time`) USING BTREE,
  INDEX `state_2`(`state`, `end_time`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '课程表' ;

CREATE TABLE `lesson_schedule`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `class_id` bigint(20) UNSIGNED NOT NULL COMMENT '班级id',
  `course_id` bigint(20) UNSIGNED NOT NULL COMMENT '课程id',
  `teacher_ids` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '上课老师',
  `assistant_ids` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '助教',
  `start_date` date NOT NULL COMMENT '开始日期',
  `end_date` date NOT NULL COMMENT '结束日期',
  `dec_lesson_count` tinyint(4) UNSIGNED NOT NULL DEFAULT 1 COMMENT '学员扣课次数',
  `times` int(11) NULL DEFAULT NULL COMMENT '排课次数',
  `exclude_holiday` tinyint(1) NULL DEFAULT 0 COMMENT '排除节日',
  `state` tinyint(1) NULL DEFAULT 0 COMMENT '是否生成课表',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑者',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `conflict_ids` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '冲突的id列表 空字符表示无冲突 null是未检查',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `course_id`(`course_id`, `deleted`) USING BTREE,
  INDEX `class_id`(`class_id`, `deleted`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '排课计划' ;

CREATE TABLE `lesson_schedule_setting`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `schedule_id` bigint(20) UNSIGNED NOT NULL COMMENT '编排计划id',
  `weeks` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '星期',
  `start_time` time(0) NOT NULL COMMENT '开始时间',
  `end_time` time(0) NOT NULL COMMENT '结束时间',
  `room_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '教室ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `schedule_id`(`schedule_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '编排上课时间设置' ;

CREATE TABLE `lesson_student`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `lesson_id` bigint(20) UNSIGNED NOT NULL COMMENT '课程id',
  `class_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '班级id为空表示调课生',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学员id',
  `dec_lesson_count` int(11) NULL DEFAULT 0 COMMENT '实扣课次',
  `lesson_count` int(11) NULL DEFAULT 0 COMMENT '应扣课次',
  `teacher_id` bigint(11) UNSIGNED NULL DEFAULT NULL COMMENT '点名的老师',
  `sign_time` datetime(0) NULL DEFAULT NULL COMMENT '签到时间',
  `sign_type` tinyint(4) NULL DEFAULT NULL COMMENT '签到方式',
  `sign_state` tinyint(4) NULL DEFAULT 0 COMMENT '签到结果',
  `score` tinyint(4) NULL DEFAULT NULL COMMENT '老师评分',
  `evaluation` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '老师评语',
  `evaluate_time` datetime(0) NULL DEFAULT NULL COMMENT '评语时间',
  `evaluate_teacher` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '评语老师',
  `consume_course_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '实际消费课程',
  `consume_student_course_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '消费课程与学生关联表ID',
  `counselor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生的顾问',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '加入时间',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '上课老师所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `lesson_id_student_id`(`lesson_id`, `student_id`) USING BTREE,
  INDEX `teacher_id`(`teacher_id`) USING BTREE,
  INDEX `counselor`(`counselor`) USING BTREE,
  INDEX `student_id`(`student_id`, `sign_state`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '课时学员关联表' ;

CREATE TABLE `lesson_teacher`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `lesson_id` bigint(20) UNSIGNED NOT NULL COMMENT '课程id',
  `teacher_id` bigint(20) UNSIGNED NOT NULL COMMENT '学员id',
  `commission` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '课时费',
  `type_num` tinyint(4) NOT NULL COMMENT '1上课老师2助教',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `lesson_id`(`lesson_id`, `teacher_id`) USING BTREE,
  INDEX `teacher_id`(`teacher_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '课时老师关联表' ;

CREATE TABLE `material`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `school_id` bigint(20) UNSIGNED NOT NULL COMMENT '所属学校',
  `category_id` bigint(20) UNSIGNED NOT NULL COMMENT '所属分类ID',
  `category_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '分类名',
  `name` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '物料名称',
  `storage` int(11) NULL DEFAULT 0 COMMENT '库存量',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '物料说明',
  `cover` varchar(200) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '封面图',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `state` tinyint(1) NULL DEFAULT 1 COMMENT '启用状态',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '物料表' ;

CREATE TABLE `material_record`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `material_id` bigint(20) UNSIGNED NOT NULL COMMENT '物料ID',
  `amount` int(11) NULL DEFAULT NULL COMMENT '变动数量',
  `reason` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '变动原因说明',
  `change_type` tinyint(4) NULL DEFAULT NULL COMMENT '变动类型1入库2出库3积分商城出库 ',
  `change_target_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '变动对象id如积分商城里的商品id',
  `remark` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注信息',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '变动时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `student_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '涉及学生id',
  `staff_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '涉及员工id',
  `org_id` bigint(20) NULL DEFAULT NULL COMMENT '所属物料的组织ID',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学校id',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '物料出入库记录' ;

CREATE TABLE `message`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '发送标题',
  `content` varchar(500) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '发送内容',
  `to_id` bigint(20) UNSIGNED NOT NULL COMMENT '接收人ID 0所有',
  `from_id` bigint(20) UNSIGNED NOT NULL DEFAULT 0 COMMENT '发送人ID',
  `to_type` tinyint(4) NULL DEFAULT NULL COMMENT '接受者类型  1 老师 2 学生',
  `from_type` tinyint(4) NULL DEFAULT NULL COMMENT '发送者类型 0 系统 1 老师 2 学生',
  `send_time` datetime(0) NULL DEFAULT NULL COMMENT '发送时间',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者',
  `deleted` tinyint(1) NULL DEFAULT NULL COMMENT '删除标记',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '站内信' ;

CREATE TABLE `notice`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT 'id',
  `title` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '公告标题',
  `content` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '公告内容',
  `view_num` int(11) NULL DEFAULT 0,
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '公告' ;

CREATE TABLE `operation_record`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `type` tinyint(4) NOT NULL DEFAULT 1 COMMENT '类型',
  `item_id` bigint(20) UNSIGNED NOT NULL COMMENT '审核对象',
  `state` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT '0' COMMENT '审核状态',
  `content` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '审核备注',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '审核人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '处理时间',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '审核操作记录' ;

CREATE TABLE `org`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `pid` bigint(20) UNSIGNED NULL DEFAULT 0 COMMENT '上级公司',
  `name` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '公司名称',
  `state` tinyint(1) NULL DEFAULT 1 COMMENT '是否有效',
  `shortname` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '公司简称',
  `type` tinyint(4) NULL DEFAULT 0 COMMENT '类型',
  `level` tinyint(4) NOT NULL COMMENT '级别1集团总部2分校3部门',
  `id_path` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '路径',
  `name_path` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '机构名路径',
  `contact_name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '联系人',
  `phone` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '联系电话',
  `fax` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '传真',
  `email` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT 'Email',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '描述',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `province` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '省',
  `city` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '市',
  `district` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '区',
  `address` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '地址',
  `sort_num` int(11) NULL DEFAULT 0 COMMENT '排序',
  `license` varchar(80) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '营业执照',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `pid`(`pid`, `deleted`) USING BTREE,
  INDEX `id_path`(`id_path`(250)) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '机构表' ;

CREATE TABLE `point_record`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生id',
  `point` int(11) NOT NULL COMMENT '变动积分',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '变动时间',
  `stage` tinyint(4) NOT NULL COMMENT '变动阶段',
  `balance` int(11) NULL DEFAULT NULL COMMENT '剩余积分',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '详细信息',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '积分记录' ;

CREATE TABLE `position`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '职务id',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '职位岗位' ;

CREATE TABLE `quartz_job`  (
  `id` bigint UNSIGNED NOT NULL  COMMENT '主键',
  `job_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '任务名称',
  `group_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '任务分组',
  `job_class` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '执行类路径',
  `status` tinyint(1) NULL DEFAULT 1 COMMENT '状态',
  `cron_expression` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT 'cron表达式',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '定时任务' ;

CREATE TABLE `refund`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `student_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生id',
  `student_course_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生课程关联表id',
  `operator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '退费办理人',
  `refund_amount` decimal(10, 2) NULL DEFAULT NULL COMMENT '退费金额 负数',
  `refund_lesson_count` int(11) NULL DEFAULT NULL COMMENT '退费课时',
  `apply_time` datetime(0) NULL DEFAULT NULL COMMENT '退费发起时间',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '退费说明',
  `done_time` datetime(0) NULL DEFAULT NULL COMMENT '退费办完时间',
  `type_num` tinyint(4) NULL DEFAULT 1 COMMENT '类型',
  `verify_state` tinyint(4) NULL DEFAULT 1 COMMENT '退款状态',
  `verify_time` datetime(0) NULL DEFAULT NULL COMMENT '审核时间',
  `verify_staff` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '审核人',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `student_course_id`(`student_course_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '学员退款记录' ;

CREATE TABLE `region`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `pid` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '父id',
  `short_name` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '简称',
  `name` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '名称',
  `merger_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '全称',
  `level` tinyint(2) NULL DEFAULT NULL COMMENT '层级 0 1 2 省市区县',
  `pinyin` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '拼音',
  `code` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '长途区号',
  `zip_code` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '邮编',
  `first` varchar(10) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '首字母',
  `lng` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '经度',
  `lat` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '纬度',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `pinyin`(`pinyin`) USING BTREE,
  INDEX `pid`(`pid`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '省市地区表' ;

CREATE TABLE `setting`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '组名',
  `code` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '编码',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '信息',
  `sort_num` int(11) NULL DEFAULT 0 COMMENT '排序',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `code`(`code`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '系统设置表' ;

CREATE TABLE `setting_notice`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '名称',
  `code` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '码',
  `wx_on` tinyint(1) NULL DEFAULT 0 COMMENT '微信是否开启',
  `wx_code` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '微信模板',
  `sms_on` tinyint(1) NULL DEFAULT 0 COMMENT '短信是否开启',
  `sms_code` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '短信模板',
  `email_on` tinyint(1) NULL DEFAULT NULL COMMENT 'Email是否开启',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '说明',
  `sort_num` int(11) NULL DEFAULT 0 COMMENT '排序',
  `group_code` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '分组',
  `params` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '参数说明',
  `notice_remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '消息备注信息',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `code`(`code`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '系统设置表' ;

CREATE TABLE `setting_option`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `setting_id` bigint(20) UNSIGNED NOT NULL COMMENT '组id',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '名称',
  `code` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '码',
  `value` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '值',
  `value_type` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT 'str' COMMENT '值数据类型',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '说明',
  `sort_num` int(11) NULL DEFAULT 0 COMMENT '排序',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `code`(`code`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '系统设置表' ;

CREATE TABLE `shop_order`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `sn` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '订单号',
  `user_id` bigint(20) UNSIGNED NOT NULL COMMENT '用户',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生id',
  `order_money` decimal(10, 2) NOT NULL COMMENT '订单金额',
  `pay_money` decimal(10, 2) NULL DEFAULT NULL COMMENT '支付金额',
  `state` tinyint(4) NOT NULL DEFAULT 0 COMMENT '订单状态',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `pay_time` datetime(0) NULL DEFAULT NULL COMMENT '支付时间',
  `cancel_time` datetime(0) NULL DEFAULT NULL COMMENT '取消时间',
  `refunded` tinyint(1) NULL DEFAULT 0 COMMENT '是否已退款',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生所在学校的id',
  `counselor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生的顾问',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `sn`(`sn`) USING BTREE,
  INDEX `student_id`(`student_id`, `state`) USING BTREE,
  INDEX `state`(`state`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '订单' ;

CREATE TABLE `shop_order_item`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `order_id` bigint(50) UNSIGNED NOT NULL COMMENT '订单号',
  `item_id` bigint(20) UNSIGNED NOT NULL COMMENT '课程id',
  `item_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '名称',
  `item_type` tinyint(4) NULL DEFAULT NULL COMMENT '购买物品类型 1 课程',
  `price` decimal(10, 2) NULL DEFAULT NULL COMMENT '购买价格',
  `quantity` int(10) UNSIGNED NULL DEFAULT NULL COMMENT '购买数量',
  `cover` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '图片',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `item_id`(`item_id`, `item_type`, `order_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '订单关联物品列表' ;

CREATE TABLE `shop_order_refund`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `refund_sn` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '退款编号',
  `order_id` bigint(20) UNSIGNED NOT NULL COMMENT '订单id',
  `user_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生端账号id',
  `student_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生id',
  `item_names` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '物品名称',
  `refund_money` decimal(10, 2) UNSIGNED NOT NULL COMMENT '退款金额',
  `reason_type` tinyint(4) NULL DEFAULT NULL COMMENT '原因类型',
  `reason` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '原因描述',
  `state` tinyint(4) NOT NULL COMMENT '状态',
  `verify_staff` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '审核人',
  `verify_time` datetime(0) NULL DEFAULT NULL COMMENT '审核时间',
  `verify_remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '审核备注',
  `wx_refund_id` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '微信退款id',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '申请时间',
  `operator_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '执行退款人ID',
  `operation_time` datetime(0) NULL DEFAULT NULL COMMENT '执行退款时间',
  `operator_name` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '执行退款人姓名',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属order的学校ID',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `sn`(`refund_sn`) USING BTREE,
  INDEX `user_id`(`user_id`) USING BTREE,
  INDEX `bill_id`(`order_id`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '订单退款记录';

CREATE TABLE `shop_payment`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `order_id` bigint(20) UNSIGNED NOT NULL COMMENT '订单id',
  `user_id` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '手机端账号id',
  `order_sn` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '订单编号',
  `wx_trade_id` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '微信交易号',
  `wx_openid` varchar(64) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '微信支付者openid',
  `pay_money` decimal(11, 2) NOT NULL COMMENT '支付金额',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '支付记录表' ;

CREATE TABLE `staff`  (
  `id` bigint(20) UNSIGNED NOT NULL ,
  `name` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '姓名',
  `mobile` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '手机号',
  `wx_access_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '微信登录id',
  `email` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT 'EMAIL',
  `birthday` date NULL DEFAULT NULL COMMENT '生日',
  `gender` tinyint(2) NULL DEFAULT 0 COMMENT '性别',
  `id_card` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '身份证',
  `school` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '毕业学校',
  `degree` tinyint(2) NULL DEFAULT NULL COMMENT '学历',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `state` tinyint(2) NULL DEFAULT 1 COMMENT '在职状态',
  `is_manager` tinyint(1) NULL DEFAULT 0 COMMENT '是否是管理者',
  `head_img` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '头像',
  `hire_date` date NULL DEFAULT NULL COMMENT '入职日期',
  `fire_date` date NULL DEFAULT NULL COMMENT '离职日期',
  `intro` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '介绍',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '创建时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '是否删除',
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '密码',
  `class_fee` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '课时费',
  `assistant_fee` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '助教费',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT 'STAFF所属组织ID',
  `is_inner` tinyint(1) NULL DEFAULT 1 COMMENT '是否内部人员',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `mobile`(`mobile`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '教师员工表' ;

CREATE TABLE `staff_orginfo`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `staff_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '员工id',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属机构',
  `group_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属集团',
  `com_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属公司',
  `dpt_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属部门',
  `position_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属职位',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `add_time` datetime(0) NULL DEFAULT NULL,
  `creator` bigint(255) UNSIGNED NULL DEFAULT NULL,
  `id_path` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT 'id全路径',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `staff_id`(`staff_id`, `org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '员工机构信息表' ;

CREATE TABLE `staff_position`  (
  `id` bigint(20) UNSIGNED NOT NULL ,
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '职位名称',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑者',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '职位表' ;

CREATE TABLE `student`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `user_id` bigint(20) UNSIGNED NOT NULL COMMENT '家长id',
  `family_rel` tinyint(4) NULL DEFAULT 0 COMMENT '家庭关系',
  `as_default` tinyint(1) NULL DEFAULT 1 COMMENT '家长默认查看的学员',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属分校',
  `name` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '姓名',
  `deleted` int(1) NULL DEFAULT 0 COMMENT '逻辑删除',
  `stage` tinyint(2) NULL DEFAULT NULL COMMENT '阶段状态0意向学员',
  `gender` tinyint(2) NULL DEFAULT 0 COMMENT '性别',
  `birthday` date NULL DEFAULT NULL COMMENT '生日',
  `head_img` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '头像',
  `join_way` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '加入方式',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `graduation_date` date NULL DEFAULT NULL COMMENT '结业日期',
  `graduation_reason` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '结业原因',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '加入时间',
  `counselor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '顾问',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `idcard` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '身份证号',
  `redpoint_grade` datetime(0) NULL DEFAULT NULL COMMENT '红点标记成绩最后查看时间',
  `redpoint_evaluate` datetime(0) NULL DEFAULT NULL COMMENT '红点标记点评最后查看时间',
  `grade` year NULL DEFAULT NULL COMMENT '入学年份',
  `join_date` date NULL DEFAULT NULL COMMENT '入学日期',
  `wx_access_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '微信登录记录id',
  `credit` bigint(20) UNSIGNED NULL DEFAULT 0 COMMENT '学生积分',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  `grade_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '年级ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `stage`(`stage`) USING BTREE,
  INDEX `name`(`name`) USING BTREE,
  INDEX `mobile`(`user_id`) USING BTREE,
  INDEX `counselor`(`counselor`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '学生表' ;

CREATE TABLE `student_course`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生id',
  `course_id` bigint(20) UNSIGNED NOT NULL COMMENT '课程d',
  `subject_id` bigint(20) UNSIGNED NOT NULL COMMENT '科目id',
  `start_date` date NULL DEFAULT NULL COMMENT '开始时间',
  `expire_date` date NULL DEFAULT NULL COMMENT '过期日期',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `count_lesson_total` int(10) NULL DEFAULT 0 COMMENT '购买总课次',
  `count_lesson_complete` int(10) NULL DEFAULT 0 COMMENT '已上课次',
  `count_lesson_refund` int(10) NULL DEFAULT 0 COMMENT '退款次数',
  `course_amount` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '套餐金额',
  `discount_amount` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '优惠金额',
  `amount` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '成交/合约金额',
  `paid_amount` decimal(10, 2) UNSIGNED NULL DEFAULT NULL COMMENT '实付金额',
  `pay_off` tinyint(1) NULL DEFAULT NULL COMMENT '是否付清 0 否1是',
  `operator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '经手人',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '录入时间',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `verify_state` tinyint(4) NULL DEFAULT 1 COMMENT '审核状态',
  `warning_times` tinyint(4) NULL DEFAULT 0 COMMENT '不足时已提醒次数',
  `priority` tinyint(4) NULL DEFAULT 1 COMMENT '消课优先级',
  `unit_price` decimal(10, 2) NULL DEFAULT NULL COMMENT '单价',
  `from_trial` tinyint(1) NULL DEFAULT 0 COMMENT '是否来自于体验试用',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '报名老师所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `course_id`(`course_id`) USING BTREE,
  INDEX `student_id`(`student_id`, `course_id`, `expire_date`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '报名签约表' ;

CREATE TABLE `student_credit_log`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生id',
  `user_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生账号id',
  `credit` bigint(20) UNSIGNED NOT NULL COMMENT '变动数量',
  `current_credit` int(11) NULL DEFAULT NULL COMMENT '剩余积分数量',
  `change_type` tinyint(4) NULL DEFAULT NULL COMMENT '变动类型',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '变动时间',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '其他说明',
  `source_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '记录来源id',
  `staff_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '调整人',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生所属学校ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '学生积分变动记录' ;

CREATE TABLE `student_leave`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '请假时间',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学生外键',
  `lesson_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '请假课程外键',
  `reason` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '原因',
  `state` tinyint(4) NULL DEFAULT 1 COMMENT '状态',
  `verify_staff` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '取消操作人',
  `verify_time` datetime(0) NULL DEFAULT NULL COMMENT '取消时间',
  `counselor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生的顾问',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生所属学校ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE,
  INDEX `lesson_id`(`lesson_id`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '学员请假' ;

CREATE TABLE `student_lesson_count_log`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学员id',
  `course_id` bigint(20) UNSIGNED NOT NULL COMMENT '课程id',
  `lesson_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '课次id',
  `change_count` int(11) NULL DEFAULT NULL COMMENT '变更课次数',
  `remaining_count` int(11) NULL DEFAULT NULL COMMENT '剩余数量',
  `staff_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '操作人',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '时间',
  `stage` tinyint(4) NULL DEFAULT NULL COMMENT '变更阶段',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE,
  INDEX `course_id`(`course_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '学员课次变更记录表' ;

CREATE TABLE `subject`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '科目',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '简介',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建人',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑者',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '新增时间',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '修改时间',
  `deleted` tinyint(1) NULL DEFAULT 0 COMMENT '删除标记',
  `sort_num` int(11) NULL DEFAULT 0 COMMENT '排序值',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '科目' ;

CREATE TABLE `sys_log`  (
  `id` bigint(20) UNSIGNED NOT NULL  COMMENT '主键',
  `operator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '操作人',
  `student_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生id',
  `type` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '类型',
  `info` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '信息',
  `path` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '路径',
  `url` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '请求地址',
  `method` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '请求方法',
  `param` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '参数',
  `ip` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT 'IP地址',
  `browser_name` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '浏览器名',
  `browser_ver` varchar(30) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '浏览器版本',
  `os_name` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '系统名称',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '日志时间',
  `time_cost` int(10) NULL DEFAULT NULL COMMENT '响应时间毫秒',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `operator`(`operator`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '系统用户日志' ;

CREATE TABLE `sys_permission`  (
  `id` bigint UNSIGNED NOT NULL COMMENT '主键',
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '' COMMENT '菜单名称',
  `parent_id` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT '' COMMENT '父类id',
  `url` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `code` varchar(50) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `path` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  `enabled` smallint(1) NOT NULL DEFAULT 1 COMMENT '是否启用 1 启用，0 禁用',
  `group_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '分组',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '权限' ;

CREATE TABLE `sys_role`  (
  `id` bigint UNSIGNED NOT NULL COMMENT '主键',
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '角色名称',
  `code` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '角色编码',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `code`(`code`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '角色' ;

CREATE TABLE `sys_role_permission`  (
  `id` bigint UNSIGNED NOT NULL COMMENT '主键',
  `role_id` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '角色id',
  `permission_id` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '菜单id',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `permission_id`(`permission_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '角色权限' ;

CREATE TABLE `sys_user_role`  (
  `id` bigint UNSIGNED NOT NULL COMMENT '主键',
  `user_id` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '用户id',
  `role_id` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL DEFAULT '' COMMENT '角色id',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8 COLLATE = utf8_general_ci COMMENT = '用户角色' ;

CREATE TABLE `teach_evaluation`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `lesson_id` bigint(20) UNSIGNED NOT NULL COMMENT '课次id',
  `teacher_id` bigint(20) UNSIGNED NOT NULL COMMENT '老师id',
  `score1` tinyint(4) NULL DEFAULT NULL COMMENT '综合评分',
  `score2` tinyint(4) NULL DEFAULT NULL COMMENT '课堂气氛',
  `score3` tinyint(4) NULL DEFAULT NULL COMMENT '授课态度',
  `score4` tinyint(4) NULL DEFAULT NULL COMMENT '教学效果',
  `content` text CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '评语',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '评价时间',
  `student_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生id',
  `anonymity` tinyint(1) NULL DEFAULT 0 COMMENT '是否匿名',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '被评价老师所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `lesson_id`(`lesson_id`, `student_id`) USING BTREE,
  INDEX `teacher_id`(`teacher_id`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '学评教' ;

CREATE TABLE `trial_appointment`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '主键',
  `lesson_id` bigint(20) UNSIGNED NOT NULL COMMENT '试听课次',
  `student_id` bigint(20) UNSIGNED NOT NULL COMMENT '学员id',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '预约时间',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `verify_state` tinyint(2) NULL DEFAULT 1 COMMENT '审核状态',
  `verify_time` datetime(0) NULL DEFAULT NULL COMMENT '审核时间',
  `verify_staff` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '审核人',
  `verify_remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '审核内容',
  `course_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属课程',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生所属学校ID',
  `counselor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '学生的顾问',
  PRIMARY KEY (`id`) USING BTREE,
  INDEX `student_id`(`student_id`) USING BTREE,
  INDEX `lesson_id`(`lesson_id`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '试听预约记录' ;

CREATE TABLE `user`  (
  `id` bigint(20) UNSIGNED NOT NULL COMMENT '用户主键',
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '家长姓名',
  `wx_access_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '微信id',
  `mobile` varchar(11) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '手机号账号',
  `email` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT 'email',
  `state` tinyint(1) NULL DEFAULT 1 COMMENT '账号状态',
  `password` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '密码',
  `login_times` int(11) NULL DEFAULT 0 COMMENT '登录次数',
  `latest_login_time` datetime(0) NULL DEFAULT NULL COMMENT '上次登录时间',
  `latest_login_ip` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '上次登录ip',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '加入时间',
  `remark` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '备注',
  `creator` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '添加者',
  `school_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '所属学校id',
  `org_id` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '创建者所属组织ID',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `mobile`(`mobile`) USING BTREE,
  INDEX `creator`(`creator`) USING BTREE,
  INDEX `school_id`(`school_id`) USING BTREE,
  INDEX `org_id`(`org_id`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '家长端用户表' ;

CREATE TABLE `wx_access`  (
  `id` bigint(11) UNSIGNED NOT NULL  COMMENT '主键',
  `openid` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '微信openid',
  `unionid` varchar(100) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '微信unionid',
  `nickname` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT '' COMMENT '昵称',
  `add_time` datetime(0) NULL DEFAULT NULL COMMENT '添加时间',
  `latest_login` datetime(0) NULL DEFAULT NULL COMMENT '最后登录时间',
  `unsubscribe` tinyint(1) NULL DEFAULT 0 COMMENT '是否取消关注',
  `head_img` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '头像',
  `unsub_time` datetime(0) NULL DEFAULT NULL COMMENT '取消关注事件',
  `gender` tinyint(4) NULL DEFAULT 0 COMMENT '取消关注时间',
  `city` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '城市',
  `province` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '身份',
  `country` varchar(30) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL COMMENT '国家',
  `reg_from` varchar(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT 'wx' COMMENT '通过什么注册的 mp 公众号 miniapp 小程序',
  PRIMARY KEY (`id`) USING BTREE,
  UNIQUE INDEX `openid`(`openid`) USING BTREE
) ENGINE = InnoDB  CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '微信登录记录表' ;

CREATE TABLE `wx_menu`  (
  `id` bigint UNSIGNED NOT NULL COMMENT '不自增主键',
  `pid` bigint UNSIGNED NOT NULL COMMENT '上级id',
  `name` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NOT NULL COMMENT '菜单名',
  `url` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '菜单URL',
  `type` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '菜单类型',
  `key_code` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '事件KEY',
  `appid` varchar(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '小程序APPID',
  `pagepath` varchar(255) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '小程序页面地址',
  `media_id` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '素材media_id',
  `article_id` varchar(100) CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL DEFAULT NULL COMMENT '文章article_id',
  `send_text` mediumtext CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci NULL COMMENT '发送文字',
  `editor` bigint(20) UNSIGNED NULL DEFAULT NULL COMMENT '编辑人',
  `edit_time` datetime(0) NULL DEFAULT NULL COMMENT '编辑时间',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci COMMENT = '微信菜单设置' ;

SET FOREIGN_KEY_CHECKS = 1;
