#pragma once
#include <iostream>
#include <memory>
#include <list>
//#pragma execution_character_set("utf-8")    // 解决汉字乱码问题，注意！！！
/// <summary>
/// Tree 基础图元数据结构
/// </summary>
class layerTreeItem
{
public:

    layerTreeItem() {};
    ~layerTreeItem() {};
    static long layerNumsID;//静态变量，记录结点个数
    void SetData(const std::string& name);//设置结点数据

    int GUID;//结点ID

    std::string gName{ "" };//结点名字

    std::shared_ptr<std::list<layerTreeItem>> gChilds{ nullptr };//子节点列表

    std::string toString() const {
        return "ture dude";
    }
    
};

