#pragma once

#include "Mapper.h"
#include "../../../domain/do/home/LessonComment/LessonCommentDO.h"


class LessonCommentMapper : public Mapper<LessonCommentDO>
{
public:
	LessonCommentDO mapper(ResultSet* resultSet) const override
	{
        LessonCommentDO data;

        // 1. id (bigint -> uint64_t)
        data.setId(resultSet->getUInt64(1));

        // 2. lesson_id (bigint -> uint64_t)
        data.setLessonId(resultSet->getUInt64(2));

        // 3. class_id (int)
        data.setClassId(resultSet->getInt(3));

        // 4. student_id (bigint -> uint64_t)
        data.setStudentId(resultSet->getUInt64(4));

        // 5. dec_lesson_count (int)
        data.setDecLessonCount(resultSet->getInt(5));

        // 6. lesson_count (int)
        data.setLessonCount(resultSet->getInt(6));

        // 7. teacher_id (bigint -> uint64_t)
        data.setTeacherId(resultSet->getUInt64(7));

        // 8. sign_time (datetime -> string)
        data.setSignTime(resultSet->getString(8));

        // 9. sign_type (tinyint -> int)
        data.setSignType(resultSet->getInt(9));

        // 10. sign_state (tinyint -> int)
        data.setSignState(resultSet->getInt(10));

        // 11. score (tinyint -> int)
        data.setScore(resultSet->getInt(11));

        // 12. evaluation (varchar -> string)
        data.setEvaluation(resultSet->getString(12));

        // 13. evaluate_time (datetime -> string)
        data.setEvaluateTime(resultSet->getString(13));

        // 14. evaluate_teacher (bigint -> uint64_t)
        data.setEvaluateTeacherId(resultSet->getUInt64(14));

        // 15. consume_course_id (bigint -> uint64_t)
        data.setConsumeCourseId(resultSet->getUInt64(15));

        // 16. consume_student_course_id (bigint -> uint64_t)
        data.setConsumeStudentCourseId(resultSet->getUInt64(16));

        // 17. counselor (bigint -> uint64_t)
        data.setCounselor(resultSet->getUInt64(17));

        // 18. add_time (datetime -> string)
        data.setAddTime(resultSet->getString(18));

        // 19. org_id (bigint -> uint64_t)
        data.setOrgId(resultSet->getUInt64(19)); \

        data.setEvaluateTeacher(resultSet->getString(20));

        return data;
	}
};