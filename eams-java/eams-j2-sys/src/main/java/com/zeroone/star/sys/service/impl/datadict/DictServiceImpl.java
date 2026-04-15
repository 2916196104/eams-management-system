package com.zeroone.star.sys.service.impl.datadict;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictTypeRemoveDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictTypeSaveDTO;
import com.zeroone.star.sys.entity.Dict;
import com.zeroone.star.sys.entity.DictItem;
import com.zeroone.star.sys.mapper.datadict.DataDictMapper;
import com.zeroone.star.sys.mapper.datadict.DictMapper;
import com.zeroone.star.sys.service.datadict.DictService;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.Arrays;

@Service
public class DictServiceImpl extends ServiceImpl<DictMapper, Dict>  implements DictService {

    @Resource
    private DataDictMapper dataDictMapper;

    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean saveDictType(DictTypeSaveDTO dto) {
        Dict dict = new Dict();
        BeanUtils.copyProperties(dto, dict);

        if (dict.getId() == null) {
            return save(dict);
        } else {
            return updateById(dict);
        }
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public boolean removeDictType(DictTypeRemoveDTO dto) {
        Integer[] ids = dto.getIds();
        if (ids == null || ids.length == 0) {
            return false;
        }

        // ====================== 在这里直接删字典项，不依赖任何Service！======================
        QueryWrapper<DictItem> wrapper = new QueryWrapper<>();
        wrapper.in("dict_id", ids);
        dataDictMapper.delete(wrapper);

        // 再删类型
        return removeByIds(Arrays.asList(ids));
    }
}
