package com.zeroone.star.course.service.impl;

import cn.hutool.core.util.StrUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.course.entity.CourseSectionDO;
import com.zeroone.star.course.mapper.CourseChapterMapper;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.AddChapterDTO;
import com.zeroone.star.project.dto.j9.course.RemoveChapterDTO;
import com.zeroone.star.course.service.ICourseChapterService;
import com.zeroone.star.project.query.j9.course.ChapterQuery;
import com.zeroone.star.project.vo.j9.course.ChapterVO;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;

/**
 * <p>
 * 描述：课程章节服务实现类
 * </p>
 * @author YourName
 * @version 1.0.0
 */
@Service
public class CourseChapterServiceImpl extends ServiceImpl<CourseChapterMapper, CourseSectionDO> implements ICourseChapterService {

    @Override
    public PageDTO<ChapterVO> listChapters(ChapterQuery query) {
        // 1. 构建分页对象
        Page<CourseSectionDO> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 2. 构建查询条件
        LambdaQueryWrapper<CourseSectionDO> wrapper = Wrappers.lambdaQuery();
        // 如果传入了课程ID，则精确匹配
        if (query.getCourseId() != null) {
            wrapper.eq(CourseSectionDO::getCourseId, query.getCourseId());
        }
        // 如果传入了章节名称，则模糊匹配 (注意：DO中对应的字段是 title)
        if (StrUtil.isNotBlank(query.getChapterName())) {
            wrapper.like(CourseSectionDO::getTitle, query.getChapterName());
        }
        // DO中没有sort字段，所以这里改为按创建时间升序排列
        wrapper.orderByAsc(CourseSectionDO::getAddTime);

        // 3. 执行查询
        Page<CourseSectionDO> doPage = baseMapper.selectPage(page, wrapper);

        // 4. DO 转 VO (因为字段名不一致，手动设置属性最稳妥，或者使用 MapStruct 配置映射关系)
        List<ChapterVO> voList = doPage.getRecords().stream()
                .map(sectionDO -> {
                    ChapterVO vo = new ChapterVO();
                    vo.setId(sectionDO.getId());
                    vo.setCourseId(sectionDO.getCourseId());
                    // 字段名不一致映射
                    vo.setName(sectionDO.getTitle());
                    vo.setCreateTime(sectionDO.getAddTime());
                    vo.setUpdateTime(sectionDO.getEditTime());

                    // DO中不存在的字段可以给默认值
                    vo.setSort(0);
                    return vo;
                })
                .collect(Collectors.toList());

        // 5. 封装返回分页结果
        PageDTO<ChapterVO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(doPage.getCurrent());
        pageDTO.setPageSize(doPage.getSize());
        pageDTO.setTotal(doPage.getTotal());
        pageDTO.setPages(doPage.getPages());
        pageDTO.setRows(voList);

        return pageDTO;
    }

    @Override
    public String saveChapter(AddChapterDTO dto) {
        // 1. DTO 转 DO
        CourseSectionDO sectionDO = new CourseSectionDO();
        sectionDO.setCourseId(dto.getCourseId());
        // dto 的 name 对应 do 的 title
        sectionDO.setTitle(dto.getName());

        // 注：DTO中传进来的 sort 和 description 字段在 CourseSectionDO 里并没有，因此无法保存入库
        // 建议：如果不需要用到这两个字段，后续可以从 DTO中删除；如果必须要，需要让架构师给数据库加字段。

        // 补全基础数据 (如果你的mybatis-plus没有配置自动填充机制，这里需要手动赋值)
        sectionDO.setAddTime(LocalDateTime.now());
        sectionDO.setLessonCount(0); // 默认课时数为0

        // 2. 执行插入 (继承自ServiceImpl的方法底层调用的是BaseMapper的insert)
        boolean result = this.save(sectionDO);
        return result ? "添加章节成功" : "添加章节失败";
    }

    @Override
    public String removeChapter(RemoveChapterDTO dto) {
        // 执行逻辑删除或物理删除，依赖于 CourseSectionDO 中 @TableLogic 的配置
        boolean result = this.removeById(dto.getId());
        return result ? "移除章节成功" : "移除章节失败或章节不存在";
    }
}