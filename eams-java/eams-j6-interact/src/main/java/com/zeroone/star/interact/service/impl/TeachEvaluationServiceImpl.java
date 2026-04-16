package com.zeroone.star.interact.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.interact.mapper.TeachEvaluationMapper;
import com.zeroone.star.interact.service.ITeachEvaluationService;
import com.zeroone.star.project.dataobject.j6.interact.TeachEvaluationDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.TeachEvaluationDTO;
import com.zeroone.star.project.query.j6.interact.TeachEvaluationQuery;
import org.springframework.stereotype.Service;

@Service
public class TeachEvaluationServiceImpl extends ServiceImpl<TeachEvaluationMapper, TeachEvaluationDO>
        implements ITeachEvaluationService {

    @Override
    public PageDTO<TeachEvaluationDTO> queryPage(TeachEvaluationQuery condition) {
        //1.构建分页对象
        Page<TeachEvaluationDTO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());

        //2.执行SQL查询
        IPage<TeachEvaluationDTO> result = baseMapper.queryPage(
                page,
                condition.getLessonId(),
                condition.getTeacherId(),
                condition.getStudentId(),
                condition.getStartTime(),
                condition.getEndTime()
        );

        //3.转换为PageDTO
        return PageDTO.create((Page<TeachEvaluationDTO>) result);
    }

}
