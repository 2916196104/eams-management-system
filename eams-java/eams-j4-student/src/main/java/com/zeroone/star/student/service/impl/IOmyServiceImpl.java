package com.zeroone.star.student.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.LessonCountDTO;
import com.zeroone.star.student.entity.StudentCreditLog;
import com.zeroone.star.student.entity.StudentLessonCountLog;
import com.zeroone.star.student.mapper.IOmyMapper;
import com.zeroone.star.student.service.IOmyServcie;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.List;

/**
 * 获取消课记录服务实现
 * @author MRME39
 */
@Service
public class IOmyServiceImpl implements IOmyServcie {

    @Resource
    IOmyMapper iomyMapper;

    @Override
    public PageDTO<LessonCountDTO> PageLessonCount(String StudentID) {
        //查询
        List<StudentLessonCountLog> LessonCount = iomyMapper.getById(Integer.parseInt(StudentID));
        String name = iomyMapper.SelectNameById(StudentID);
        //补充DTO数据
        List<LessonCountDTO> lessonCountDTOS = new ArrayList<>();
        int i = 1;
        for(StudentLessonCountLog studentLessonCountLog:LessonCount){
            LessonCountDTO lessonCountDTO = new LessonCountDTO();
            lessonCountDTO.setId(String.valueOf(i));
            i++;
            lessonCountDTO.setStudent_name(name);
            String ChangeCount = "";
            if(studentLessonCountLog.getChangeCount() > 0){
                ChangeCount =  "+" + studentLessonCountLog.getChangeCount();
            }else if(studentLessonCountLog.getChangeCount() < 0){
                ChangeCount =  "-" + studentLessonCountLog.getChangeCount();
            }else{
                ChangeCount = "0";
            }
            lessonCountDTO.setChange_number(ChangeCount);
            lessonCountDTO.setRemain_number(String.valueOf(studentLessonCountLog.getRemainingCount()));
            lessonCountDTO.setCourse_name(iomyMapper.SelectCourseById(studentLessonCountLog.getCourseId()));
//            lessonCountDTO.setCourse_time();上课时间待补充，数据表中没有这个数据
            lessonCountDTO.setChange_person(iomyMapper.SelectStaffById(studentLessonCountLog.getStaff_id()));
            lessonCountDTO.setRemark(studentLessonCountLog.getRemark());
            LocalDateTime localDateTime =studentLessonCountLog.getAddTime();
            lessonCountDTO.setChange_time(localDateTime.toString());
            lessonCountDTOS.add(lessonCountDTO);
        }
        //组装数据
        Page<LessonCountDTO> page = new Page<>(1, 10);
        page.setRecords(lessonCountDTOS);
        page.setTotal(LessonCount.size());
        page.setCurrent(1);
        page.setSize(10);
        page.setPages((long) Math.ceil((double) LessonCount.size() / 10));

        //转换PageDTO
        PageDTO<LessonCountDTO> pageDTO = PageDTO.create(page, LessonCountDTO.class);
        return pageDTO;
    }
}
