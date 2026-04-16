package com.zeroone.star.stumanager.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.StuClassQuery;
import com.zeroone.star.project.vo.j8.stumanager.ClassScheduleVO;
import com.zeroone.star.project.vo.j8.stumanager.StuClassVO;
import com.zeroone.star.stumanager.entity.Class;
import com.zeroone.star.stumanager.mapper.ClassMapper;
import com.zeroone.star.stumanager.mapper.SubjectMapper;
import com.zeroone.star.stumanager.service.IClassService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.time.LocalDate;
import java.util.List;

/**
 * <p>
 * 班级 服务实现类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Service
public class ClassServiceImpl extends ServiceImpl<ClassMapper, Class> implements IClassService {
    @Resource
    private ClassMapper classMapper;

    private SubjectMapper subjectMapper;


    @Override
    public PageDTO<StuClassVO> listStuClass(Integer pageNo, Integer pageSize, Long studentId) {
        StuClassQuery stuClassQuery = new StuClassQuery();
        stuClassQuery.setStudentId(studentId);
        Page<StuClassVO> pages = new Page<>(pageNo, pageSize);
        IPage<StuClassVO> page = classMapper.selectStuClassByPage(pages, stuClassQuery);
        Page<StuClassVO> p = (Page<StuClassVO>) page;
        return PageDTO.create(p);
    }

    @Override
    public PageDTO<ClassScheduleVO> listClassSchedule(Integer pageNo, Integer pageSize, StuClassQuery stuClassQuery) {
        Page<ClassScheduleVO> pages = new Page<>(pageNo, pageSize);
        IPage<ClassScheduleVO> page = classMapper.selectClassScheduleByPage(pages, stuClassQuery);
        Page<ClassScheduleVO> p = (Page<ClassScheduleVO>) page;
        return PageDTO.create(p);
    }
}
