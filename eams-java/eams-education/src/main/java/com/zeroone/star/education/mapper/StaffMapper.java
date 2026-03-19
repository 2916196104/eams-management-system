package com.zeroone.star.education.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.education.entity.Staff;
import com.zeroone.star.project.query.j5.schedule.TeacherByNameQuery;
import com.zeroone.star.project.vo.j5.schedule.TeacherOptionVO;
import org.apache.ibatis.annotations.Param;

public interface StaffMapper extends BaseMapper<Staff> {
    Page<TeacherOptionVO> getListByTeacherName(Page<Staff> page, @Param("query") TeacherByNameQuery query);
}
