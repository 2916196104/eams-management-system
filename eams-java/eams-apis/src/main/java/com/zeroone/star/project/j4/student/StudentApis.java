package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.http.ResponseEntity;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;

public interface StudentApis {

    /**
     * 修改顾问
     * @param studentDTO
     * @return
     */
    JsonVO<String> modifyConsultant(StudentDTO studentDTO);

    /**
     * 导入在线学员
     */
    JsonVO<String> importOnlineStudents(MultipartFile file);

    /**
     * 导出在线学员
     */
    ResponseEntity<byte[]> exportOnlineStudents();

}