package com.zeroone.star.j5.courseplan.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.j5.courseplan.entity.Staff;
import com.zeroone.star.project.query.j5.courseplan.TeacherByNameQuery;
import com.zeroone.star.project.vo.j5.courseplan.TeacherOptionVO;

public interface StaffService extends IService<Staff> {
    Page<TeacherOptionVO> listByTeacherName(TeacherByNameQuery query);
}
