#pragma once
#pragma once
#ifndef _STUDENT_DAO_
#define _STUDENT_DAO_

#include "BaseDAO.h"
#include "../../domain/do/student/StudentDO.h"
#include "../../domain/query/student/StudentQuery.h"

/**
 * ʾ�������ݿ����ʵ��
 */
class StudentDAO : public BaseDAO
{
private:
    //************************************
    // Method:      queryConditionBuilder
    // FullName:    StudentDAO::queryConditionBuilder
    // Access:      private 
    // Returns:     std::string ��������SQL��䣬��WHERE���ֵ����
    // Parameter:   const StudentQuery::Wrapper& query ��ѯ���ݶ���
    // Parameter:   SqlParams& params ��Ų�ѯ���ݵĲ�������
    // Description: ��ѯ����������������StudentQuery����̬������ѯ������ز���
    //************************************
    inline std::string queryConditionBuilder(
        const StudentQuery::Wrapper& query, SqlParams& params);

public:
    // ͳ����������
    uint64_t count(const StudentQuery::Wrapper& query);

    // ��ҳ��ѯ����
    std::list<StudentDO> selectWithPage(const StudentQuery::Wrapper& query);

    // ͨ��������ѯ����
    // std::list<StudentDO> selectByName(const string& name);

    // ͨ��ID��ѯ����
    StudentDO selectById(std::string id);

    // ��������
    uint64_t insert(const StudentDO& data);

    // ������������
    uint64_t insertBatch(const std::list<StudentDO>& datas);

    // ��������
    uint64_t update(const StudentDO& data);

    // ͨ��IDɾ������
    uint64_t deleteById(const std::string& id);
};

#endif // !_SAMPLE_DAO_