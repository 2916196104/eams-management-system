package com.zeroone.star.project.j6.interact;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.GradeListDTO;
import com.zeroone.star.project.dto.j6.interact.GradeFormDTO;
import com.zeroone.star.project.dto.j6.interact.GradeRecordDTO;
import com.zeroone.star.project.query.j6.interact.GradeFormQuery;
import com.zeroone.star.project.query.j6.interact.GradeRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.web.multipart.MultipartFile;

import java.util.List;
import java.util.Map;

/**
 * 描述：成绩管理相关接口
 */
public interface GradeApis {
	/**
	 * 获得成绩单列表（条件+分页）
	 * @param condition 查询条件
	 * @return 成绩单列表
	 */
	JsonVO<PageDTO<GradeFormDTO>> queryForm(GradeFormQuery condition);

	/**
	 * 分页查询成绩列表信息
     * @param gradeRecordQuery 查询条件
	 * @return 返回结果
	 */
    JsonVO<PageDTO<GradeListDTO>> queryGrade(GradeRecordQuery gradeRecordQuery);


	/**
	 * 保存成绩单信息
	 * @param gradeFormDTO  成绩单信息
	 * todo 可能需要新建一个类来作为传入参数
	 * @return 保存结果
	 */
	JsonVO<Long> saveGrade(GradeFormDTO gradeFormDTO);

	/**
	 * 删除成绩单
	 * @param ids 成绩单id列表
	 * @return 返回结果
	 */
	JsonVO<List<Long> > deleteGrade(List<Long> ids);


	/**
	 * 保存成绩
	 * @param gradeRecordDTO 成绩数据对象
	 * @return
	 */
	//修改保存
    JsonVO<String> saveGradeRecord(GradeRecordDTO gradeRecordDTO);

    /**
	 * 删除成绩,支持批量删除
	 * @return
	 */
	JsonVO<List<Long>> deleteGradeRecord(List<Long> ids);

	/**
	 * 导入成绩
	 * @param grade_id
	 * @param file
	 * @return
	 */
	JsonVO<String> addGrades(Long grade_id, MultipartFile file);
}
