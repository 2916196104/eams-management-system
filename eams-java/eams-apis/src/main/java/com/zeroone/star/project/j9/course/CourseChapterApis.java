package com.zeroone.star.project.j9.course;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.AddChapterDTO;
import com.zeroone.star.project.dto.j9.course.RemoveChapterDTO;
import com.zeroone.star.project.query.j9.course.ChapterQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.course.ChapterVO;

/**
 * 课程章节管理接口定义
 */
public interface CourseChapterApis {

    /**
     * 获取关联章节列表（条件+分页）
     */
    JsonVO<PageDTO<ChapterVO>> queryChapters(ChapterQuery query);

    /**
     * 添加章节
     */
    JsonVO<String> addChapter(AddChapterDTO dto);

    /**
     * 移除章节
     */
    JsonVO<String> removeChapter(RemoveChapterDTO dto);
}
