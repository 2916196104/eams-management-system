package com.zeroone.star.eamsj3data.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.eamsj3data.entity.TeachEvaluation;
import com.zeroone.star.project.dto.j3.data.TeachEvaluationDTO;
import com.zeroone.star.project.query.j3.data.TeachEvaluationQuery;
import org.springframework.stereotype.Service;



public interface TeachEvaluationService extends IService<TeachEvaluation> {
    Page<TeachEvaluationDTO> queryTeachEvaluation(TeachEvaluationQuery query);
}
