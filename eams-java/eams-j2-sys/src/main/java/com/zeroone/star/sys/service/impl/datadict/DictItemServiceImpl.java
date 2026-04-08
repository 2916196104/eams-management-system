package com.zeroone.star.sys.service.impl.datadict;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictItemDTO;
import com.zeroone.star.project.query.PageQuery;
import com.zeroone.star.project.query.j2.sys.datadict.DictItemQuery;
import com.zeroone.star.project.vo.j2.sys.Datadict.DatadictVO;
import com.zeroone.star.sys.entity.DictItem;
import com.zeroone.star.sys.mapper.datadict.DictItemMapper;
import com.zeroone.star.sys.service.datadict.DictItemService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * 描述：数据字典服务实现类
 * </p>
 * @author softmaple
 * @version 1.0.0
 */
@Service
public class DictItemServiceImpl extends ServiceImpl<DictItemMapper, DictItem> implements DictItemService {

    @Resource
    private DictItemMapper dictItemMapper;

    /**
     * 根据ID获取数据字典
     * @param id 字典id
     * @return 数据字典
     */
    @Override
    public DictItemDTO getDatadictById(Long id) {
        DictItem dictItemEntity = dictItemMapper.selectById(id);
        DictItemDTO dictItemDTO = new DictItemDTO();
        BeanUtil.copyProperties(dictItemEntity, dictItemDTO);
        return dictItemDTO;
    }

    /**
     * 分页获取数据字典列表
     * @param pageQuery 分页查询参数
     * @return 分页数据字典列表
     */
    @Override
    public PageDTO<DatadictVO> listDatadictByType(DictItemQuery pageQuery) {
        // 构建分页查询对象
        Page<DictItem> page = new Page<>(pageQuery.getPageIndex(), pageQuery.getPageSize());
        // 构建查询条件
        QueryWrapper<DictItem> queryWrapper = new QueryWrapper<>();
        if (pageQuery.getDictId() != null){
            queryWrapper.eq("dict_id", pageQuery.getDictId());
        }
        Page<DictItem> result = dictItemMapper.selectPage(page, queryWrapper);
        return PageDTO.create(result, DatadictVO.class);
    }
    /**
     * 添加数据字典
     * @param dictItemDTO 数据字典DTO
     */

    @Override
    public void addDatadict(DictItemDTO dictItemDTO) {
        DictItem dictItem = BeanUtil.copyProperties(dictItemDTO, DictItem.class);
        dictItemMapper.insert(dictItem);
    }

    /**
     * 修改数据字典
     * @param dictItemDTO 数据字典DTO
     */
    @Override
    public void updateDatadict(DictItemDTO dictItemDTO) {
        DictItem dictItem = BeanUtil.copyProperties(dictItemDTO, DictItem.class);
        dictItemMapper.updateById(dictItem);
    }

    /**
     * 删除数据字典
     * @param ids 字典id列表
     */
    @Override
    public void deleteDatadict(List<Long> ids) {
        dictItemMapper.deleteBatchIds(ids);
    }

    @Override
    public PageDTO<DictItemDTO> queryPage(DictItemQuery query) {
        if (query.getDictId() == null) {
            throw new IllegalArgumentException("查询字典项必须指定 dictId");
        }
        Page<DictItem> mpPage = new Page<>(query.getPageIndex(), query.getPageSize());
        QueryWrapper<DictItem> wrapper = new QueryWrapper<>();
        wrapper.eq("dict_id", query.getDictId());
        Page<DictItem> resultPage = this.page(mpPage, wrapper);
        return PageDTO.create(resultPage, DictItemDTO.class);
    }

    @Override
    public PageDTO<DatadictVO> listDatadictByDictIdPage(Long dictId, Integer pageIndex, Integer pageSize) {
        Page<DictItem> mpPage = new Page<>(pageIndex, pageSize);

        QueryWrapper<DictItem> wrapper = new QueryWrapper<>();
        wrapper.eq("dict_id", dictId);
        wrapper.orderByAsc("sort_num");

        Page<DictItem> resultPage = page(mpPage, wrapper);

        return PageDTO.create(resultPage, DatadictVO.class);
    }
}
