package com.zeroone.star.interact.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.interact.mapper.StudentEvaluationMapper;
import com.zeroone.star.interact.service.IStudentEvaluationService;
import com.zeroone.star.project.dataobject.j6.interact.LessonStudentDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.StudentEvaluationDTO;
import com.zeroone.star.project.query.j6.interact.StudentEvaluationQuery;
import org.springframework.stereotype.Service;

@Service
public class StudentEvaluationServiceImpl extends ServiceImpl<StudentEvaluationMapper, LessonStudentDO>
        implements IStudentEvaluationService {

    @Override
    public PageDTO<StudentEvaluationDTO> queryPage(StudentEvaluationQuery condition) {
        //1.构建分页对象
        Page<StudentEvaluationDTO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());

        //2.执行SQL查询
        IPage<StudentEvaluationDTO> result = baseMapper.queryPage(
                page,
                condition.getEvaluation(),
                condition.getLessonId(),
                condition.getTeacherId(),
                condition.getStudentId(),
                condition.getStartTime(),
                condition.getEndTime()
        );

        //3.转换为PageDTO
        return PageDTO.create((Page<StudentEvaluationDTO>) result);
    }

}
