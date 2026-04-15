package com.zeroone.star.j5.courseplan.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseplan.entity.Staff;
import com.zeroone.star.j5.courseplan.mapper.StaffMapper;
import com.zeroone.star.j5.courseplan.service.StaffService;
import com.zeroone.star.project.query.j5.courseplan.TeacherByNameQuery;
import com.zeroone.star.project.vo.j5.courseplan.TeacherOptionVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class StaffServiceImpl extends ServiceImpl<StaffMapper, Staff> implements StaffService {

    @Autowired
    private StaffMapper staffMapper;

    /**
     * 获取教师下拉列表
     * @param query 查询参数
     * @return 教师下拉列表
     */
    @Override
    public Page<TeacherOptionVO> listByTeacherName(TeacherByNameQuery query) {
        // 1、创建分页查询对象
        Page<Staff> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 2、进行分页查询
        return staffMapper.getListByTeacherName(page,query);
    }
}
