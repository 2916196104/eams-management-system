package com.zeroone.star.j5.courseplan.service;

import com.zeroone.star.project.dto.j5.courseplan.BatchGenerateLessonDTO;
import com.zeroone.star.project.dto.j5.courseplan.ConflictCheckDTO;
import com.zeroone.star.project.dto.j5.courseplan.DeleteLessonDTO;
import com.zeroone.star.project.vo.j5.courseschedule.BatchGenerateLessonVO;
import com.zeroone.star.project.vo.j5.courseschedule.ConflictCheckVO;
import com.zeroone.star.project.vo.j5.courseschedule.DeleteLessonResultVO;

public interface ICoursePlanService {
    BatchGenerateLessonVO batchGenerateLessons(BatchGenerateLessonDTO dto);
    ConflictCheckVO checkConflict(ConflictCheckDTO dto);
    DeleteLessonResultVO deleteLessons(DeleteLessonDTO dto);
}