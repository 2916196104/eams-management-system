package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseschedule.entity.LessonStudent;
import com.zeroone.star.j5.courseschedule.mapper.LessonStudentMapper;
import com.zeroone.star.j5.courseschedule.service.ILessonStudentService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonCountLogQueryDTO;
import com.zeroone.star.project.dto.j5.courseschedule.LessonSignSaveDTO;
import com.zeroone.star.project.query.PageQuery;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Map;

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
public class LessonStudentServiceImpl extends ServiceImpl<LessonStudentMapper, LessonStudent> implements ILessonStudentService {

    @Override
    public PageDTO<Map<String, Object>> queryStatusList(String keyword, String status, PageQuery query) {
        // TODO skeleton only: add real status list query logic in next stage
        return null;
    }

    @Override
    public Integer addOrUpdateRecord(LessonSignSaveDTO dto) {
        // TODO skeleton only: add real sign save logic in next stage
        return 0;
    }

    @Override
    public Integer batchAddOrUpdateRecord(List<LessonSignSaveDTO> dtoList) {
        // TODO skeleton only: add real batch sign save logic in next stage
        return 0;
    }

    @Override
    public Integer batchSetStatus(List<Long> lessonStudentIds, String status) {
        // TODO skeleton only: add real batch status logic in next stage
        return 0;
    }

    @Override
    public Integer batchToggleLessonStatus(List<Long> lessonStudentIds, String actionType) {
        // TODO skeleton only: add real stop/resume logic in next stage
        return 0;
    }

    @Override
    public Integer rollbackCourseNum(List<Long> lessonStudentIds) {
        // TODO skeleton only: add real rollback logic in next stage
        return 0;
    }

    @Override
    public PageDTO<?> queryLessonCountLog(LessonCountLogQueryDTO queryDTO) {
        // TODO skeleton only: add real log query logic in next stage
        return null;
    }
}
