package com.zeroone.star.project.j5.schedule;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j5.schedule.TeacherByNameQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.schedule.TeacherOptionVO;

/*
* 教师员工相关接口
* */
public interface StaffApis {
    /*
     * 描述：获取教师下拉列表
     * */
    JsonVO<PageDTO<TeacherOptionVO>> getTeacherOption(TeacherByNameQuery query);
}
