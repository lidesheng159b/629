#include "mainWindow.h"
#include"layerStandardItem.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QtGui>
#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtCore/qbytearray.h>
#include<string>
//#pragma execution_character_set("utf-8")    // 解决汉字乱码问题，注意！！！
IMGPro::IMGPro(QWidget *parent): QMainWindow(parent)
{
    //setupUi(this) 函数接受当前窗口对象的指针作为参数，以便将 UI 定义中的控件和部件与窗口对象关联起来。
    ui.setupUi(this);
    ui_init(&ui);
    
    //初始化图层列表资源
    InitSource();
    //MakeDrawing();
  
    // 标题大小
    setWindowTitle(QStringLiteral("图像"));

    // 软件图标
    setWindowIcon(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/1.PNG")));

    // 界面大小
    resize(QApplication::desktop()->width() * 0.9, QApplication::desktop()->height() * 0.9);
    move(QApplication::desktop()->width() * 0.05, QApplication::desktop()->height() * 0.01);
    //ui.treeView->resize(QApplication::desktop()->width() * 0.9, QApplication::desktop()->height() * 0.9);
    ui.treeView->setFixedHeight(QApplication::desktop()->height() * 0.9);
    //widge布局
    QRect availableGeometry = QApplication::desktop()->availableGeometry();
    ui.graphicsView->resize(availableGeometry.width()- ui.treeView->width(), availableGeometry.height());
    ui.graphicsView->move(availableGeometry.x() + availableGeometry.width() - ui.graphicsView->width(), availableGeometry.y());
    //可修改
    //ui.widget->resize(availableGeometry.width()- ui.treeView->width(), availableGeometry.height());
    //ui.widget->move(availableGeometry.x() + availableGeometry.width() - ui.widget->width(), availableGeometry.y());

    // 第一个菜单
    QMenu* menu1 = menuBar()->addMenu(QStringLiteral("读取文件"));
    // 创建子菜单，第一个参数QIcon为添加图标，注意路径是否正确，第二个参数是子菜单的显示文本
    QAction* act1_1 = new QAction(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/1.PNG")), QStringLiteral("读取shp文件"), this);
    QAction* act1_2 = new QAction(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/1.PNG")), QStringLiteral("读取自定义文件"), this);
    // 创建快捷方式：Ctrl+N，如果想自定义快捷键，可以设置为act->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    //act1->setShortcuts(QKeySequence::New);//默认ctrl+n
    // 子菜单触发时执行槽函数
    connect(act1_1, SIGNAL(triggered()), this, SLOT(pSlot1()));
    // 菜单栏添加子菜单
    menu1->addAction(act1_1);
    menu1->addAction(act1_2);

    // 第二个菜单：添加二级菜单
    QMenu* menu2 = menuBar()->addMenu(QStringLiteral("图元绘制"));
    QAction* act2 = new QAction(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/2.PNG")), QStringLiteral("图形绘制"), this);//设置图标
    menu2->addAction(act2); //给菜单赋予这个动作，即给menu2增加一个新的动作，可以理解为子菜单+1

    QMenu* submenu = new QMenu();
    QAction* subact1_1_1 = new QAction(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/3.PNG")), QStringLiteral("线段(line)"), this);
    submenu->addAction(subact1_1_1);//给submenu增加一个新的动作，可以理解为子菜单+1
    QAction* subact1_1_2 = new QAction(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/3.PNG")), QStringLiteral("点(point)"), this);
    submenu->addAction(subact1_1_2);//给submenu增加一个新的动作，可以理解为子菜单+1
    QAction* subact1_1_3 = new QAction(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/3.PNG")), QStringLiteral("多边形(polygon)"), this);
    submenu->addAction(subact1_1_3);//给submenu增加一个新的动作，可以理解为子菜单+1
    QAction* subact1_1_4 = new QAction(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/3.PNG")), QStringLiteral("圆(circle)"), this);
    submenu->addAction(subact1_1_4);//给submenu增加一个新的动作，可以理解为子菜单+1
    QAction* subact1_1_5 = new QAction(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/3.PNG")), QStringLiteral("扇形(sector)"), this);
    submenu->addAction(subact1_1_5);//给submenu增加一个新的动作，可以理解为子菜单+1
    QAction* subact1_1_6 = new QAction(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/3.PNG")), QStringLiteral("文本(text)"), this);
    submenu->addAction(subact1_1_6);//给submenu增加一个新的动作，可以理解为子菜单+1
    QAction* subact1_1_7 = new QAction(QIcon(QStringLiteral("E:/嘉然表情包/试图把我激怒（修复版）/3.PNG")), QStringLiteral("位图(bitmap)"), this);
    submenu->addAction(subact1_1_7);//给submenu增加一个新的动作，可以理解为子菜单+1

    //什么时候位于菜单末尾了就不用创建QMenu，直接QAction

   


    act2->setMenu(submenu); // 在act2这个子菜单引出这个menu

    //********************************************
    // 窗口自带的工具栏
    QAction* act2_1 = new QAction(QIcon(QStringLiteral("./src/修改.png")), QStringLiteral("选择图形"), this);
    QAction* act2_2 = new QAction(QIcon(QStringLiteral("./src/保存图片.png")), QStringLiteral("保存图片"), this);
    QAction* act2_3 = new QAction(QIcon(QStringLiteral("./src/刷新.png")), QStringLiteral("刷新"), this);
    QAction* act2_4 = new QAction(QIcon(QStringLiteral("./src/导出.png")), QStringLiteral("导出"), this);
    //ui.mainToolBar->addAction(act1_1);  //添加动作
    ui.mainToolBar->addAction(act2_1);	//添加动作,修改图形
    ui.mainToolBar->addAction(act2_2);	//添加动作,保存图形
    ui.mainToolBar->addAction(act2_3);	//
    ui.mainToolBar->addAction(act2_4);	//导出
    // 自定义工具栏
    QToolBar* toolBar = new QToolBar();
    toolBar->setMovable(false);     // 设置工具栏不可移动,默认是可移动
    addToolBar(toolBar);                // 把工具栏添加到窗口

    QPushButton* button = new QPushButton();    // 这里用按钮控件进行测试
    button->setText(QStringLiteral("控件"));

    //toolBar->addAction(subact1_1_1);         // 添加动作
    //toolBar->addWidget(button);         // 添加控件
 
    // 任务栏
    act1_1->setStatusTip(QStringLiteral("子菜单"));//给这个动作添加提示文本（在左下角）
    


    //****************************************************//
    //                      connect                       //
    //                                                    //
    // ***************************************************//
    //connect函数部分
    QSignalMapper* signalMapper = new QSignalMapper(this);

    connect(subact1_1_1, SIGNAL(triggered()), signalMapper, SLOT(map()));//线段
    connect(subact1_1_2, SIGNAL(triggered()), signalMapper, SLOT(map()));//点
    connect(subact1_1_3, SIGNAL(triggered()), signalMapper, SLOT(map()));//多边形
    connect(subact1_1_4, SIGNAL(triggered()), signalMapper, SLOT(map()));//圆形
    connect(subact1_1_5, SIGNAL(triggered()), signalMapper, SLOT(map()));//扇形
    connect(subact1_1_6, SIGNAL(triggered()), signalMapper, SLOT(map()));//文本
    connect(subact1_1_7, SIGNAL(triggered()), signalMapper, SLOT(map()));//位图

    signalMapper->setMapping(subact1_1_1, 1);
    signalMapper->setMapping(subact1_1_2, 2);
    signalMapper->setMapping(subact1_1_3, 3);
    signalMapper->setMapping(subact1_1_4, 4);
    signalMapper->setMapping(subact1_1_5, 5);
    signalMapper->setMapping(subact1_1_6, 6);
    signalMapper->setMapping(subact1_1_7, 7);


    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(setStateInMain1(int)));
    //*****************
    connect(act2_1, SIGNAL(triggered()), this, SLOT(select_on()));//开启修改
    connect(act2_2, SIGNAL(triggered()), this, SLOT(save()));//保存图形
    connect(act2_3, SIGNAL(triggered()), this, SLOT(shuaxing()));//保存图形
    connect(act2_4, SIGNAL(triggered()), this, SLOT(savetxt()));//保存图形

    ///*************可修改
    //ui.widget->setLayout(new QVBoxLayout);
    //ui.widget->layout()->addWidget(&drawingContext);
    ui.graphicsView->setLayout(new QVBoxLayout);
    ui.graphicsView->layout()->addWidget(&drawingContext);
    // 
    

}

IMGPro::~IMGPro()
{}

// 打印日志函数，接受一个 std::string 类型的参数 str
void PrintLog(const std::string& str)
{
    // 弹出一个信息框，展示参数 str 的值，并将其转换为 const char* 类型
    QMessageBox::information(nullptr, "", str.c_str());
}

// 打印日志函数，接受一个 QString 类型的参数 str
void PrintLog(QString str)
{
    // 弹出一个信息框，展示参数 str 的值
    QMessageBox::information(nullptr, "", str);
}


//void IMGPro::iSlot()// 槽函数
//{
//    QMessageBox::information(this, tr("hello"), tr("Hello World!"));//跳出来的提示
//}

void IMGPro::InitSource()
{

    ui.treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    //添加右键菜单...
    QString qss = " QMenu{color:#E8E8E8;background:#4D4D4D;margin:2px;}\
                    QMenu::item{padding:3px 20px 3px 20px;}\
                    QMenu::indicator{width:13px;height:13px;}\
                    QMenu::item:selected{color:#E8E8E8;border:0px solid #575757;background:#1E90FF;}\
                    QMenu::separator{height:1px;background:#757575;}";      //设置样式表
    menu = new QMenu(ui.treeView);
    menu->setStyleSheet(qss);                                         //给菜单设置样式
    QAction* a1 = new QAction(QStringLiteral("增加"));
    menu->addAction(a1);
    
    connect(a1, &QAction::triggered, this, [&]() {
        // 创建选择框对话框
        shapeDialog = new QDialog(this);
        shapeDialog->setWindowTitle(QStringLiteral("选择图形"));
        QVBoxLayout* layout = new QVBoxLayout(shapeDialog);

        // 创建图形选择框
        shapeComboBox = new QComboBox();
        shapeComboBox->addItem(QStringLiteral("线段"));
        shapeComboBox->addItem(QStringLiteral("点"));
        shapeComboBox->addItem(QStringLiteral("多边形"));
        shapeComboBox->addItem(QStringLiteral("圆形"));
        shapeComboBox->addItem(QStringLiteral("扇形"));
        shapeComboBox->addItem(QStringLiteral("待定图形"));
        layout->addWidget(shapeComboBox);

        // 创建确定和取消按钮
        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout->addWidget(buttonBox);

        // 连接确定按钮的槽函数
        connect(buttonBox, &QDialogButtonBox::accepted, this, [&]() {
            int selectedShapeIndex = shapeComboBox->currentIndex();

            QModelIndex curIndex = ui.treeView->currentIndex();
            if (curIndex.isValid()) {
                auto curItem = model->itemFromIndex(curIndex);
                if (curItem != nullptr) {
                    QStringList shapeNames = { QStringLiteral("线段"), QStringLiteral("点"), QStringLiteral("多边形"), QStringLiteral("圆形"), QStringLiteral("扇形"), QStringLiteral("待定图形") };
                    QString itemName = QStringLiteral("%1_%2").arg(shapeNames.value(selectedShapeIndex)).arg(model->rowCount());
                    auto item = new layerStandardItem(itemName);
                    item->setCheckable(true);
                    item->setCheckState(Qt::Checked);
                    curItem->appendRow(item);

                    // 设置新增的项目在TreeView中可见
                    QModelIndex newItemIndex = model->indexFromItem(item);
                    ui.treeView->setExpanded(newItemIndex, true);
                    ui.treeView->scrollTo(newItemIndex);
                }
            }

            // 根据选择的图形类型设置相应的绘制状态
            if (selectedShapeIndex >= 0 && selectedShapeIndex <= 5) {
                drawingContext.isDrawing = 1;
                drawingContext.type = selectedShapeIndex + 1;
                setStateInMain1(selectedShapeIndex + 1);
            }

            shapeDialog->accept();
            });

        // 连接取消按钮的槽函数
        connect(buttonBox, &QDialogButtonBox::rejected, shapeDialog, &QDialog::reject);

        // 显示选择框对话框
        shapeDialog->exec();
        });


    QAction* a2 = new QAction(QStringLiteral("查看"));
    menu->addAction(a2);
    connect(a2, &QAction::triggered, this, [&]() {

        QModelIndex curIndex = ui.treeView->currentIndex();
        if (curIndex.isValid())
        {

            auto curItem = static_cast<layerStandardItem*>((model->itemFromIndex(curIndex)));
            if (curItem != nullptr)
            {
                QString info;
                info.append(curItem->text());//获取当前文本.
                info.append(QStringLiteral("\r\n状态: %1\r\n").arg(curItem->checkState()));
                info.append(QStringLiteral("自己的数据(IlayerTreeItem): %1").arg(curItem->gTreeData->toString().c_str()));
                PrintLog(info);
            }

        }

        });

    QAction* a5 = new QAction(QStringLiteral("展开"));
    menu->addAction(a5);
    connect(a5, &QAction::triggered, this, [&]() {

        QModelIndex curIndex = ui.treeView->currentIndex();
        if (curIndex.isValid())
        {
            ui.treeView->expand(curIndex);
        }

        });

    QAction* a6 = new QAction(QStringLiteral("收起"));
    menu->addAction(a6);
    connect(a6, &QAction::triggered, this, [&]() {

        QModelIndex curIndex = ui.treeView->currentIndex();
        if (curIndex.isValid())
        {
            ui.treeView->collapse(curIndex);
        }

        });

    QAction* a3 = new QAction(QStringLiteral("修改"));
    menu->addAction(a3);
    connect(a3, &QAction::triggered, this, [&]() {

        QModelIndex curIndex = ui.treeView->currentIndex();
        if (curIndex.isValid())
        {

            auto curItem = static_cast<layerStandardItem*>((model->itemFromIndex(curIndex)));
            if (curItem != nullptr)
            {
               
                // 获取用户输入的文本
                bool ok;
                QString text = QInputDialog::getText(this, QStringLiteral("修改"), QStringLiteral("请输入修改内容:"), QLineEdit::Normal, curItem->gTreeData->gName.c_str(), &ok);
                if (ok && !text.isEmpty())
                {
                    // 更新数据和UI
                    curItem->gTreeData->gName = text.toStdString();
                    curItem->setText(text);
                    PrintLog(QStringLiteral("修改完成"));
                }
            }

        }

        });

    QAction* a4 = new QAction(QStringLiteral("删除"));
    menu->addAction(a4);
    connect(a4, &QAction::triggered, this, [&]() {

        QModelIndex curIndex = ui.treeView->currentIndex();
        if (curIndex.isValid())
        {
            auto parentIndex = curIndex.parent();
            if (parentIndex.isValid())
            {
                auto parentItem = model->itemFromIndex(parentIndex);
                parentItem->removeRow(curIndex.row());
            }
            else
            {
                model->removeRow(curIndex.row());
            }

        }

        });
    //给菜单添加项


    //添加一些Tree数据.
    {
        model = new QStandardItemModel(ui.treeView); //指定父对象，便于内存管理
        model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("名称") << QStringLiteral("说明"));
        ui.treeView->setModel(model);//设置数据Model,关键.

        rootItem1 = new layerStandardItem(QStringLiteral("图层1"));//图层1
        model->appendRow(rootItem1);
        layerStandardItem* childItem1_1 = new layerStandardItem(QStringLiteral("三角形"));
        rootItem1->appendRow(childItem1_1);
        layerStandardItem* childItem1_2 = new layerStandardItem(QStringLiteral("四边形"));
        rootItem1->appendRow(childItem1_2);
        rootItem1->appendRow(new layerStandardItem(QStringLiteral("折线1")));
        rootItem1->appendRow(new layerStandardItem(QStringLiteral("折线2")));

        rootItem2 = new layerStandardItem(QStringLiteral("图层2"));
        model->appendRow(rootItem2);
        //model->setItem(model->indexFromItem(rootItem2).row(), 1, new layerStandardItem(QStringLiteral("黄鹤楼")));//设置第二列内容.

        layerStandardItem* childItem2_1 = new layerStandardItem(QStringLiteral("折线"));
        rootItem2->appendRow(childItem2_1);
        //rootItem2->setChild(childItem2_1->index().row(), 1, new layerStandardItem(QStringLiteral("步行街")));//在第二列添加数据.

        layerStandardItem* childItem2_2 = new layerStandardItem(QStringLiteral("折线")); //注意这里->rootItem2,通过父类设置其所在的行.
        rootItem2->appendRow(childItem2_2);
        //rootItem2->setChild(childItem2_2->index().row(),1,new layerStandardItem(QStringLiteral("揽月楼")));

        rootItem2->appendRow(new layerStandardItem(QStringLiteral("折线")));
    }

    

}
void IMGPro::updateTreeView()
{
    // 清空数据模型
    model->clear();
    model = new QStandardItemModel(ui.treeView); //指定父对象，便于内存管理
    model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("名称") << QStringLiteral("说明"));
    ui.treeView->setModel(model);//设置数据Model,关键.
    // 重新添加根节点
    rootItem1 = new layerStandardItem(QStringLiteral("图层1"));//图层1
    rootItem2 = new layerStandardItem(QStringLiteral("图层2"));
    model->appendRow(rootItem1);
    model->appendRow(rootItem2);

    // 获取场景中的项
    QList<QGraphicsItem*> items = drawingContext.scene->items();

    // 遍历场景中的项，创建对应的layerStandardItem
    for (QGraphicsItem* item : items) {
        // 过滤掉非指定类型的项
        if (item->type() != QGraphicsPolygonItem::Type && item->type() != QGraphicsEllipseItem::Type) {
            continue;
        }

        // 获取项的数据
        QString name = item->data(Qt::UserRole).toString();

        // 创建layerStandardItem，并设置名称为项的数据
        layerStandardItem* layerItem = new layerStandardItem(name);

        // 将layerStandardItem添加到对应的根节点
        if (item->type() == QGraphicsPolygonItem::Type) {
            rootItem1->appendRow(layerItem);
        }
        else if (item->type() == QGraphicsEllipseItem::Type) {
            rootItem2->appendRow(layerItem);
        }
    }
}



/// <summary>
/// 右键菜单...
/// </summary>
/// <param name="pos"></param>
void IMGPro::on_treeView_customContextMenuRequested(const QPoint& pos)
{
    if (ui.treeView->hasFocus()) {

        menu->exec(this->mapToGlobal(pos));
    }
}


//connect函数部分记得ctrl+F直接搜connect



//槽函数实现部分



void IMGPro::setStateInMain1(int i) //设置线
{
    //drawingContext.setCurrentState(new DrawingLINESTRING());
    //drawingContext.draw();

    //QAction* senderAction = qobject_cast<QAction*>(sender());
    if (i) {
        drawingContext.isDrawing= 1;
        if (i == 1) {//线
            // 处理线段相关操作
            drawingContext.setCurrentState(new DrawingLINESTRING());
            
            drawingContext.type = 1;
        }
        else if (i == 2) {//点
            drawingContext.setCurrentState(new DrawingPOINT());
            //drawingContext.draw();
            drawingContext.type = 2;
        }
        else if (i == 3) {//多边形
            drawingContext.setCurrentState(new DrawingPOLYGON());
            //drawingContext.draw();
            drawingContext.type = 3;
        }
        else if (i == 4) {//圆
            drawingContext.setCurrentState(new DrawingCIRCLE());
            //drawingContext.draw();
            drawingContext.type = 4;
        }
        else if (i == 5) {//扇形
            drawingContext.setCurrentState(new DrawingSECTOR());
            //drawingContext.draw();
            drawingContext.type = 5;
        }
        else if (i == 6) {
            drawingContext.setCurrentState(new DrawingTEXT());//文本
            //drawingContext.draw();
            drawingContext.type = 6;
        }
        else if (i == 7) {
            drawingContext.setCurrentState(new DrawingBITMAP());//位图
            //drawingContext.draw();
            drawingContext.type = 7;
        }
    }
}
void IMGPro::select_on() {
    if (drawingContext.isSelecting == 1) { 
        drawingContext.isSelecting = 0;
        
        ui.label->setText(QStringLiteral("现在是未选择状态"));
    }

    else if (drawingContext.isSelecting == 0)
    { 
        drawingContext.isSelecting = 1;
        drawingContext.scene->clearSelection();
        ui.label->setText(QStringLiteral("现在是选择状态"));
        //drawingContext.setCurrentState(NULL);

    }
    
}

void IMGPro::save() {
    // 弹出文件保存对话框，让用户选择保存的文件路径和名称
    QString filePath = QFileDialog::getSaveFileName(this, QStringLiteral("保存图像"), "", QStringLiteral("PNG 文件(*.png)"));

    if (!filePath.isEmpty()) {
        // 创建一个空白的QPixmap对象
        QPixmap pixmap(drawingContext.scene->sceneRect().size().toSize());

        // 使用QPainter在QPixmap上绘制场景
        QPainter painter(&pixmap);
        drawingContext.scene->render(&painter);

        // 保存导出的pixmap为图像文件
        pixmap.save(filePath);
    }

}

void IMGPro::shuaxing() {
    drawingContext.shuaxing();
    //updateTreeView();
}

void IMGPro::savetxt()
{
    
        // 弹出文件保存对话框
        QString fileName = QFileDialog::getSaveFileName(this, QStringLiteral("保存文件"), QString(), QStringLiteral("文本文件 (*.txt)"));
        if (fileName.isEmpty()) {
            return;
        }

        // 调用输出函数将数据写入文件
        drawingContext.outputArraysToTxt(fileName);
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("成功保存"));
  
}






