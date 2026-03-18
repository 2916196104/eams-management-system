package com.zeroone.star.education.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j5.schedule.StaffApis;
import com.zeroone.star.project.query.j5.schedule.TeacherByNameQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.schedule.TeacherOptionVO;
import io.swagger.annotations.Api;
import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@Api(tags = "教师员工管理")
@Slf4j
@RequestMapping("/j5/staff")
public class StaffController implements StaffApis {
    @Override
    public JsonVO<PageDTO<TeacherOptionVO>> getTeacherOption(TeacherByNameQuery query) {
        return null;
    }
}
