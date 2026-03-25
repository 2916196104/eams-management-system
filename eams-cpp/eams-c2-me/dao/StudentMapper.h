//#pragma once
///*
// * 学生结果集映射器
// * 功能：将数据库查询的ResultSet（结果集）转换为StudentDO对象
// * 新手关键：列索引从1开始，必须和SELECT语句的列顺序一致！
// * D:\01StarProject\WorkSpaseTeamCopy\zero-one-eams2603\eams-cpp\eams-c2-me\dao\StudentMapper.h
// */
//#include "Mapper.h"          // 基础映射器基类
////#include "StudentDO.h"       // 学生实体类
//#include "../domain/do/StudentDO.h"       // 学生实体类
//
//#include "D:\01StarProject\WorkSpaseTeamCopy\zero-one-eams2603\eams-cpp\lib-mysql\include\jdbc\cppconn\resultset.h"       // 数据库结果集（封装查询结果）
//
// // 普通映射器（用于列表查询）
//class StudentMapper : public Mapper<StudentDO>
//{
//public:
//    // 核心映射方法：把结果集转成StudentDO对象
//    StudentDO mapper(ResultSet* resultSet) const override
//    {
//        StudentDO studentDO;
//        // 按student表列顺序绑定（索引从1开始！）
//        studentDO.setId(resultSet->getString(1));          // 第1列：id（主键）
//        studentDO.setUserId(resultSet->getInt64(2));       // 第2列：user_id（家长id）
//        studentDO.setFamilyRel(resultSet->getInt(3));      // 第3列：family_rel（家庭关系）
//        studentDO.setAsDefault(resultSet->getInt(4));      // 第4列：as_default（是否默认学员）
//        studentDO.setSchoolId(resultSet->getInt64(5));     // 第5列：school_id（所属分校）
//        studentDO.setName(resultSet->getString(6));        // 第6列：name（姓名）
//        studentDO.setDeleted(resultSet->getInt(7));        // 第7列：deleted（逻辑删除）
//        studentDO.setStage(resultSet->getInt(8));          // 第8列：stage（阶段状态）
//        studentDO.setGender(resultSet->getInt(9));         // 第9列：gender（性别）
//        studentDO.setBirthday(resultSet->getString(10));   // 第10列：birthday（生日）
//        studentDO.setHeadImg(resultSet->getString(11));    // 第11列：head_img（头像）
//        studentDO.setJoinWay(resultSet->getInt64(12));     // 第12列：join_way（加入方式）
//        studentDO.setRemark(resultSet->getString(13));     // 第13列：remark（备注）
//        studentDO.setGraduationDate(resultSet->getString(14)); // 第14列：graduation_date（结业日期）
//        studentDO.setGraduationReason(resultSet->getString(15)); // 第15列：graduation_reason（结业原因）
//        studentDO.setAddTime(resultSet->getString(16));    // 第16列：add_time（加入时间）
//        studentDO.setCounselor(resultSet->getInt64(17));   // 第17列：counselor（顾问）
//        studentDO.setCreator(resultSet->getInt64(18));     // 第18列：creator（创建者）
//        studentDO.setEditor(resultSet->getInt64(19));      // 第19列：editor（编辑人）
//        studentDO.setEditTime(resultSet->getString(20));   // 第20列：edit_time（编辑时间）
//        studentDO.setIdcard(resultSet->getString(21));     // 第21列：idcard（身份证号）
//        studentDO.setRedpointGrade(resultSet->getString(22)); // 第22列：redpoint_grade（成绩红点时间）
//        studentDO.setRedpointEvaluate(resultSet->getString(23)); // 第23列：redpoint_evaluate（点评红点时间）
//        studentDO.setGrade(resultSet->getInt(24));         // 第24列：grade（入学年份）
//        studentDO.setJoinDate(resultSet->getString(25));   // 第25列：join_date（入学日期）
//        studentDO.setWxAccessId(resultSet->getInt64(26));  // 第26列：wx_access_id（微信登录ID）
//        studentDO.setCredit(resultSet->getInt(27));        // 第27列：credit（积分）
//        studentDO.setOrgId(resultSet->getInt64(28));       // 第28列：org_id（所属组织ID）
//        studentDO.setGradeId(resultSet->getInt(29));       // 第29列：grade_id（年级ID）
//        return studentDO;
//    }
//};
//
//// 智能指针版本映射器（用于单条查询，返回shared_ptr）
//class PtrStudentMapper : public Mapper<PtrStudentDO>
//{
//public:
//    PtrStudentDO mapper(ResultSet* resultSet) const override
//    {
//        auto studentDO = std::make_shared<StudentDO>();
//        // 和上面普通映射器的字段绑定逻辑完全一致
//        studentDO->setId(resultSet->getString(1));
//        studentDO->setUserId(resultSet->getInt64(2));
//        studentDO->setFamilyRel(resultSet->getInt(3));
//        studentDO->setAsDefault(resultSet->getInt(4));
//        studentDO->setSchoolId(resultSet->getInt64(5));
//        studentDO->setName(resultSet->getString(6));
//        studentDO->setDeleted(resultSet->getInt(7));
//        studentDO->setStage(resultSet->getInt(8));
//        studentDO->setGender(resultSet->getInt(9));
//        studentDO->setBirthday(resultSet->getString(10));
//        studentDO->setHeadImg(resultSet->getString(11));
//        studentDO->setJoinWay(resultSet->getInt64(12));
//        studentDO->setRemark(resultSet->getString(13));
//        studentDO->setGraduationDate(resultSet->getString(14));
//        studentDO->setGraduationReason(resultSet->getString(15));
//        studentDO->setAddTime(resultSet->getString(16));
//        studentDO->setCounselor(resultSet->getInt64(17));
//        studentDO->setCreator(resultSet->getInt64(18));
//        studentDO->setEditor(resultSet->getInt64(19));
//        studentDO->setEditTime(resultSet->getString(20));
//        studentDO->setIdcard(resultSet->getString(21));
//        studentDO->setRedpointGrade(resultSet->getString(22));
//        studentDO->setRedpointEvaluate(resultSet->getString(23));
//        studentDO->setGrade(resultSet->getInt(24));
//        studentDO->setJoinDate(resultSet->getString(25));
//        studentDO->setWxAccessId(resultSet->getInt64(26));
//        studentDO->setCredit(resultSet->getInt(27));
//        studentDO->setOrgId(resultSet->getInt64(28));
//        studentDO->setGradeId(resultSet->getInt(29));
//        return studentDO;
//    }
//};