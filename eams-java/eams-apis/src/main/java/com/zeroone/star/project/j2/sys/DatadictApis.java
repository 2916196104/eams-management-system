package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.*;
import com.zeroone.star.project.dto.query.j2.sys.DictItemQuery;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.DatadictVO;

import java.util.List;

public interface DatadictApis {
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

    /**
     * 保存字典类型
     * @param dictTypeSaveDTO 字典类型保存参数（字段匹配dict表）
     * @return 操作结果（true=成功，false=失败）
     */
    JsonVO<Boolean> saveDictType(DictTypeSaveDTO dictTypeSaveDTO);

    /**
     * 删除字典类型（支持批量）
     * @param dictTypeRemoveDTO 待删除字典类型ID数组（匹配dict表id字段）
     * @return 操作结果（true=成功，false=失败）
     */
    JsonVO<Boolean> removeDictType(DictTypeRemoveDTO dictTypeRemoveDTO);

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
