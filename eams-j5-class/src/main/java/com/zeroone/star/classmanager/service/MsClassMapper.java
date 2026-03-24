package com.zeroone.star.classmanager.service;

import com.zeroone.star.project.Do.j5.classmanager.ClassDO;
import com.zeroone.star.project.vo.j5.classmanager.ClassListVO;
import org.mapstruct.Mapper;

//class领域类型转换器
@Mapper(componentModel = "spring")
public interface MsClassMapper {
    ClassListVO toClassDetailVO(ClassDO clazz);
}
