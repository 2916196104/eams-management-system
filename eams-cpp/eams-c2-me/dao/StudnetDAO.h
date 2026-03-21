//#pragma once
///*
// * 学生数据访问对象（DAO）头文件
// * 功能：封装学生表的数据库操作（查询单条、新增）
// * 新手注意：DAO层只负责和数据库交互，不包含业务逻辑
// */
//#include "BaseDAO.h"          // 基础DAO基类
//#include "StudentDO.h"       // 学生实体类（对应student表）
//#include "StudentMapper.h"   // 结果集映射器（DO和数据库列的映射）
////#include "SqlParams.h"       // SQL参数绑定工具
//#include <string>            // 字符串类型
//#include <list>              // 列表容器（可选，若扩展批量查询）
//
// // 学生DAO类，继承BaseDAO获取基础数据库操作能力
//class StudentDAO : public BaseDAO
//{
//public:
//    /**
//     * 功能：根据学生ID查询单个学生信息（核心接口1：获取当前学生信息）
//     * @param id 学生表主键ID（对应student.id）
//     * @return PtrStudentDO 学生DO对象的智能指针（查询不到返回nullptr）
//     */
//    PtrStudentDO selectById(const std::string& id);
//
//    /**
//     * 功能：新增保存学生信息（核心接口2：PUSH新增学生）
//     * @param studentDO 待保存的学生DO对象（需设置非空字段）
//     * @return int 受影响的行数（1=新增成功，0=失败）
//     * 新手注意：主键id若为自增，可改用BaseDAO的insertAutoPk方法
//     */
//    int insert(const StudentDO& studentDO);
//};