-- Change DataBase
USE `zo_eams`;
SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- 组织结构
INSERT INTO `org` VALUES (1, 0, '学校总部', 1, NULL, 0, 1, '1', '学校总部', NULL, NULL, NULL, NULL, NULL, 1, 1, NULL, NULL, 0, NULL, NULL, NULL, NULL, 0, NULL);

-- 职位岗位
INSERT INTO `position` VALUES (1, '校长', NULL, NULL, NULL, NULL, 0);

-- 系统设置类型
INSERT INTO `setting` VALUES (1, '系统设置', 'normal_setting', NULL, 0);
INSERT INTO `setting` VALUES (2, '课时设置', 'lesson_setting', NULL, 0);
INSERT INTO `setting` VALUES (3, '短信设置', 'sms_setting', NULL, 0);
INSERT INTO `setting` VALUES (4, '微信公众号设置', 'wx_mp_setting', NULL, 0);
INSERT INTO `setting` VALUES (5, '关于我们', 'about_us', NULL, 0);

-- 系统设置项值
INSERT INTO `setting_option` VALUES (100, 1, '班级结业时班内学员自动结业', 'class_close_with_graduate_student', 'false', 'bool', '如果学员课次有余量的则不会自动结业', 0);
INSERT INTO `setting_option` VALUES (101, 1, '报单1V1课程时自动生成班级', 'class_auto_create_on_one2one', 'true', 'bool', NULL, 0);
INSERT INTO `setting_option` VALUES (102, 1, '家长端初始密码', 'student_default_pwd', '111111', 'str', '添加学生时的默认登录密码', 0);
INSERT INTO `setting_option` VALUES (103, 1, '学员预约后自动入课', 'auto_join_lesson_by_appointment', 'true', 'bool', '管理端可以取消预约', 0);
INSERT INTO `setting_option` VALUES (104, 1, '体验卡使用规则说明', 'course_trial_help', '企鹅范文反问我', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (105, 1, '新订单默认提醒账号', 'order_notice_mobile', 'admin', 'str', '学员在线购课后，若无顾问则通知该账号。', 0);
INSERT INTO `setting_option` VALUES (106, 1, '在线支付后可申请退款的小时数(0表示不限制)', 'order_refund_limit_hour', '0', 'int', '在线支付后可申请退款的小时数(0表示不限制)', 0);
INSERT INTO `setting_option` VALUES (107, 1, '积分兑换说明', 'credit_mall_help', '积分兑换礼品后，不可取消，请确认礼品；因库存影响或有礼品不足导致随机发放；详情咨询店内老师。', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (108, 1, '是否脱敏学生的手机号码', 'student_mobile_marker_switch', 'true', 'bool', '为保护客户资源，开启后手机号码将被脱敏处理。', 0);
INSERT INTO `setting_option` VALUES (109, 1, '学生请假额外提醒账号', 'student_leave_notify_mobile', 'admin', 'str', '学生请假后，会额外提醒该账号', 0);
INSERT INTO `setting_option` VALUES (200, 2, '课次数不足预警数量', 'lesson_count_less_warning_count', '1', 'int', '课次不足时可以按设置给学员和负责老师发通知', 0);
INSERT INTO `setting_option` VALUES (201, 2, '课次数不足提醒次数', 'lesson_count_less_warning_times', '2', 'int', NULL, 0);
INSERT INTO `setting_option` VALUES (202, 2, '次日上课提醒时间', 'lesson_remind_time', '19:50', 'time', NULL, 0);
INSERT INTO `setting_option` VALUES (203, 2, '每天课次数不足预警时间', 'lesson_count_warning_time', '15:44', 'time', '课次不足时可以按设置给学员和负责老师发通知', 0);
INSERT INTO `setting_option` VALUES (204, 2, '学生端开启签到功能', 'student_center_can_sign', 'true', 'bool', '关闭后只能在管理端通过老师点名消课', 0);
INSERT INTO `setting_option` VALUES (205, 2, '学生端可签到全天的课', 'student_can_sign_whole_day', 'false', 'bool', '学生端开启签到功能才生效', 0);
INSERT INTO `setting_option` VALUES (206, 2, '默认点名旷课时是否扣课时', 'decrease_lesson_when_absence', 'true', 'bool', NULL, 0);
INSERT INTO `setting_option` VALUES (207, 2, '学生在上课前多少小时可以请假', 'student_leave_limit_hour', '2', 'int', '学生在上课前多少小时可以请假(0表示上课前都可以)', 0);
INSERT INTO `setting_option` VALUES (208, 2, '老师在上课前多少小时可点名', 'teacher_sign_limit_before_lesson', '0', 'int', '留空表示不限制', 0);
INSERT INTO `setting_option` VALUES (209, 2, '老师在下课后多少小时可点名', 'teacher_sign_limit_after_lesson', '0', 'int', '留空表示不限制', 0);
INSERT INTO `setting_option` VALUES (300, 3, '短信接口KEY', 'sms_access_key', 'w', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (301, 3, '短信接口秘钥', 'sms_access_secret', NULL, 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (302, 3, '短信签名', 'sms_sign_name', '宏之博', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (303, 3, '验证码短信模板ID', 'sms_code_template', 'SMS_223835183、', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (400, 4, '公众号AppId', 'wx_mp_app_id', 'appid', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (401, 4, '公众号Secret', 'wx_mp_secret', 'd3a', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (402, 4, '公众号Token', 'wx_mp_token', 'iop【34与或576ure', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (403, 4, '公众号AesKey', 'wx_mp_aes_key', '方法委屈·', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (404, 4, '微信支付商户号', 'wx_pay_mchid', '让他给我woide', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (405, 4, '微信支付商户密钥', 'wx_pay_mchkey', '1', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (406, 4, '服务商模式子商户公众账号ID', 'wx_pay_subappid', '1', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (407, 4, '服务商模式子商户号', 'wx_pay_submchid', '1', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (408, 4, 'apiclient_cert.p12文件的绝对路径', 'wx_pay_keypath', '1', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (500, 5, '客服热线', 'hotline', '123456', 'str', NULL, 0);
INSERT INTO `setting_option` VALUES (501, 5, '报名须知', 'shopping_guide', '报名须知', 'str', NULL, 0);

-- 通知设置
INSERT INTO `setting_notice` VALUES (1, '学员上课提醒', 'studentLessonStart', 1, 'VPRMRW8分店2ibUYaOg5vs8Jg8VlLYoEGVMqz4uIYwE_VVg', 1, '无', 0, '上课前一天自动发送上课提醒给学员', 0, 'student', '公众号消息模板搜标题：上课提醒通知，行业：教育 - 培训，编号：OPENTM206931431', '');
INSERT INTO `setting_notice` VALUES (2, '学员签到与点名通知', 'studentSign', 1, '65vkd9GGQBREbOIicozD647Tjr0evDXK9x5uzPxjT8Y', 1, '无', 0, '点名后，自动发送点名信息给学员', 0, 'student', '公众号消息模板搜标题：消课完成提醒，行业：教育 - 培训，编号：OPENTM416236454', '');
INSERT INTO `setting_notice` VALUES (3, '课次状态变更通知给学员', 'studentLessonOnChange', 1, 'A4ZQe57VBkPxPzSwpkZweNosebVEodr2KwBNNQx3NKo', 1, '无', 1, '课次状态变化后发送通知给学员', 0, 'student', '公众号消息模板搜标题：课程状态变更通知，行业：教育 - 培训，编号：OPENTM207707252', '');
INSERT INTO `setting_notice` VALUES (4, '报名通知', 'studentNewContract', 1, 'IldxiI55g0lPVs6VEAAdGTliZpXm29l2pdB3ouxDYb0', 0, '无', 1, '报名后，自动发送课程签约信息给学员', 0, 'student', '公众号消息模板搜标题：报名结果通知，行业：教育 - 培训，编号：OPENTM411026400', '');
INSERT INTO `setting_notice` VALUES (5, '缴费预警通知', 'studentLessonCountLess', 1, 'yr8ezeT9cAhjiGcQ1Q-yDUg8rVyTnRtE2tUeOlNhi3s', 0, '无', 1, '学员剩余课时不足时，发送提醒通知给学员', 0, 'student', '公众号消息模板搜标题：缴费提醒，行业：教育 - 培训，编号：OPENTM405831457', NULL);
INSERT INTO `setting_notice` VALUES (6, '老师上课提醒', 'teacherLessonStart', 1, 'VPRMRW82ibUYaOg5vs8Jg8VlLYoEGVMqz4uIYwE_VVg', 0, '无', 1, '上课前一天自动发送上课提醒给上课老师', 0, 'teacher', '公众号消息模板搜标题：上课提醒通知，行业：教育 - 培训，编号：OPENTM206931431', '');
INSERT INTO `setting_notice` VALUES (7, '学员请假提醒', 'teacherStudentLeave', 1, 'v956MOdVrribWTkBwFn32N1eSO0Hxkmpc7FW8GKC_SI', 0, '无', 1, '学员发起请假后，自动发送提醒给上课老师', 0, 'teacher', '公众号消息模板搜标题：学生请假通知，行业：教育 - 培训，编号：OPENTM415433846', NULL);
INSERT INTO `setting_notice` VALUES (8, '学员课次不足提醒', 'teacherStudentLessonLess', 1, 'yr8ezeT9cAhjiGcQ1Q-yDUg8rVyTnRtE2tUeOlNhi3s', 0, '无', 1, '学员剩余课时不足时，发送提醒通知学员的负责老师', 0, 'teacher', '公众号消息模板搜标题：缴费提醒，行业：教育 - 培训，编号：OPENTM405831457', NULL);
INSERT INTO `setting_notice` VALUES (9, '课次状态变更通知给老师', 'teacherLessonOnChange', 0, 'A4ZQe57VBkPxPzSwpkZweNosebVEodr2KwBNNQx3NKo', 0, '无', 1, '课次状态变化后发送通知给上课老师和助教', 0, 'teacher', '公众号消息模板搜标题：课程状态变更通知，行业：教育 - 培训，编号：OPENTM207707252', NULL);
INSERT INTO `setting_notice` VALUES (10, '在线购课支付后通知学员', 'studentNewOrder', 1, 'hje7GdZMmEPvYat_2G6mMgIVe2F_lnEO7TgZIVhqYVk', 0, '无', 1, '在线购课支付后通知学员', 0, 'student', '公众号消息模板搜标题：订单完成通知，行业：IT科技 - IT软件与服务，编号：OPENTM204987069', NULL);
INSERT INTO `setting_notice` VALUES (11, '学员在线购课后通知顾问', 'teacherNewOrder', 1, 'hje7GdZMmEPvYat_2G6mMgIVe2F_lnEO7TgZIVhqYVk', 0, '无', 1, '学员在线购课后通知顾问，或系统设置里的默认提醒账号', 0, 'teacher', '公众号消息模板搜标题：订单完成通知，行业：IT科技 - IT软件与服务，编号：OPENTM204987069', NULL);
INSERT INTO `setting_notice` VALUES (12, '学生预约成功提醒老师', 'teacherNewAppointment', 1, 'A4ZQe57VBkPxPzSwpkZweNosebVEodr2KwBNNQx3NKo', 0, '无', 1, '学生预约成功提醒老师', 0, 'teacher', '公众号消息模板搜标题：课程状态变更通知， 行业：教育 - 培训，编号：OPENTM207707252', NULL);
INSERT INTO `setting_notice` VALUES (13, '老师课后点评结果通知学生', 'studentLessonEvaluated', 1, 'QitTyc-JBkcBa0mjEmDr9Cs8d9IogRhBPjGWpoh8Q-0', 0, '无', 0, '老师课后点评通知学生点评结果', 0, 'student', '公众号消息模板搜标题：点评结果通知， 行业：教育 - 培训，编号：OPENTM416648520', '');

SET FOREIGN_KEY_CHECKS = 1;