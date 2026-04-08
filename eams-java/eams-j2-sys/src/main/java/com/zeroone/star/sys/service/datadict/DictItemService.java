package com.zeroone.star.sys.service.datadict;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictItemDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictItemDTO;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.query.j2.sys.datadict.DictItemQuery;
import com.zeroone.star.project.vo.j2.sys.Datadict.DatadictVO;
import com.zeroone.star.sys.entity.DictItem;

import java.util.List;

/**
 * <p>
 * 描述：数据字典服务类
 * </p>
 * @author softmaple
 * @version 1.0.0
 */
public interface DictItemService extends IService<DictItem> {
    /**
     * 根据ID获取数据字典
     * @param id 字典id
     */
    DictItemDTO getDatadictById(Long id);

    /**
     * 分页获取数据字典列表
     * @param pageQuery 分页查询参数
     */
    PageDTO<DatadictVO> listDatadictByType(DictItemQuery pageQuery);

    /**
     * 添加数据字典
     * @param dictItemDTO 数据字典DTO
     */
    void addDatadict(DictItemDTO dictItemDTO);

    /**
     * 修改数据字典
     * @param dictItemDTO 数据字典DTO
     */
    void updateDatadict(DictItemDTO dictItemDTO);

    /**
     * 删除数据字典
     * @param ids 字典id列表
     */
    void deleteDatadict(List<Long> ids);

    PageDTO<DictItemDTO> queryPage(DictItemQuery condition);

    PageDTO<DatadictVO> listDatadictByDictIdPage(Long dictId, Integer pageIndex, Integer pageSize);
}
