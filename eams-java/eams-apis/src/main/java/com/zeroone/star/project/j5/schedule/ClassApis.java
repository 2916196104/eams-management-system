package com.zeroone.star.project.j5.schedule;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j5.schedule.ClassByNameQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j5.schedule.ClassOptionVO;

/*
* 描述：班级管理相关接口声明
* */
public interface ClassApis {
    /*
    * 描述：获取班级下拉列表
    * */
    JsonVO<PageDTO<ClassOptionVO>> getClassOption(ClassByNameQuery query);
}
