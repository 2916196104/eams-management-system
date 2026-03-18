package com.zeroone.star.education.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.query.j5.schedule.ClassByNameQuery;
import com.zeroone.star.project.vo.j5.schedule.ClassOptionVO;
import org.apache.ibatis.annotations.Param;

public interface ClassMapper extends BaseMapper<Class> {
    Page<ClassOptionVO> getByClassName(Page<ClassOptionVO> page,@Param("query")ClassByNameQuery query);
}
