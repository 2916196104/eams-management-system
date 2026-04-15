package com.zeroone.star.j5.courseplan.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j5.courseplan.entity.Staff;
import com.zeroone.star.project.query.j5.courseplan.TeacherByNameQuery;
import com.zeroone.star.project.vo.j5.courseplan.TeacherOptionVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper

public interface StaffMapper extends BaseMapper<Staff> {
    Page<TeacherOptionVO> getListByTeacherName(Page<Staff> page, @Param("query") TeacherByNameQuery query);
}
