package com.zeroone.star.j5.courseschedule.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.DO.j5.courseschedule.CourseStudentDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.courseschedule.EvaluationDTO;
import com.zeroone.star.project.query.j5.courseschedule.EvaluationQuery;
import com.zeroone.star.project.vo.j5.courseschedule.EvaluationVO;

/**
 * @author silvan
 * @description
 */
public interface IEvaluationService extends IService<CourseStudentDO> {
    Long saveEvaluation(EvaluationDTO evaluationDTO);

    PageDTO<EvaluationVO> queryPage(EvaluationQuery condition);

}
