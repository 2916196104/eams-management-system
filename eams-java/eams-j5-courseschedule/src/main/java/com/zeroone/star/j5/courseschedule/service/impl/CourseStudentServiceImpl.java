package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.*;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import com.zeroone.star.j5.courseschedule.mapper.LessonStudentMapper;
import com.zeroone.star.j5.courseschedule.service.ICourseStudentService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonChangeStateDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonCountLogQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonParamDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * <p>
 * 描述：课次学员关联服务实现类
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 冷月葬花魂
 * @version 1.0.0
 */
@Service
public class CourseStudentServiceImpl extends ServiceImpl<LessonStudentMapper, LessonStudent> implements ICourseStudentService {

    @Override
    public PageDTO<?> queryList(LessonParamDTO param) {
        // TODO skeleton only: add real query logic in next stage
        return null;
    }

    @Override
    public Integer batchSetStatus(List<Long> lessonStudentIds, String status) {
        // TODO skeleton only: add real batch status logic in next stage
        return 0;
    }

    @Override
    public Integer batchRollCall(List<LessonSignSaveDTO> signList) {
        // TODO skeleton only: add real batch roll-call logic in next stage
        return 0;
    }

    @Override
    public Integer changeLessonState(LessonChangeStateDTO dto) {
        // TODO skeleton only: add real lesson state transition logic in next stage
        return 0;
    }



    @Override
    public Integer rollbackCourseNum(List<Long> lessonStudentIds) {
        // TODO skeleton only: add real rollback logic in next stage
        return 0;
    }

    @Override
    public PageDTO<?> queryLessonCountLog(LessonCountLogQueryDTO queryDTO) {
        return null;
    }

//    @Override
//    public PageDTO<?> queryLessonCountLog(LessonCountLogQueryDTO queryDTO) {
//        // TODO skeleton only: add real log query logic in next stage
//        return null;
//    }
}
