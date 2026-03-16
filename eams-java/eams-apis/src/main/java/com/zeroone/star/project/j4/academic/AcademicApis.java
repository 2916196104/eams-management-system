package com.zeroone.star.project.j4.academic;


import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

// 学员相关接口
public interface AcademicApis {
/**
 * 分页查询学生信息的方法
 * @param condition 学生查询条件对象，包含查询参数
 * @return JsonVO<PageDTO<StudentDTO>> 返回分页数据结果，包含学生信息的分页对象
 */
    JsonVO<PageDTO<StudentDTO>> queryPage(StudentQuery condition);

    //保存学生信息

    JsonVO<Long>saveStudents(StudentDTO studentDTO);
    //删除学生信息
    JsonVO<Long>deleteStudents(Long id);
    //更新学生信息
    JsonVO<Long>updateStudents(StudentDTO studentDTO);
    //根据id查询学生信息
    JsonVO<StudentDTO>queryStudents(Long id);
    //查询所有学生信息
    JsonVO<List<StudentDTO>>queryStudents();
}
