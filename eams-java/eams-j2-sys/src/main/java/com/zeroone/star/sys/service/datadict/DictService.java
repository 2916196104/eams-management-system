package com.zeroone.star.sys.service.datadict;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictTypeRemoveDTO;
import com.zeroone.star.project.dto.j2.sys.Datadict.DictTypeSaveDTO;
import com.zeroone.star.sys.entity.Dict;

public interface DictService extends IService<Dict> {
    boolean saveDictType(DictTypeSaveDTO dto);
    boolean removeDictType(DictTypeRemoveDTO dto);
}
