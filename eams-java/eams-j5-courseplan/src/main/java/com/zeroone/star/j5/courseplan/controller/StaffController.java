package com.zeroone.star.j5.courseplan.controller;

import com.zeroone.star.j5.courseplan.service.StaffService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j5.schedule.StaffApis;
import com.zeroone.star.project.query.j5.schedule.TeacherByNameQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.schedule.TeacherOptionVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@Api(tags = "教师员工管理")
@Slf4j
@RequestMapping("/j5/staff")
public class StaffController implements StaffApis {

    @Autowired
    private StaffService staffService;

    /**
     * 获取教师下拉列表
     * @param query 查询参数
     * @return 教师下拉列表
     */
    @GetMapping("/teachers")
    @ApiOperation("教师/助教下拉菜单列表")
    @Override
    public JsonVO<PageDTO<TeacherOptionVO>> getTeacherOption(TeacherByNameQuery query) {
        PageDTO<TeacherOptionVO> page = PageDTO.create(staffService.listByTeacherName(query));
        return JsonVO.success(page);
    }
}
