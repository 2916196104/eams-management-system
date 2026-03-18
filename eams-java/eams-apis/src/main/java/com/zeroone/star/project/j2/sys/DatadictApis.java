package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.DatadictDTO;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.DatadictVO;

import java.util.List;

/**
 * <p>
 * 描述：数据字典API接口定义
 * </p>
 * @author softmaple
 * @version 1.0.0
 */
public interface DatadictApis {
    /**
     * 根据id获取数据字典
     */
    JsonVO<DatadictVO> getDatadictById(Integer id);
    /**
     * 获取数据字典列表
     */
    JsonVO<PageDTO<DatadictVO>> listDatadict(PageQuery query);
    /**
     * 增加数据字典
     */
    JsonVO<String> addDatadict(DatadictDTO dto);
    /**
     * 修改数据字典
     */
    JsonVO<String> updateDatadict(DatadictDTO dto);
    /**
     * 删除数据字典
     */
    JsonVO<String> deleteDatadict(List<Integer> ids);

    /**
     * 获取字典名称列表
     * @param dictId 字典类型ID（对应dict表的id）
     * @return 该类型下的所有字典列表
     */
    JsonVO<PageDTO<DatadictVO>> listDatadictByDictIdPage(Long dictId, PageQuery query);
}
