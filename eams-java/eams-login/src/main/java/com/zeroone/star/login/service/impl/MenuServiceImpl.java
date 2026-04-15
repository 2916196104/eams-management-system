package com.zeroone.star.login.service.impl;

import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.login.entity.Menu;
import com.zeroone.star.login.mapper.MenuMapper;
import com.zeroone.star.login.service.IMenuService;
import com.zeroone.star.project.vo.login.MenuTreeVO;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * Menu service implementation.
 */
class LoginMenuTreeVO extends MenuTreeVO {
    @Override
    @SuppressWarnings("unchecked")
    public List<MenuTreeVO> getChildren() {
        if (tnChildren == null) {
            return new ArrayList<>();
        }
        return (List<MenuTreeVO>) (List<?>) tnChildren;
    }
}

@Service
public class MenuServiceImpl extends ServiceImpl<MenuMapper, Menu> implements IMenuService {

    @Override
    public List<MenuTreeVO> listMenuByRoleName(List<String> roleNames) {
        if (roleNames == null || roleNames.isEmpty()) {
            return Collections.emptyList();
        }

        List<Menu> grantedMenus = baseMapper.selectByRoleCodes(roleNames);
        if (grantedMenus == null || grantedMenus.isEmpty()) {
            return Collections.emptyList();
        }

        List<Menu> menus = appendAncestorMenus(grantedMenus);
        return buildTree(menus);
    }

    private List<Menu> appendAncestorMenus(List<Menu> grantedMenus) {
        Map<Integer, Menu> menuIndex = new LinkedHashMap<>();
        for (Menu menu : grantedMenus) {
            if (menu.getId() != null) {
                menuIndex.put(menu.getId(), menu);
            }
        }

        Set<Integer> pendingParentIds = collectMissingParentIds(menuIndex.values(), menuIndex.keySet());
        while (!pendingParentIds.isEmpty()) {
            List<Menu> parentMenus = baseMapper.selectByIds(new ArrayList<>(pendingParentIds));
            if (parentMenus == null || parentMenus.isEmpty()) {
                break;
            }

            int sizeBeforeLoad = menuIndex.size();
            for (Menu parentMenu : parentMenus) {
                if (parentMenu.getId() != null) {
                    menuIndex.putIfAbsent(parentMenu.getId(), parentMenu);
                }
            }

            if (menuIndex.size() == sizeBeforeLoad) {
                break;
            }
            pendingParentIds = collectMissingParentIds(menuIndex.values(), menuIndex.keySet());
        }

        List<Menu> orderedMenus = new ArrayList<>(menuIndex.values());
        orderedMenus.sort(Comparator.comparing(Menu::getId, Comparator.nullsLast(Integer::compareTo)));
        return orderedMenus;
    }

    private Set<Integer> collectMissingParentIds(Collection<Menu> menus, Set<Integer> knownIds) {
        Set<Integer> missingParentIds = new LinkedHashSet<>();
        for (Menu menu : menus) {
            Integer parentId = normalizeParentId(menu.getParentMenuId());
            if (parentId != null && !knownIds.contains(parentId)) {
                missingParentIds.add(parentId);
            }
        }
        return missingParentIds;
    }

    private List<MenuTreeVO> buildTree(List<Menu> menus) {
        if (menus == null || menus.isEmpty()) {
            return Collections.emptyList();
        }

        Map<Integer, Menu> menuIndex = new LinkedHashMap<>();
        for (Menu menu : menus) {
            if (menu.getId() != null) {
                menuIndex.put(menu.getId(), menu);
            }
        }

        Map<Integer, List<Menu>> childrenByParentId = new LinkedHashMap<>();
        List<Menu> rootMenus = new ArrayList<>();
        for (Menu menu : menuIndex.values()) {
            Integer parentId = normalizeParentId(menu.getParentMenuId());
            if (parentId == null || !menuIndex.containsKey(parentId)) {
                rootMenus.add(menu);
                continue;
            }
            childrenByParentId.computeIfAbsent(parentId, key -> new ArrayList<>()).add(menu);
        }

        Set<Integer> visibleMenuIds = new LinkedHashSet<>();
        for (Menu rootMenu : rootMenus) {
            markVisibleMenus(rootMenu, childrenByParentId, visibleMenuIds, new LinkedHashSet<>());
        }

        List<MenuTreeVO> trees = new ArrayList<>();
        for (Menu rootMenu : rootMenus) {
            MenuTreeVO treeNode = buildNode(rootMenu, childrenByParentId, visibleMenuIds, 0);
            if (treeNode != null) {
                trees.add(treeNode);
            }
        }
        return trees;
    }

    private boolean markVisibleMenus(Menu menu,
                                     Map<Integer, List<Menu>> childrenByParentId,
                                     Set<Integer> visibleMenuIds,
                                     Set<Integer> visiting) {
        Integer menuId = menu.getId();
        if (menuId == null) {
            return false;
        }
        if (visibleMenuIds.contains(menuId)) {
            return true;
        }
        if (!visiting.add(menuId)) {
            return hasDisplayPath(menu);
        }

        boolean visible = hasDisplayPath(menu);
        List<Menu> children = childrenByParentId.get(menuId);
        if (children != null) {
            for (Menu child : children) {
                visible = markVisibleMenus(child, childrenByParentId, visibleMenuIds, visiting) || visible;
            }
        }

        visiting.remove(menuId);
        if (visible) {
            visibleMenuIds.add(menuId);
        }
        return visible;
    }

    private MenuTreeVO buildNode(Menu menu,
                                 Map<Integer, List<Menu>> childrenByParentId,
                                 Set<Integer> visibleMenuIds,
                                 int depth) {
        Integer menuId = menu.getId();
        if (menuId == null || !visibleMenuIds.contains(menuId)) {
            return null;
        }

        LoginMenuTreeVO treeNode = toTreeNode(menu);
        treeNode.setTnDepth(depth);

        List<Menu> children = childrenByParentId.get(menuId);
        if (children != null) {
            for (Menu child : children) {
                MenuTreeVO childNode = buildNode(child, childrenByParentId, visibleMenuIds, depth + 1);
                if (childNode != null) {
                    treeNode.addChild(childNode);
                }
            }
        }
        return treeNode;
    }

    private LoginMenuTreeVO toTreeNode(Menu menu) {
        LoginMenuTreeVO treeNode = new LoginMenuTreeVO();
        Integer parentId = normalizeParentId(menu.getParentMenuId());
        treeNode.setTnId(String.valueOf(menu.getId()));
        treeNode.setTnPid(parentId == null ? null : String.valueOf(parentId));
        treeNode.setId(menu.getId());
        treeNode.setIcon(menu.getIcon());
        treeNode.setText(menu.getName());
        treeNode.setHref(StringUtils.hasText(menu.getPath()) ? menu.getPath() : null);
        treeNode.setPid(parentId);
        return treeNode;
    }

    private Integer normalizeParentId(Integer parentId) {
        return parentId == null || parentId <= 0 ? null : parentId;
    }

    private boolean hasDisplayPath(Menu menu) {
        return StringUtils.hasText(menu.getPath());
    }
}
