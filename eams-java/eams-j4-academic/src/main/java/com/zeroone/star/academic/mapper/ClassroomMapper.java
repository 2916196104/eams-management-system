package com.zeroone.star.academic.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.academic.entity.Classroom;
import com.zeroone.star.project.query.j4.academic.ClassroomQuery;
import com.zeroone.star.project.vo.j4.academic.ClassroomVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface ClassroomMapper extends BaseMapper<Classroom> {
    IPage<ClassroomVO> getList(@Param("objectPage") Page<?> objectPage,
                               @Param("query") ClassroomQuery query);
}
