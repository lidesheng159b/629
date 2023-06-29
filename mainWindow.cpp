#include "mainWindow.h"
#include"layerStandardItem.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QtGui>
#include <QtWidgets>
#include <QtWidgets/QApplication>
#include <QtCore/qbytearray.h>
#include<string>
//#pragma execution_character_set("utf-8")    // ��������������⣬ע�⣡����
IMGPro::IMGPro(QWidget *parent): QMainWindow(parent)
{
    //setupUi(this) �������ܵ�ǰ���ڶ����ָ����Ϊ�������Ա㽫 UI �����еĿؼ��Ͳ����봰�ڶ������������
    ui.setupUi(this);
    ui_init(&ui);
    
    //��ʼ��ͼ���б���Դ
    InitSource();
    //MakeDrawing();
  
    // �����С
    setWindowTitle(QStringLiteral("ͼ��"));

    // ����ͼ��
    setWindowIcon(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/1.PNG")));

    // �����С
    resize(QApplication::desktop()->width() * 0.9, QApplication::desktop()->height() * 0.9);
    move(QApplication::desktop()->width() * 0.05, QApplication::desktop()->height() * 0.01);
    //ui.treeView->resize(QApplication::desktop()->width() * 0.9, QApplication::desktop()->height() * 0.9);
    ui.treeView->setFixedHeight(QApplication::desktop()->height() * 0.9);
    //widge����
    QRect availableGeometry = QApplication::desktop()->availableGeometry();
    ui.graphicsView->resize(availableGeometry.width()- ui.treeView->width(), availableGeometry.height());
    ui.graphicsView->move(availableGeometry.x() + availableGeometry.width() - ui.graphicsView->width(), availableGeometry.y());
    //���޸�
    //ui.widget->resize(availableGeometry.width()- ui.treeView->width(), availableGeometry.height());
    //ui.widget->move(availableGeometry.x() + availableGeometry.width() - ui.widget->width(), availableGeometry.y());

    // ��һ���˵�
    QMenu* menu1 = menuBar()->addMenu(QStringLiteral("��ȡ�ļ�"));
    // �����Ӳ˵�����һ������QIconΪ����ͼ�꣬ע��·���Ƿ���ȷ���ڶ����������Ӳ˵�����ʾ�ı�
    QAction* act1_1 = new QAction(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/1.PNG")), QStringLiteral("��ȡshp�ļ�"), this);
    QAction* act1_2 = new QAction(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/1.PNG")), QStringLiteral("��ȡ�Զ����ļ�"), this);
    // ������ݷ�ʽ��Ctrl+N��������Զ����ݼ�����������Ϊact->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    //act1->setShortcuts(QKeySequence::New);//Ĭ��ctrl+n
    // �Ӳ˵�����ʱִ�вۺ���
    connect(act1_1, SIGNAL(triggered()), this, SLOT(pSlot1()));
    // �˵��������Ӳ˵�
    menu1->addAction(act1_1);
    menu1->addAction(act1_2);

    // �ڶ����˵������Ӷ����˵�
    QMenu* menu2 = menuBar()->addMenu(QStringLiteral("ͼԪ����"));
    QAction* act2 = new QAction(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/2.PNG")), QStringLiteral("ͼ�λ���"), this);//����ͼ��
    menu2->addAction(act2); //���˵������������������menu2����һ���µĶ�������������Ϊ�Ӳ˵�+1

    QMenu* submenu = new QMenu();
    QAction* subact1_1_1 = new QAction(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/3.PNG")), QStringLiteral("�߶�(line)"), this);
    submenu->addAction(subact1_1_1);//��submenu����һ���µĶ�������������Ϊ�Ӳ˵�+1
    QAction* subact1_1_2 = new QAction(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/3.PNG")), QStringLiteral("��(point)"), this);
    submenu->addAction(subact1_1_2);//��submenu����һ���µĶ�������������Ϊ�Ӳ˵�+1
    QAction* subact1_1_3 = new QAction(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/3.PNG")), QStringLiteral("�����(polygon)"), this);
    submenu->addAction(subact1_1_3);//��submenu����һ���µĶ�������������Ϊ�Ӳ˵�+1
    QAction* subact1_1_4 = new QAction(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/3.PNG")), QStringLiteral("Բ(circle)"), this);
    submenu->addAction(subact1_1_4);//��submenu����һ���µĶ�������������Ϊ�Ӳ˵�+1
    QAction* subact1_1_5 = new QAction(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/3.PNG")), QStringLiteral("����(sector)"), this);
    submenu->addAction(subact1_1_5);//��submenu����һ���µĶ�������������Ϊ�Ӳ˵�+1
    QAction* subact1_1_6 = new QAction(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/3.PNG")), QStringLiteral("�ı�(text)"), this);
    submenu->addAction(subact1_1_6);//��submenu����һ���µĶ�������������Ϊ�Ӳ˵�+1
    QAction* subact1_1_7 = new QAction(QIcon(QStringLiteral("E:/��Ȼ�����/��ͼ���Ҽ�ŭ���޸��棩/3.PNG")), QStringLiteral("λͼ(bitmap)"), this);
    submenu->addAction(subact1_1_7);//��submenu����һ���µĶ�������������Ϊ�Ӳ˵�+1

    //ʲôʱ��λ�ڲ˵�ĩβ�˾Ͳ��ô���QMenu��ֱ��QAction

   


    act2->setMenu(submenu); // ��act2����Ӳ˵��������menu

    //********************************************
    // �����Դ��Ĺ�����
    QAction* act2_1 = new QAction(QIcon(QStringLiteral("./src/�޸�.png")), QStringLiteral("ѡ��ͼ��"), this);
    QAction* act2_2 = new QAction(QIcon(QStringLiteral("./src/����ͼƬ.png")), QStringLiteral("����ͼƬ"), this);
    QAction* act2_3 = new QAction(QIcon(QStringLiteral("./src/ˢ��.png")), QStringLiteral("ˢ��"), this);
    QAction* act2_4 = new QAction(QIcon(QStringLiteral("./src/����.png")), QStringLiteral("����"), this);
    //ui.mainToolBar->addAction(act1_1);  //���Ӷ���
    ui.mainToolBar->addAction(act2_1);	//���Ӷ���,�޸�ͼ��
    ui.mainToolBar->addAction(act2_2);	//���Ӷ���,����ͼ��
    ui.mainToolBar->addAction(act2_3);	//
    ui.mainToolBar->addAction(act2_4);	//����
    // �Զ��幤����
    QToolBar* toolBar = new QToolBar();
    toolBar->setMovable(false);     // ���ù����������ƶ�,Ĭ���ǿ��ƶ�
    addToolBar(toolBar);                // �ѹ��������ӵ�����

    QPushButton* button = new QPushButton();    // �����ð�ť�ؼ����в���
    button->setText(QStringLiteral("�ؼ�"));

    //toolBar->addAction(subact1_1_1);         // ���Ӷ���
    //toolBar->addWidget(button);         // ���ӿؼ�
 
    // ������
    act1_1->setStatusTip(QStringLiteral("�Ӳ˵�"));//���������������ʾ�ı��������½ǣ�
    


    //****************************************************//
    //                      connect                       //
    //                                                    //
    // ***************************************************//
    //connect��������
    QSignalMapper* signalMapper = new QSignalMapper(this);

    connect(subact1_1_1, SIGNAL(triggered()), signalMapper, SLOT(map()));//�߶�
    connect(subact1_1_2, SIGNAL(triggered()), signalMapper, SLOT(map()));//��
    connect(subact1_1_3, SIGNAL(triggered()), signalMapper, SLOT(map()));//�����
    connect(subact1_1_4, SIGNAL(triggered()), signalMapper, SLOT(map()));//Բ��
    connect(subact1_1_5, SIGNAL(triggered()), signalMapper, SLOT(map()));//����
    connect(subact1_1_6, SIGNAL(triggered()), signalMapper, SLOT(map()));//�ı�
    connect(subact1_1_7, SIGNAL(triggered()), signalMapper, SLOT(map()));//λͼ

    signalMapper->setMapping(subact1_1_1, 1);
    signalMapper->setMapping(subact1_1_2, 2);
    signalMapper->setMapping(subact1_1_3, 3);
    signalMapper->setMapping(subact1_1_4, 4);
    signalMapper->setMapping(subact1_1_5, 5);
    signalMapper->setMapping(subact1_1_6, 6);
    signalMapper->setMapping(subact1_1_7, 7);


    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(setStateInMain1(int)));
    //*****************
    connect(act2_1, SIGNAL(triggered()), this, SLOT(select_on()));//�����޸�
    connect(act2_2, SIGNAL(triggered()), this, SLOT(save()));//����ͼ��
    connect(act2_3, SIGNAL(triggered()), this, SLOT(shuaxing()));//����ͼ��
    connect(act2_4, SIGNAL(triggered()), this, SLOT(savetxt()));//����ͼ��

    ///*************���޸�
    //ui.widget->setLayout(new QVBoxLayout);
    //ui.widget->layout()->addWidget(&drawingContext);
    ui.graphicsView->setLayout(new QVBoxLayout);
    ui.graphicsView->layout()->addWidget(&drawingContext);
    // 
    

}

IMGPro::~IMGPro()
{}

// ��ӡ��־����������һ�� std::string ���͵Ĳ��� str
void PrintLog(const std::string& str)
{
    // ����һ����Ϣ��չʾ���� str ��ֵ��������ת��Ϊ const char* ����
    QMessageBox::information(nullptr, "", str.c_str());
}

// ��ӡ��־����������һ�� QString ���͵Ĳ��� str
void PrintLog(QString str)
{
    // ����һ����Ϣ��չʾ���� str ��ֵ
    QMessageBox::information(nullptr, "", str);
}


//void IMGPro::iSlot()// �ۺ���
//{
//    QMessageBox::information(this, tr("hello"), tr("Hello World!"));//����������ʾ
//}

void IMGPro::InitSource()
{

    ui.treeView->setContextMenuPolicy(Qt::CustomContextMenu);
    //�����Ҽ��˵�...
    QString qss = " QMenu{color:#E8E8E8;background:#4D4D4D;margin:2px;}\
                    QMenu::item{padding:3px 20px 3px 20px;}\
                    QMenu::indicator{width:13px;height:13px;}\
                    QMenu::item:selected{color:#E8E8E8;border:0px solid #575757;background:#1E90FF;}\
                    QMenu::separator{height:1px;background:#757575;}";      //������ʽ��
    menu = new QMenu(ui.treeView);
    menu->setStyleSheet(qss);                                         //���˵�������ʽ
    QAction* a1 = new QAction(QStringLiteral("����"));
    menu->addAction(a1);
    
    connect(a1, &QAction::triggered, this, [&]() {
        // ����ѡ���Ի���
        shapeDialog = new QDialog(this);
        shapeDialog->setWindowTitle(QStringLiteral("ѡ��ͼ��"));
        QVBoxLayout* layout = new QVBoxLayout(shapeDialog);

        // ����ͼ��ѡ���
        shapeComboBox = new QComboBox();
        shapeComboBox->addItem(QStringLiteral("�߶�"));
        shapeComboBox->addItem(QStringLiteral("��"));
        shapeComboBox->addItem(QStringLiteral("�����"));
        shapeComboBox->addItem(QStringLiteral("Բ��"));
        shapeComboBox->addItem(QStringLiteral("����"));
        shapeComboBox->addItem(QStringLiteral("����ͼ��"));
        layout->addWidget(shapeComboBox);

        // ����ȷ����ȡ����ť
        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        layout->addWidget(buttonBox);

        // ����ȷ����ť�Ĳۺ���
        connect(buttonBox, &QDialogButtonBox::accepted, this, [&]() {
            int selectedShapeIndex = shapeComboBox->currentIndex();

            QModelIndex curIndex = ui.treeView->currentIndex();
            if (curIndex.isValid()) {
                auto curItem = model->itemFromIndex(curIndex);
                if (curItem != nullptr) {
                    QStringList shapeNames = { QStringLiteral("�߶�"), QStringLiteral("��"), QStringLiteral("�����"), QStringLiteral("Բ��"), QStringLiteral("����"), QStringLiteral("����ͼ��") };
                    QString itemName = QStringLiteral("%1_%2").arg(shapeNames.value(selectedShapeIndex)).arg(model->rowCount());
                    auto item = new layerStandardItem(itemName);
                    item->setCheckable(true);
                    item->setCheckState(Qt::Checked);
                    curItem->appendRow(item);

                    // ������������Ŀ��TreeView�пɼ�
                    QModelIndex newItemIndex = model->indexFromItem(item);
                    ui.treeView->setExpanded(newItemIndex, true);
                    ui.treeView->scrollTo(newItemIndex);
                }
            }

            // ����ѡ���ͼ������������Ӧ�Ļ���״̬
            if (selectedShapeIndex >= 0 && selectedShapeIndex <= 5) {
                drawingContext.isDrawing = 1;
                drawingContext.type = selectedShapeIndex + 1;
                setStateInMain1(selectedShapeIndex + 1);
            }

            shapeDialog->accept();
            });

        // ����ȡ����ť�Ĳۺ���
        connect(buttonBox, &QDialogButtonBox::rejected, shapeDialog, &QDialog::reject);

        // ��ʾѡ���Ի���
        shapeDialog->exec();
        });


    QAction* a2 = new QAction(QStringLiteral("�鿴"));
    menu->addAction(a2);
    connect(a2, &QAction::triggered, this, [&]() {

        QModelIndex curIndex = ui.treeView->currentIndex();
        if (curIndex.isValid())
        {

            auto curItem = static_cast<layerStandardItem*>((model->itemFromIndex(curIndex)));
            if (curItem != nullptr)
            {
                QString info;
                info.append(curItem->text());//��ȡ��ǰ�ı�.
                info.append(QStringLiteral("\r\n״̬: %1\r\n").arg(curItem->checkState()));
                info.append(QStringLiteral("�Լ�������(IlayerTreeItem): %1").arg(curItem->gTreeData->toString().c_str()));
                PrintLog(info);
            }

        }

        });

    QAction* a5 = new QAction(QStringLiteral("չ��"));
    menu->addAction(a5);
    connect(a5, &QAction::triggered, this, [&]() {

        QModelIndex curIndex = ui.treeView->currentIndex();
        if (curIndex.isValid())
        {
            ui.treeView->expand(curIndex);
        }

        });

    QAction* a6 = new QAction(QStringLiteral("����"));
    menu->addAction(a6);
    connect(a6, &QAction::triggered, this, [&]() {

        QModelIndex curIndex = ui.treeView->currentIndex();
        if (curIndex.isValid())
        {
            ui.treeView->collapse(curIndex);
        }

        });

    QAction* a3 = new QAction(QStringLiteral("�޸�"));
    menu->addAction(a3);
    connect(a3, &QAction::triggered, this, [&]() {

        QModelIndex curIndex = ui.treeView->currentIndex();
        if (curIndex.isValid())
        {

            auto curItem = static_cast<layerStandardItem*>((model->itemFromIndex(curIndex)));
            if (curItem != nullptr)
            {
               
                // ��ȡ�û�������ı�
                bool ok;
                QString text = QInputDialog::getText(this, QStringLiteral("�޸�"), QStringLiteral("�������޸�����:"), QLineEdit::Normal, curItem->gTreeData->gName.c_str(), &ok);
                if (ok && !text.isEmpty())
                {
                    // �������ݺ�UI
                    curItem->gTreeData->gName = text.toStdString();
                    curItem->setText(text);
                    PrintLog(QStringLiteral("�޸����"));
                }
            }

        }

        });

    QAction* a4 = new QAction(QStringLiteral("ɾ��"));
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
    //���˵�������


    //����һЩTree����.
    {
        model = new QStandardItemModel(ui.treeView); //ָ�������󣬱����ڴ����
        model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("����") << QStringLiteral("˵��"));
        ui.treeView->setModel(model);//��������Model,�ؼ�.

        rootItem1 = new layerStandardItem(QStringLiteral("ͼ��1"));//ͼ��1
        model->appendRow(rootItem1);
        layerStandardItem* childItem1_1 = new layerStandardItem(QStringLiteral("������"));
        rootItem1->appendRow(childItem1_1);
        layerStandardItem* childItem1_2 = new layerStandardItem(QStringLiteral("�ı���"));
        rootItem1->appendRow(childItem1_2);
        rootItem1->appendRow(new layerStandardItem(QStringLiteral("����1")));
        rootItem1->appendRow(new layerStandardItem(QStringLiteral("����2")));

        rootItem2 = new layerStandardItem(QStringLiteral("ͼ��2"));
        model->appendRow(rootItem2);
        //model->setItem(model->indexFromItem(rootItem2).row(), 1, new layerStandardItem(QStringLiteral("�ƺ�¥")));//���õڶ�������.

        layerStandardItem* childItem2_1 = new layerStandardItem(QStringLiteral("����"));
        rootItem2->appendRow(childItem2_1);
        //rootItem2->setChild(childItem2_1->index().row(), 1, new layerStandardItem(QStringLiteral("���н�")));//�ڵڶ�����������.

        layerStandardItem* childItem2_2 = new layerStandardItem(QStringLiteral("����")); //ע������->rootItem2,ͨ���������������ڵ���.
        rootItem2->appendRow(childItem2_2);
        //rootItem2->setChild(childItem2_2->index().row(),1,new layerStandardItem(QStringLiteral("����¥")));

        rootItem2->appendRow(new layerStandardItem(QStringLiteral("����")));
    }

    

}
void IMGPro::updateTreeView()
{
    // �������ģ��
    model->clear();
    model = new QStandardItemModel(ui.treeView); //ָ�������󣬱����ڴ����
    model->setHorizontalHeaderLabels(QStringList() << QStringLiteral("����") << QStringLiteral("˵��"));
    ui.treeView->setModel(model);//��������Model,�ؼ�.
    // �������Ӹ��ڵ�
    rootItem1 = new layerStandardItem(QStringLiteral("ͼ��1"));//ͼ��1
    rootItem2 = new layerStandardItem(QStringLiteral("ͼ��2"));
    model->appendRow(rootItem1);
    model->appendRow(rootItem2);

    // ��ȡ�����е���
    QList<QGraphicsItem*> items = drawingContext.scene->items();

    // ���������е��������Ӧ��layerStandardItem
    for (QGraphicsItem* item : items) {
        // ���˵���ָ�����͵���
        if (item->type() != QGraphicsPolygonItem::Type && item->type() != QGraphicsEllipseItem::Type) {
            continue;
        }

        // ��ȡ�������
        QString name = item->data(Qt::UserRole).toString();

        // ����layerStandardItem������������Ϊ�������
        layerStandardItem* layerItem = new layerStandardItem(name);

        // ��layerStandardItem���ӵ���Ӧ�ĸ��ڵ�
        if (item->type() == QGraphicsPolygonItem::Type) {
            rootItem1->appendRow(layerItem);
        }
        else if (item->type() == QGraphicsEllipseItem::Type) {
            rootItem2->appendRow(layerItem);
        }
    }
}



/// <summary>
/// �Ҽ��˵�...
/// </summary>
/// <param name="pos"></param>
void IMGPro::on_treeView_customContextMenuRequested(const QPoint& pos)
{
    if (ui.treeView->hasFocus()) {

        menu->exec(this->mapToGlobal(pos));
    }
}


//connect�������ּǵ�ctrl+Fֱ����connect



//�ۺ���ʵ�ֲ���



void IMGPro::setStateInMain1(int i) //������
{
    //drawingContext.setCurrentState(new DrawingLINESTRING());
    //drawingContext.draw();

    //QAction* senderAction = qobject_cast<QAction*>(sender());
    if (i) {
        drawingContext.isDrawing= 1;
        if (i == 1) {//��
            // �����߶���ز���
            drawingContext.setCurrentState(new DrawingLINESTRING());
            
            drawingContext.type = 1;
        }
        else if (i == 2) {//��
            drawingContext.setCurrentState(new DrawingPOINT());
            //drawingContext.draw();
            drawingContext.type = 2;
        }
        else if (i == 3) {//�����
            drawingContext.setCurrentState(new DrawingPOLYGON());
            //drawingContext.draw();
            drawingContext.type = 3;
        }
        else if (i == 4) {//Բ
            drawingContext.setCurrentState(new DrawingCIRCLE());
            //drawingContext.draw();
            drawingContext.type = 4;
        }
        else if (i == 5) {//����
            drawingContext.setCurrentState(new DrawingSECTOR());
            //drawingContext.draw();
            drawingContext.type = 5;
        }
        else if (i == 6) {
            drawingContext.setCurrentState(new DrawingTEXT());//�ı�
            //drawingContext.draw();
            drawingContext.type = 6;
        }
        else if (i == 7) {
            drawingContext.setCurrentState(new DrawingBITMAP());//λͼ
            //drawingContext.draw();
            drawingContext.type = 7;
        }
    }
}
void IMGPro::select_on() {
    if (drawingContext.isSelecting == 1) { 
        drawingContext.isSelecting = 0;
        
        ui.label->setText(QStringLiteral("������δѡ��״̬"));
    }

    else if (drawingContext.isSelecting == 0)
    { 
        drawingContext.isSelecting = 1;
        drawingContext.scene->clearSelection();
        ui.label->setText(QStringLiteral("������ѡ��״̬"));
        //drawingContext.setCurrentState(NULL);

    }
    
}

void IMGPro::save() {
    // �����ļ�����Ի������û�ѡ�񱣴���ļ�·��������
    QString filePath = QFileDialog::getSaveFileName(this, QStringLiteral("����ͼ��"), "", QStringLiteral("PNG �ļ�(*.png)"));

    if (!filePath.isEmpty()) {
        // ����һ���հ׵�QPixmap����
        QPixmap pixmap(drawingContext.scene->sceneRect().size().toSize());

        // ʹ��QPainter��QPixmap�ϻ��Ƴ���
        QPainter painter(&pixmap);
        drawingContext.scene->render(&painter);

        // ���浼����pixmapΪͼ���ļ�
        pixmap.save(filePath);
    }

}

void IMGPro::shuaxing() {
    drawingContext.shuaxing();
    //updateTreeView();
}

void IMGPro::savetxt()
{
    
        // �����ļ�����Ի���
        QString fileName = QFileDialog::getSaveFileName(this, QStringLiteral("�����ļ�"), QString(), QStringLiteral("�ı��ļ� (*.txt)"));
        if (fileName.isEmpty()) {
            return;
        }

        // �����������������д���ļ�
        drawingContext.outputArraysToTxt(fileName);
        QMessageBox::information(this, QStringLiteral("��ʾ"), QStringLiteral("�ɹ�����"));
  
}





