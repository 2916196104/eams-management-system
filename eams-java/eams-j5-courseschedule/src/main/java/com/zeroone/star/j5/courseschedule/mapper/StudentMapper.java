package com.zeroone.star.j5.courseschedule.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.project.DO.j5.classmanager.ClassStudent;
import com.zeroone.star.project.DO.j5.classmanager.Student;
import org.apache.ibatis.annotations.Mapper;

/**
 * @author silvan
 * @description
 */
@Mapper
public interface StudentMapper extends BaseMapper<Student> {
}
