package com.zeroone.star.oauth2.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.zeroone.star.oauth2.entity.Menu;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * <p>
 * 菜单 Mapper 接口
 * </p>
 * @author 阿伟
 */
@Mapper
public interface MenuMapper extends BaseMapper<Menu> {

    /**
     * Query enabled permission urls for resource-role cache loading.
     *
     * @return enabled permission resources
     */
    List<Menu> listAllLinkUrl();
}
