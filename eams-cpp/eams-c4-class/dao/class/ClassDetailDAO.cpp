#include"stdafx.h"
#include"ClassDetailDAO.h"
#include"ClassDetailMapper.h"

PtrClassDetailDO ClassDetailDAO::selectClassDetailById(std::string id)
{
	string sql = "SELECT class_name,staff_name,room_name,course_name,start_date,end_date,planed_student_count,remark,be_over,course_lessons FROM class_detail WHERE id = ?";
	return sqlSession->executeQueryOne<PtrClassDetailDO>(sql,PtrClassDetailMapper(),"s",id);
}