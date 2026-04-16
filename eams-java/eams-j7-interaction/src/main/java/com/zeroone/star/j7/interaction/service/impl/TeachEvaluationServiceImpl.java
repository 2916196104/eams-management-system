package com.zeroone.star.j7.interaction.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.zeroone.star.j7.interaction.entity.TeachEvaluation;
import com.zeroone.star.j7.interaction.mapper.TeachEvaluationMapper;
import com.zeroone.star.j7.interaction.service.TeachEvaluationService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.TeachEvaluationQuery;
import com.zeroone.star.project.vo.j7.interaction.TeachEvaluationVO;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;
import java.util.stream.Collectors;

@Service
public class TeachEvaluationServiceImpl implements TeachEvaluationService {

    @Resource
    private TeachEvaluationMapper teachEvaluationMapper;

    @Override
    public PageDTO<TeachEvaluationVO> pageList(TeachEvaluationQuery query) {
        // 分页参数
        long pageIndex = query.getPageIndex() < 1 ? 1 : query.getPageIndex();
        long pageSize = query.getPageSize();

        if (pageSize != 30 && pageSize != 50 && pageSize != 100 && pageSize != 200) {
            pageSize = 30L;
        }

        // 查询条件
        LambdaQueryWrapper<TeachEvaluation> wrapper = new LambdaQueryWrapper<>();
        if (query.getTeacherId() != null) {
            wrapper.eq(TeachEvaluation::getTeacherId, query.getTeacherId());
        }
        if (query.getStudentId() != null) {
            wrapper.eq(TeachEvaluation::getStudentId, query.getStudentId());
        }
        if (query.getLessonId() != null) {
            wrapper.eq(TeachEvaluation::getLessonId, query.getLessonId());
        }
        if (query.getAddTimeStart() != null) {
            wrapper.ge(TeachEvaluation::getAddTime, query.getAddTimeStart());
        }
        if (query.getAddTimeEnd() != null) {
            wrapper.le(TeachEvaluation::getAddTime, query.getAddTimeEnd());
        }

        // 1. 手动查总数
        long total = teachEvaluationMapper.selectCount(wrapper);

        // 2. 手动分页
        int start = (int) ((pageIndex - 1) * pageSize);
        wrapper.last("LIMIT " + start + "," + pageSize);
        List<TeachEvaluation> records = teachEvaluationMapper.selectList(wrapper);

        // 3. 转VO
        List<TeachEvaluationVO> voList = records.stream().map(this::toVo).collect(Collectors.toList());

        // 4. 封装结果
        PageDTO<TeachEvaluationVO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(pageIndex);
        pageDTO.setPageSize(pageSize);
        pageDTO.setTotal(total);
        pageDTO.setPages((total + pageSize - 1) / pageSize);
        pageDTO.setRows(voList);

        return pageDTO;
    }

    private TeachEvaluationVO toVo(TeachEvaluation e) {
        TeachEvaluationVO vo = new TeachEvaluationVO();
        vo.setAtmosphereScore(e.getScore1());
        vo.setAttitudeScore(e.getScore2());
        vo.setEffectScore(e.getScore3());
        vo.setContent(e.getContent());
        vo.setAddTime(e.getAddTime());
        vo.setAnonymity(e.getAnonymity());
        vo.setOrgId(e.getOrgId());

        int sum = (e.getScore1() == null ? 0 : e.getScore1())
                + (e.getScore2() == null ? 0 : e.getScore2())
                + (e.getScore3() == null ? 0 : e.getScore3());
        vo.setOverallScore(sum / 3);

        vo.setStudentName("学生ID：" + e.getStudentId());
        vo.setTeacherName("老师ID：" + e.getTeacherId());
        vo.setLessonTitle("课次ID：" + e.getLessonId());
        return vo;
    }
}