package com.zeroone.star.sys.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.sys.entity.Dict;
import com.zeroone.star.sys.mapper.DictMapper;
import com.zeroone.star.sys.service.DictService;
import org.springframework.stereotype.Service;

@Service
public class DictServiceImpl extends ServiceImpl<DictMapper, Dict>  implements DictService {
}
