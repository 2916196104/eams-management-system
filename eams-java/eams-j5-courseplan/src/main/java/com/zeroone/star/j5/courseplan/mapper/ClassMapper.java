package com.zeroone.star.j5.courseplan.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j5.courseplan.ClassByNameQuery;
import com.zeroone.star.project.vo.j5.courseplan.ClassOptionVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import com.zeroone.star.j5.courseplan.entity.Class;

@Mapper
public interface ClassMapper extends BaseMapper<Class> {
    Page<ClassOptionVO> listByClassName(Page<ClassOptionVO> page,@Param("query")ClassByNameQuery query);
}
