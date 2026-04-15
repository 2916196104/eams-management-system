package com.zeroone.star.project.j4.academic;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import java.util.List;

/**
 * <p>
 * 描述：学员模块缴欠费与退费接口
 * </p>
 */

// 学员相关接口
public interface AcademicApis {

    JsonVO<PageDTO<StudentDTO>> queryPage(StudentQuery condition);

    JsonVO<Long> saveStudents(StudentDTO studentDTO);

    JsonVO<Long> deleteStudents(Long id);

    JsonVO<Long> updateStudents(StudentDTO studentDTO);

    JsonVO<StudentDTO> queryStudents(Long id);

    JsonVO<List<StudentDTO>> queryStudents();
}
