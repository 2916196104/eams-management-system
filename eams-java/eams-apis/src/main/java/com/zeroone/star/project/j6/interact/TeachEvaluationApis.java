package com.zeroone.star.project.j6.interact;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.TeachEvaluationDTO;
import com.zeroone.star.project.query.j6.interact.TeachEvaluationQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * <p>
 * 描述：学评教接口声明
 * </p>
 */
public interface TeachEvaluationApis {

    /**
     * 获取学生点评列表（条件+分页）
     * @param condition 查询条件
     * @return 学生点评列表
     */
    JsonVO<PageDTO<TeachEvaluationDTO>> queryPage(TeachEvaluationQuery condition);


}