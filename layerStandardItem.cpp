#include "layerStandardItem.h"
#include <memory>


layerStandardItem::~layerStandardItem()
{
	
}
void layerStandardItem::InitData()//获取数据
{
	if (gTreeData == nullptr) gTreeData = std::make_shared<layerTreeItem>();//初始化一个layerTreeItem对象并用std::make_shared包装成shared_ptr类型
	// 设置该item可勾选
	this->setCheckable(true);
	// 设置item的初始勾选状态为已勾选
	this->setCheckState(Qt::Checked);
	// 设置item不可编辑
	this->setEditable(false);
}