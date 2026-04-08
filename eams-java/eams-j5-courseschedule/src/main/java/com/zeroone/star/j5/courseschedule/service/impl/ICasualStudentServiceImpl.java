package com.zeroone.star.j5.courseschedule.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j5.courseschedule.mapper.CasualStudentMapper;
import com.zeroone.star.j5.courseschedule.mapper.CourseStudentMapper;
import com.zeroone.star.j5.courseschedule.mapper.StudentMapper;
import com.zeroone.star.j5.courseschedule.service.ICasualStudentService;
import com.zeroone.star.project.DO.j5.courseschedule.CourseStudentDO;
import com.zeroone.star.project.dto.j5.courseschedule.CourseStudentDTO;
import org.springframework.beans.BeanUtils;
import org.springframework.stereotype.Service;
import org.springframework.util.CollectionUtils;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

/**
 * @author silvan
 * @description
 */
@Service
public class ICasualStudentServiceImpl extends ServiceImpl<CasualStudentMapper, CourseStudentDO>implements ICasualStudentService {

    @Resource
    private CourseStudentMapper courseStudentMapper;

    @Resource
    private StudentMapper studentMapper;

    public ICasualStudentServiceImpl(CourseStudentMapper courseStudentMapper) {
        this.courseStudentMapper = courseStudentMapper;
    }

    /*
    * 添加随课生
    * */
    @Override
    public Long addCourseStudent(CourseStudentDTO courseStudentDTO) {
//        获取学生ID列表
        List<Long> studentIds = courseStudentDTO.getStudentIds();

//        批量构建DO
        List<CourseStudentDO> students =new ArrayList<>();
        for(Long studentId : studentIds){
//            判断该学生是否存在
            CourseStudentDO exist = courseStudentMapper.selectById(studentId);
            if(exist!=null){
                String name=studentMapper.selectById(studentId).getName();
                throw new RuntimeException("学生"+name+"已存在");
            }




//            创建DO
            CourseStudentDO courseStudentDO=new CourseStudentDO();
//            复制属性（id，lessonId）
            BeanUtils.copyProperties(courseStudentDTO,courseStudentDO);
//            设置学生id
            courseStudentDO.setStudentId(studentId);
            courseStudentDO.setStudentType(1);
            courseStudentDO.setCreateTime(LocalDateTime.now());
            courseStudentDO.setUpdateTime(LocalDateTime.now());

            students.add(courseStudentDO);
        }

        boolean result = this.saveBatch(students);

        return result?1L:0L;

    }
}
