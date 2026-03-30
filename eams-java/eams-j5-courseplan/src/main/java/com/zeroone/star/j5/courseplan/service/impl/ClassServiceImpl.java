package com.zeroone.star.j5.courseplan.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;

import com.zeroone.star.j5.courseplan.mapper.ClassMapper;
import com.zeroone.star.j5.courseplan.service.ClassService;
import com.zeroone.star.project.query.j5.courseplan.ClassByNameQuery;
import com.zeroone.star.project.vo.j5.courseplan.ClassOptionVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import com.zeroone.star.j5.courseplan.entity.Class;

@Service
public class ClassServiceImpl extends ServiceImpl<ClassMapper, Class> implements ClassService {
    @Autowired
    private ClassMapper classMapper;
    /*
    * 根据班级名查询班级信息，用于下拉菜单
    * */
    @Override
    public Page<ClassOptionVO> listByClassName(ClassByNameQuery query) {
        // sbl，忘记分页查询要创建分页查询对象了
        // 1、创建分页查询对象
        Page<ClassOptionVO> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 2、因为是多表联查，所以需要用xml获取数据
        return classMapper.listByClassName(page,query);
    }
}
