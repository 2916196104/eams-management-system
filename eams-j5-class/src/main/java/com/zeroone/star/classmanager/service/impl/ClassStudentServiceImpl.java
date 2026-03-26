package com.zeroone.star.classmanager.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.classmanager.mapper.ClassStudentMapper;
import com.zeroone.star.classmanager.service.ClassStudentService;
import com.zeroone.star.project.Do.j5.classmanager.ClassStudentDO;
import com.zeroone.star.project.query.j5.classmanager.ClassStudentQuery;
import com.zeroone.star.project.vo.j5.classmanager.ClassStudentVO;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
@Service
public class ClassStudentServiceImpl extends ServiceImpl<ClassStudentMapper, ClassStudentDO> implements ClassStudentService {
    @Resource
    private ClassStudentMapper classStudentMapper;
    /**
     * 分页查询班级学生
     * @param classId 班级ID
     * @param query 查询参数
     * @return 分页结果
     */
    @Override
    public IPage<ClassStudentVO> queryClassStudentPage(Long classId, ClassStudentQuery query) {
        Page<ClassStudentVO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        return classStudentMapper.selectClassStudentPage(page, classId, query);
    }
}
