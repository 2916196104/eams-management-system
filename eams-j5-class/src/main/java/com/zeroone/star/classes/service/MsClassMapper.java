package com.zeroone.star.classes.service;

import com.zeroone.star.project.vo.j5.classes.ClassDetailVO;
import org.mapstruct.Mapper;

//class领域类型转换器
@Mapper(componentModel = "spring")
public interface MsClassMapper {
    ClassDetailVO toClassDetailVO(Class clazz);
}
