package com.zeroone.star.academic.service.impl;

import com.zeroone.star.academic.service.ClassroomService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.academic.ClassroomDTO;
import com.zeroone.star.project.query.j4.academic.ClassroomQuery;
import com.zeroone.star.project.vo.j4.academic.ClassroomVO;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service
public class ClassroomServiceImpl implements ClassroomService {
    public PageDTO<ClassroomVO> getList(ClassroomQuery query) {
        PageDTO<ClassroomVO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(1L);
        pageDTO.setPageSize(10L);
        pageDTO.setTotal(3L);
        pageDTO.setPages(1L);

        // 添加测试数据
        List<ClassroomVO> classrooms = new ArrayList<>();

        ClassroomVO classroom1 = new ClassroomVO();
        classroom1.setId(1L);
        classroom1.setName("主教学楼 101");
        classroom1.setArea(50);
        classroom1.setAddress("主教学楼一层");
        classroom1.setRemark("普通教室");
        classrooms.add(classroom1);

        ClassroomVO classroom2 = new ClassroomVO();
        classroom2.setId(2L);
        classroom2.setName("主教学楼 201");
        classroom2.setArea(40);
        classroom2.setAddress("主教学楼二层");
        classroom2.setRemark("多媒体教室");
        classrooms.add(classroom2);

        ClassroomVO classroom3 = new ClassroomVO();
        classroom3.setId(3L);
        classroom3.setName("实验楼 301");
        classroom3.setArea(30);
        classroom3.setAddress("实验楼三层");
        classroom3.setRemark("实验室");
        classrooms.add(classroom3);

        pageDTO.setRows(classrooms);
        return pageDTO;
    }

    public ClassroomVO getClassroomById(Long id) {
        ClassroomVO classroomVO = new ClassroomVO();
        classroomVO.setId(id);
        classroomVO.setName("教室" + id);
        classroomVO.setArea(40 + (int)(id % 20));
        classroomVO.setAddress("教学楼" + ((id % 5) + 1) + "层");
        classroomVO.setRemark(id % 2 == 0 ? "多媒体教室" : "普通教室");
        return classroomVO;
    }
    public Long save(ClassroomDTO classroomDTO) {
        return classroomDTO.getId();
    }
    public List<Long> delete(List<Long> ids) {
        return ids;
    }
}