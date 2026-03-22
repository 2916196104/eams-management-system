package com.zeroone.star.project.j6.interact;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.StudentEvaluationDTO;
import com.zeroone.star.project.query.j6.interact.StudentEvaluationQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * <p>
 * 描述：教评学接口声明
 * </p>
 */
public interface StudentEvaluationApis {

    /**
     * 获取教师点评列表（条件+分页）
     * @param condition 查询条件
     * @return 教师点评列表
     */
    JsonVO<PageDTO<StudentEvaluationDTO>> queryPage(StudentEvaluationQuery condition);


}