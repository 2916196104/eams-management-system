package com.zeroone.star.project.j5.org;

import com.zeroone.star.courseschedule.dto.j5.org.DTO.LessonDTO;
import com.zeroone.star.courseschedule.dto.j5.org.DTO.LessonListDTO;
import com.zeroone.star.courseschedule.query.j5.org.LessonQuery;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

public interface LessonApis {
    JsonVO<List<LessonDTO>> queryList(LessonQuery condition);

    JsonVO<PageDTO<LessonListDTO>> queryPage(LessonQuery condition);
    JsonVO<List<LessonListDTO>> queryNameList(String name);
}
