package com.zeroone.star.j5.classmanager.service;

import com.zeroone.star.project.vo.j5.classmanager.ClassDetailVO;
import org.mapstruct.Mapper;


//class领域类型转换器
@Mapper(componentModel = "spring")
public interface MsClassMapper {
    ClassDetailVO toClassDetailVO(Class clazz);
}
