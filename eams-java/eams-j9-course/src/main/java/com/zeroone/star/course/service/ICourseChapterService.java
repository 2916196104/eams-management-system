package com.zeroone.star.course.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.course.entity.CourseSectionDO;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.AddChapterDTO;
import com.zeroone.star.project.dto.j9.course.RemoveChapterDTO;
import com.zeroone.star.project.query.j9.course.ChapterQuery;
import com.zeroone.star.project.vo.j9.course.ChapterVO;

/**
 * <p>
 * 描述：课程章节服务类接口
 * </p>
 * @author YourName
 * @version 1.0.0
 */
public interface ICourseChapterService extends IService<CourseSectionDO> {

    /**
     * 获取关联章节列表（条件+分页）
     * @param query 查询条件
     * @return 分页数据
     */
    PageDTO<ChapterVO> listChapters(ChapterQuery query);

    /**
     * 添加章节
     * @param dto 添加章节传输对象
     * @return 添加结果提示
     */
    String saveChapter(AddChapterDTO dto);

    /**
     * 移除章节
     * @param dto 移除章节传输对象
     * @return 移除结果提示
     */
    String removeChapter(RemoveChapterDTO dto);
}