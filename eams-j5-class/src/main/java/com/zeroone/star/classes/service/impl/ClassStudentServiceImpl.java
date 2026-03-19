package com.zeroone.star.classes.service.impl;

import com.zeroone.star.classes.entity.ClassStudent;
import com.zeroone.star.classes.mapper.ClassStudentMapper;
import com.zeroone.star.classes.service.IClassStudentService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

/**
 * <p>
 * 班级学员表 服务实现类
 * </p>
 *
 * @author 阿伟
 * @since 2026-03-19
 */
@Service
public class ClassStudentServiceImpl extends ServiceImpl<ClassStudentMapper, ClassStudent> implements IClassStudentService {

}
