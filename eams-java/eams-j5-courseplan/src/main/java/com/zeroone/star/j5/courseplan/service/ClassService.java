package com.zeroone.star.j5.courseplan.service;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.j5.courseplan.entity.Class;
import com.zeroone.star.project.query.j5.courseplan.ClassByNameQuery;
import com.zeroone.star.project.vo.j5.courseplan.ClassOptionVO;

public interface ClassService extends IService<Class> {
    Page<ClassOptionVO> listByClassName(ClassByNameQuery query);
}
