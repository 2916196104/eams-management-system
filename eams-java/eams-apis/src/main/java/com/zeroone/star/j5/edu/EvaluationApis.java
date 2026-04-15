package com.zeroone.star.j5.edu;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j5.edu.EvaluationDTO;
import com.zeroone.star.project.query.j5.edu.EvaluationQuery;
import com.zeroone.star.project.vo.JsonVO;

public interface EvaluationApis {

    /**
    * 返回课后点评列表
    * */
    JsonVO<PageDTO<EvaluationDTO>> queryPage(EvaluationQuery condition);

    /**
     * 保存点评
     * @param evaluationDTO 点评信息
     * @return 操作条数
     * */
    JsonVO<Long> saveEvaluation(EvaluationDTO evaluationDTO);

}
