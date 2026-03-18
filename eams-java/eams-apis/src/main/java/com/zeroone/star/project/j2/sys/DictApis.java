package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.DictDTO;
import com.zeroone.star.project.dto.j2.sys.DictItemDTO;
import com.zeroone.star.project.dto.query.j2.sys.DictItemQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface DictApis {
    /**
     * 查询数据字典这个表
     * @return
     */
    JsonVO<List<DictDTO>> query();

    /**
     *查询数据字典数据类型这个表
     * @param dictItemQuery
     * @return
     */
    JsonVO<PageDTO<DictItemDTO>> queryPage(DictItemQuery dictItemQuery);

}
