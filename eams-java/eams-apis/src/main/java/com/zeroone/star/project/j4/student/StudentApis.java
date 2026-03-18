package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.EnrollmentDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.EnrollQuery;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;

/**
 * 学生相关API接口定义
 * 该接口定义了学生信息管理的核心操作，包括查询、保存和更新功能
 */
@Api(tags = "学员管理接口")
public interface StudentApis {

    @ApiOperation("修改学员头像")
    JsonVO<String> updateStudentAvatar(StudentDTO studentDTO);

    @ApiOperation("分页查询报名记录")
    JsonVO<PageDTO<EnrollmentDTO>> queryEnrollRecords(EnrollQuery query);

    @ApiOperation("获取报名记录详情")
    JsonVO<EnrollmentDTO> getEnrollRecord(Long id);
}
