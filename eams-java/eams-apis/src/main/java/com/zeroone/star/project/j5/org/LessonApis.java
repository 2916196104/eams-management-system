package com.zeroone.star.project.j5.org;

import com.zeroone.star.project.dto.j5.coursrschedule.LessonDTO;
import com.zeroone.star.project.dto.j5.coursrschedule.LessonListDTO;
import com.zeroone.star.project.query.j5.courseschedule.LessonQuery;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface LessonApis {
    JsonVO<List<LessonDTO>> queryList(LessonQuery condition);

    JsonVO<PageDTO<LessonListDTO>> queryPage(LessonQuery condition);
    JsonVO<List<LessonListDTO>> queryNameList(String name);
}
