#ifndef _GRADE_RECORD_MAPPER_H
#define _GRADE_RECORD_MAPPER_H

#include"Mapper.h"
#include "domain/do/Grade/GradeRecordDO.h"


class GradeRecordMapper : public Mapper<GradeRecordDO> {

public:
  GradeRecordDO mapper(ResultSet* resultSet) const override
  {
    GradeRecordDO data;
    data.setId(resultSet->getInt64(1));
    data.setGradeId(resultSet->getInt64(2));
    data.setStudentId(resultSet->getInt64(3));
    data.setScore(resultSet->getInt(4));
    data.setAddTime(resultSet->getString(5));
    data.setCreator(resultSet->getInt64(6));
    return data;
  }
};
class PtrGradeRecordMapper : public Mapper<PtrGradeRecordDO> {
public:
  PtrGradeRecordDO mapper(ResultSet* resultSet) const override
  {
    auto data = std::make_shared<GradeRecordDO>();
    data->setId(resultSet->getInt64(1));
    data->setGradeId(resultSet->getInt64(2));
    data->setStudentId(resultSet->getInt64(3));
    data->setScore(resultSet->getInt(4));
    data->setAddTime(resultSet->getString(5));
    data->setCreator(resultSet->getInt64(6));
    return data;
  }
};

#endif