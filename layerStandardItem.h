#pragma once
#include <qstandarditemmodel.h>
#include "layerTreeItem.h"

/// <summary>
/// 创建自己的QstandItem 子项目.
/// </summary>
class layerStandardItem :public QStandardItem
{
public:

	using QStandardItem::QStandardItem; // 将 QStandardItem 命名空间中的 QStandardItem 类成员引入当前作用域

	layerStandardItem() : QStandardItem() { // 定义名为 layerStandardItem 的构造函数
		//冒号后面的QStandardItem()表示调用QStandardItem类的默认构造函数来构造这个类的对象。
		//即，在当前类的构造函数内，首先调用QStandardItem类的构造函数来初始化基类，然后执行InitData函数来完成类特有的初始化操作。
		InitData(); // 调用 InitData 函数初始化数据
	}

	layerStandardItem(const QString& str) :QStandardItem(str)
	{
		InitData();
		gTreeData->gName = str.toStdString().c_str(); //将QString类型的参数转换为C风格字符串(const char*)
	}

	/*void setGraphicsItem(QGraphicsItem* item)
	{
		graphicsItem = item;
	}*/

	~layerStandardItem();
	
	std::shared_ptr<layerTreeItem> gTreeData{ nullptr };//智能指针，<>里面为模板参数

private:

	void InitData();
	//QGraphicsItem* graphicsItem;

};

