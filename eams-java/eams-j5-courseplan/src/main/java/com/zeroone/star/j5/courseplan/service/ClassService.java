package com.zeroone.star.j5.courseplan.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.query.j5.schedule.ClassByNameQuery;
import com.zeroone.star.project.vo.j5.schedule.ClassOptionVO;
import com.zeroone.star.j5.courseplan.entity.Class;

public interface ClassService extends IService<Class> {
    Page<ClassOptionVO> listByClassName(ClassByNameQuery query);
}
