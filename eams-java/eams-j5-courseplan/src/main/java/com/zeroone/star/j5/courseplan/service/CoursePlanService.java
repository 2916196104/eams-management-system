package com.zeroone.star.j5.courseplan.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.IService;

import com.zeroone.star.j5.courseplan.entity.LessonSchedule;
import com.zeroone.star.project.dto.j5.courseplan.BatchGenerateLessonDTO;
import com.zeroone.star.project.dto.j5.courseplan.ConflictCheckDTO;
import com.zeroone.star.project.dto.j5.courseplan.DeleteLessonDTO;
import com.zeroone.star.project.dto.j5.courseschedule.ScheduleSaveDTO;
import com.zeroone.star.project.query.j5.courseplan.SchedulePlanQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.courseplan.LessonScheduleVO;
import com.zeroone.star.project.vo.j5.courseplan.SchedulePlanVO;
import com.zeroone.star.project.vo.j5.courseschedule.BatchGenerateLessonVO;
import com.zeroone.star.project.vo.j5.courseschedule.ConflictCheckVO;
import com.zeroone.star.project.vo.j5.courseschedule.DeleteLessonResultVO;

import java.util.List;

/*
* 描述：排课计划服务接口
* */
public interface CoursePlanService extends IService<LessonSchedule> {
    /*
    * 分页查询排课计划
    * */
    Page<SchedulePlanVO> listAll(SchedulePlanQuery query);

    JsonVO<Long> saveOrUpdateSchedule(ScheduleSaveDTO scheduleSaveDTO);

    LessonScheduleVO getScheduleById(Long id);

    List<Long> deleteSchedule(List<Long> ids);


    BatchGenerateLessonVO batchGenerateLessons(BatchGenerateLessonDTO dto);
    ConflictCheckVO checkConflict(ConflictCheckDTO dto);
    DeleteLessonResultVO deleteLessons(DeleteLessonDTO dto);
}
