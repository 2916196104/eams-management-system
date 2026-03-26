package com.zeroone.star.classmanager.service;

import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;
import org.mapstruct.Mapper;

//class领域类型转换器
@Mapper
public interface MsClassMapper {
    ClassListVO toClassDetailVO(Class clazz);
}
