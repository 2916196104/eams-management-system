package com.zeroone.star.project.j2.sys;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictItemDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictTypeRemoveDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictTypeSaveDTO;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.query.j2.sys.datadict.DictItemQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Datadict.DatadictVO;
import org.springframework.web.bind.annotation.RequestParam;

import javax.validation.constraints.NotNull;
import java.util.List;

public interface DatadictApis {

    /**
     * 查询数据字典这个表
     * @return
     */
    JsonVO<List<DictDTO>> query();

    /**
     * 查询数据字典数据类型这个表
     * @param dictId
     * @param pageIndex
     * @param pageSize
     * @return
     */
    JsonVO<PageDTO<DictItemDTO>> queryPage(@RequestParam Long dictId, @RequestParam Integer pageIndex, @RequestParam Integer pageSize);

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

    /**
     * 获取字典名称列表
     * @param dictId 字典类型ID（对应dict表的id）
     * @return 该类型下的所有字典列表
     */
    JsonVO<PageDTO<DatadictVO>> listDatadictByDictIdPage(
            @NotNull(message = "字典类型ID不能为空") @RequestParam("dictId") Long dictId,
            @RequestParam("pageIndex") Integer pageIndex,
            @RequestParam("pageSize") Integer pageSize
    );

    /**
     * 根据id获取数据字典
     */
    JsonVO<DictItemDTO> getDatadictById(Long id);
    /**
     * 获取数据字典列表
     */
    JsonVO<PageDTO<DatadictVO>> listDatadict(DictItemQuery query);
    /**
     * 增加数据字典
     */
    JsonVO<String> addDatadict(DictItemDTO dto);
    /**
     * 修改数据字典
     */
    JsonVO<String> updateDatadict(DictItemDTO dto);
    /**
     * 删除数据字典
     */
    JsonVO<String> deleteDatadict(List<Long> ids);

}
