#pragma once
#ifndef _INTENDEDSTUDENT_DAO_
#define _INTENDEDSTUDENT_DAO_

#include "BaseDAO.h"
#include "IntendedStudentMapper.h"
#include "../../domain/do/student/UserDO.h"
#include "../../domain/do/student/StudentDO.h"
#include <vector>
#include <string>

class IntendedExportDAO : public BaseDAO
{
public:
    std::list<PtrStudentDetail> selectByIds(const std::vector<std::string>& ids);
};

class IntendedImportDAO : public BaseDAO
{
public:
    /**
     * 根据手机号查询用户ID（用于判断家长是否已存在）
     */
    uint64_t selectUserIdByMobile(const std::string& mobile, SqlSession* session);

    /**
     * 恢复被禁用的账号
     */
    bool restoreUserIfDisabled(const std::string& mobile, SqlSession* session);

    /**
     * 插入新用户（家长账号）
     */
    int insertUser(const ExcelUserDO& user, SqlSession* session);

    /**
     * 单条插入学员
     */
    int insertStudent(const ExcelStudentDO& student, SqlSession* session);
};

#endif