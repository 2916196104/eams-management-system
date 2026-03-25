package com.zeroone.star.stumanager.service.impl;

import com.alibaba.cloud.commons.lang.StringUtils;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.StudentListQuery;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.mapper.StudentCourseMapper;
import com.zeroone.star.stumanager.mapper.StudentMapper;
import com.zeroone.star.stumanager.service.IStudentService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

/**
 * <p>
 * 学生表 服务实现类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Service
public class StudentServiceImpl extends ServiceImpl<StudentMapper, Student> implements IStudentService {
    @Resource
    private StudentMapper studentMapper;
    @Override
    public PageDTO<StudentListVO> listStudents(StudentListQuery query) {

        Page<StudentListVO> page = new Page<>(query.getPageIndex(), query.getPageSize());

        Page<StudentListVO> result = studentMapper.getList(page, query);

        return PageDTO.create(result);
    }
}
