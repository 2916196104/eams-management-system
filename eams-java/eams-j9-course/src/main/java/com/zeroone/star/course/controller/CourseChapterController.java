package com.zeroone.star.course.controller;

import com.zeroone.star.course.service.ICourseChapterService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.AddChapterDTO;
import com.zeroone.star.project.dto.j9.course.RemoveChapterDTO;
import com.zeroone.star.project.j9.course.CourseChapterApis;
import com.zeroone.star.project.query.j9.course.ChapterQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.course.ChapterVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import javax.validation.Valid;

/**
 * <p>
 * 描述：课程章节管理控制器
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author 阿伟学长
 * @version 1.0.0
 */
@RestController
@RequestMapping("course/chapter")
@Api(tags = "课程章节管理")
public class CourseChapterController implements CourseChapterApis {

    @Resource
    private ICourseChapterService courseChapterService;

    @ApiOperation("获取关联章节列表")
    @GetMapping("query-chapters")
    @Override
    public JsonVO<PageDTO<ChapterVO>> queryChapters(@Validated ChapterQuery query) {
        // Controller 层方法命名 queryChapters，调用 Service 层 listChapters
        PageDTO<ChapterVO> result = courseChapterService.listChapters(query);
        return JsonVO.success(result);
    }

    @ApiOperation("添加章节")
    @PostMapping("add-chapter")
    @Override
    public JsonVO<String> addChapter(@Validated @RequestBody AddChapterDTO dto) {
        // Controller 层方法命名 addChapter，调用 Service 层 saveChapter
        // @Validated 触发 DTO 中的 @NotBlank 和 @NotNull 校验，全局异常类会自动拦截
        String resultMsg = courseChapterService.saveChapter(dto);
        if ("添加章节成功".equals(resultMsg)) {
            return JsonVO.success(resultMsg);
        }
        return JsonVO.fail(resultMsg);
    }


    @ApiOperation("移除章节")
    @DeleteMapping("remove-chapter")
    @Override
    public JsonVO<String> removeChapter(@Validated @RequestBody RemoveChapterDTO dto) {
        // Controller 层方法命名 removeChapter，调用 Service 层 removeChapter
        String resultMsg = courseChapterService.removeChapter(dto);
        if ("移除章节成功".equals(resultMsg)) {
            return JsonVO.success(resultMsg);
        }
        return JsonVO.fail(resultMsg);
    }
}