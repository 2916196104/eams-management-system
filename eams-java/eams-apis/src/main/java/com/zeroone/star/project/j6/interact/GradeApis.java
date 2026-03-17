package com.zeroone.star.project.j6.interact;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.GradeDTO;
import com.zeroone.star.project.query.j6.interact.GradeQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * <p>
 * 描述：成绩单接口声明
 * </p>
 */
public interface GradeApis {
    /**
     * 获得成绩单列表（条件+分页）
     * @param condition 查询条件
     * @return 成绩单列表
     */
    JsonVO<PageDTO<GradeDTO>> queryPage(GradeQuery condition);

}
