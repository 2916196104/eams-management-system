package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.FollowUpDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.query.j4.student.FollowUpQuery;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
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
public interface StudentApis {
    //分页查询学生信息
    JsonVO<PageDTO<StudentDTO>> queryPage(StudentQuery condition);
    //保存查询信息
    JsonVO<String> saveStudent(StudentDTO studentDTO);
    //更改学生 信息
    JsonVO<String> updateStudent(StudentDTO studentDTO);

    @ApiOperation("学员跟进记录") // 接口描述，表示这是一个学员跟进记录的接口
        @GetMapping("/followUp") // HTTP GET请求映射，指定请求路径为/followUp
        // 重写父类方法的注解
    JsonVO<PageDTO<FollowUpDTO>> followUp(FollowUpQuery query);
}
