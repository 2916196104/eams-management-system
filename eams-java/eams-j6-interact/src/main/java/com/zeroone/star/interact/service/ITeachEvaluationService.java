package com.zeroone.star.interact.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dataobject.j6.interact.TeachEvaluationDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.TeachEvaluationDTO;
import com.zeroone.star.project.query.j6.interact.TeachEvaluationQuery;

public interface ITeachEvaluationService extends IService<TeachEvaluationDO> {
    PageDTO<TeachEvaluationDTO> queryPage(TeachEvaluationQuery condition);
}
