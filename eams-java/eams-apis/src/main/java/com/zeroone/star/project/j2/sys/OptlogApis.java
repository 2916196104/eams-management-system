package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Optlog.OptlogDTO;
import com.zeroone.star.project.dto.j2.sys.Optlog.OptlogOperatorDTO;
import com.zeroone.star.project.query.j2.sys.optlog.OptlogOperatorQuery;
import com.zeroone.star.project.query.j2.sys.optlog.OptlogQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * @author isme
 * @description    操作日志接口声明
 * @title com.zeroone.star.project.j2.sys
 * @date 2026/3/15
 */
public interface OptlogApis {
    /**
     * 分页查询操作日志
     * @param query 查询条件
     * @return 操作日志列表
     */
    JsonVO<PageDTO<OptlogDTO>> queryOptlog(OptlogQuery query);//分页查询操作日志

    /**
     * 获取操作人列表（姓名+职位，条件+分页）
     * @param query 查询条件
     * @return 操作人列表
     */
    JsonVO<PageDTO<OptlogOperatorDTO>> queryOptlogOperators(OptlogOperatorQuery query);

}
