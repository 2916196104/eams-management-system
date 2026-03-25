package com.zeroone.star.stumanager.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.j8.stumanager.RegistryRecordsDTO;
import com.zeroone.star.project.query.j8.stumanager.RegistryRecordsQuery;
import com.zeroone.star.stumanager.entity.StudentCourse;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

@Mapper
public interface StudentCourseMapper extends BaseMapper<StudentCourse> {

    IPage<RegistryRecordsDTO> selectRegistryRecords(
            @Param("page") Page<RegistryRecordsDTO> page,
            @Param("condition") RegistryRecordsQuery condition
    );
}
