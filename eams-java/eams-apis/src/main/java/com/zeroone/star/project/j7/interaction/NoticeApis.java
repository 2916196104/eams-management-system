package com.zeroone.star.project.j7.interaction;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.NoticeDTO;
import com.zeroone.star.project.query.j7.interaction.NoticeQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.entity.Notice;
import org.springframework.web.bind.annotation.RequestBody;

import javax.validation.Valid;
import java.util.List;

/*
* 公告管理：公告查询列表、公告详情、保存公告
* @author: 薛定猫
* @date: 2026/3/17
* */
@Valid
public interface NoticeApis {

    /*
     * 公告列表查询（条件 + 分页）
     * @param: 查询条件
     * @return: 公告列表
     * */
    JsonVO<PageDTO<Notice>> queryPage( NoticeQuery noticeQuery);


    /*
     * 公告详情页查询
     * @param: 公告id
     * @return: 详情页
     * */
    JsonVO<Notice> getNoticeDetail(Long id);


    /*
     * 保存公告
     * @param: 公告信息
     * @return: 保存结果
     * */
    JsonVO<Long> saveNotice(@RequestBody @Valid NoticeDTO noticeDTO);

    /**
     * 删除公告
     * @param  ids 公告编号
     * @return 删除结果
     */
    JsonVO<String> removeNotice(List<Long> ids);


    /**
     * 修改公告状态
     * @param  id 公告编号
     * @param  status 公告状态
     * @return 修改结果
     */
    JsonVO<String> modifyNotice(Long id,Integer status);
}