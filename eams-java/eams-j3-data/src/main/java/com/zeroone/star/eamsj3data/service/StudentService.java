package com.zeroone.star.eamsj3data.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.eamsj3data.entity.Student;
import com.zeroone.star.project.vo.j3.data.NewStudentsVO;

import java.time.LocalDateTime;
import java.util.List;


public interface StudentService extends IService<Student> {
    List<NewStudentsVO> getNewStudentsStagesInfo(LocalDateTime beginTime, LocalDateTime endTime);
}
