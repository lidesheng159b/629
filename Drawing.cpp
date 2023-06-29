#include<iostream>
#include"Drawing.h"
#include"layerStandardItem.h"
using namespace std;

Ui::IMGProClass* Dui = nullptr;


void ui_init(Ui::IMGProClass* ui_ptr)
{
    Dui = ui_ptr;
}





//--------------------------------------------------------
void DrawingContext::draw() {
    if (currentState)
    {
        currentState->draw();
    }
    else
    {
        QMessageBox::critical(Dui->centralWidget, QStringLiteral("错误"), QStringLiteral("还未选择绘制模式"));
    }
}

void DrawingContext::mousePressEvent(QMouseEvent* event) {

    //线1 点2 多边形3 圆4 扇形5
    if (isSelecting == 0) {
        if (event->button() == Qt::LeftButton && currentState) {
            QPointF scenePos = mapToScene(event->pos());
            //多边形
            if (type == 3 && isDrawing == 1) {
                // 绘制多边形
                QPen pen(Qt::black, 3);  // 设置画笔，线条宽度为3
                if (PL.isEmpty()) {
                    PL.push_back(QVector<QPoint>());
                }
                PL.back().append(scenePos.toPoint());
                 //创建多边形图形项
                QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem();

                // 清除场景中的所有项
                polygonItem->setPolygon(QPolygonF());
                scene->clear();
               
                QPolygonF polygon;
                foreach(const QPoint & point, PL.back()) {
                    polygon << point;
                }
                polygonItem->setPolygon(polygon);
                // 添加图形项到场景
                // 添加之前的多边形图形项到场景
                foreach(const QVector<QPoint>&polygonPoints, PL) {
                    QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem();
                    QPolygonF polygon;
                    foreach(const QPoint & point, polygonPoints) {
                        polygon << point;
                    }
                    polygonItem->setPen(pen);
                    polygonItem->setPolygon(polygon);
                    scene->addItem(polygonItem);
                }
                //scene->addItem(polygonItem);
            }
            //扇形
            else if (type == 5 && isDrawing == 1) {//扇形
                if (event->button() == Qt::LeftButton) {
                    // 获取点击位置
                    QPointF clickPos = mapToScene(event->pos());
                    QVector<int> sectorData;
                    // 弹出对话框让用户输入扇形相关数据
                    QDialog dialog;
                    QVBoxLayout layout(&dialog);
                    QLabel radiusLabel(QStringLiteral("半径:"));
                    QLineEdit radiusLineEdit;
                    QLabel startAngleLabel(QStringLiteral("起始角度:"));
                    QLineEdit startAngleLineEdit;
                    QLabel spanAngleLabel(QStringLiteral("扇形角度:"));
                    QLineEdit spanAngleLineEdit;
                    QPushButton okButton(QStringLiteral("确定"));

                    layout.addWidget(&radiusLabel);
                    layout.addWidget(&radiusLineEdit);
                    layout.addWidget(&startAngleLabel);
                    layout.addWidget(&startAngleLineEdit);
                    layout.addWidget(&spanAngleLabel);
                    layout.addWidget(&spanAngleLineEdit);
                    layout.addWidget(&okButton);

                    connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

                    if (dialog.exec() != QDialog::Accepted) {
                        return;
                    }

                    // 读取输入的数据
                    bool ok;
                    qreal radius = radiusLineEdit.text().toDouble(&ok);
                    if (!ok) {
                        QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("半径值无效"));
                        return;
                    }

                    int startAngle = startAngleLineEdit.text().toInt(&ok);
                    if (!ok) {
                        QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("半径值无效"));
                        return;
                    }

                    int spanAngle = spanAngleLineEdit.text().toInt(&ok);
                    if (!ok) {
                        QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("半径值无效"));
                        return;
                    }

                    // 创建扇形图元并添加到场景中
                    QGraphicsEllipseItem* sectorItem = new QGraphicsEllipseItem(clickPos.x() - radius, clickPos.y() - radius, 2 * radius, 2 * radius);
                    sectorItem->setStartAngle(startAngle * 16);
                    sectorItem->setSpanAngle(spanAngle * 16);
                    scene->addItem(sectorItem);
                    // 绘制完扇形后将数据存储到sectorData
                    sectorData.append(clickPos.x());
                    sectorData.append(clickPos.y());
                    sectorData.append(radius);
                    sectorData.append(startAngle);
                    sectorData.append(spanAngle);

                    // 将sectorData添加到扇形数组SEC
                    SEC.append(sectorData);
                }
            }
            //圆形
            else if (type == 4 && isDrawing == 1) {
                // 圆形绘制
                if (C.isEmpty()) {
                    C.push_back(QVector<QPoint>());
                }
                if (C.back().size() == 2) {
                    C.push_back(QVector<QPoint>());
                }
                if (C.back().isEmpty()) {
                    C.back().append(scenePos.toPoint());
                }

            }

            //折线
            else if (type == 1 && isDrawing == 1) {
                // 将鼠标点击位置转换为场景坐标
                QPointF scenePos = mapToScene(event->pos());
                if (L.isEmpty()) { L.append(QVector<QPoint>()); }

                L.back().append(scenePos.toPoint());


                // 清除场景中的所有项
                scene->clear();

                // 创建折线图形项
                for (int i = 0; i < L.size(); i++) {
                    QPolygonF polyline;
                    foreach(const QPoint & point, L[i]) {
                        polyline << point;
                    }
                    PolylineItem* polylineItem = new PolylineItem(polyline);
                    // 设置折线的样式，如颜色、线宽等
                    QPen pen(Qt::black, 3);
                    polylineItem->setPen(pen);

                    // 添加折线图形项到场景
                    scene->addItem(polylineItem);
                }

            }
            //点
            else if (type == 2 && isDrawing == 1) {//点

                QPointF scenePos = mapToScene(event->pos());
                P.append(scenePos.toPoint());
                for (int i = 0; i < P.size(); i++) {
                    QPointF point; // 点的坐标
                    point= P[i];
                    QGraphicsEllipseItem* pointItem = new QGraphicsEllipseItem(point.x() - 2, point.y() - 2, 4, 4); // 创建一个椭圆图形项，大小为4x4
                    pointItem->setBrush(Qt::black); // 设置椭圆的填充颜色
                    scene->addItem(pointItem); // 将图形项添加到场景中
                }

            }
            //文本
            else if (type == 6 && isDrawing == 1) {
                // 获取鼠标点击位置
                QPointF mousePos = mapToScene(event->pos());

                // 弹出对话框获取用户输入的文本
                QString userInput = QInputDialog::getText(this, QStringLiteral("输入文本"), QStringLiteral("请输入文本:"));

                // 创建文本项
                QGraphicsTextItem* textItem = new QGraphicsTextItem(userInput);
                textItem->setPos(mousePos);

                // 将文本项添加到场景中
                scene->addItem(textItem);
            }
            //位图
            else if (type == 7 && isDrawing == 1) {
                // 加载位图文件
               // 打开文件对话框选择位图文件
               QString filePath = QFileDialog::getOpenFileName(this, QStringLiteral( "选择位图文件"), "", QStringLiteral("位图文件 (*.png *.jpg *.bmp)"));

               // 加载位图文件
               if (!filePath.isEmpty()) {
                   QPixmap pixmap(filePath);

                   // 创建位图图形项
                   QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);

                   // 设置位图的位置
                   pixmapItem->setPos(scenePos);

                   // 添加位图图形项到场景
                   scene->addItem(pixmapItem);
               }

            }
        }
    }
    if (isSelecting == 1) {
        if (event->button() == Qt::LeftButton) {
            // 获取鼠标点击位置
            QPointF scenePos = mapToScene(event->pos());

            // 获取位于点击位置的图形项
            QList<QGraphicsItem*> items = scene->items(scenePos);

            // 遍历图形项，判断是否选中
            for (QGraphicsItem* item : items) {
                // 判断图形项是否是你绘制的特定类型，可以根据自己的需求进行判断
                if (1) {
                    // 将图形项标记为选中状态
                    item->setSelected(true);
                    
                    // 在这里可以进行选中图形项的处理，比如改变颜色或者边框样式
                    item->setFlag(QGraphicsItem::ItemIsSelectable, true);
                   item->setFlag(QGraphicsItem::ItemIsMovable, true);
                    //item->setFlag(QGraphicsItem::ItemIsFocusable, true);
                    //item->setFocus();
                }
            }
        }
    }
    if (event->button() == Qt::RightButton) {
        QPointF scenePos = mapToScene(event->pos());
        QGraphicsItem* selectedItem = scene->itemAt(scenePos, transform());

        if (selectedItem != nullptr) {
            // 创建一个自定义对话框
            QDialog dialog;
            dialog.setWindowTitle(QStringLiteral("选择操作"));

            QVBoxLayout layout(&dialog);
            QLabel label(QStringLiteral("请选择要执行的操作:"));
            layout.addWidget(&label);

            QPushButton deleteButton(QStringLiteral("删除"));
            QPushButton hideButton(QStringLiteral("隐藏"));

            layout.addWidget(&deleteButton);
            layout.addWidget(&hideButton);

            QObject::connect(&deleteButton, &QPushButton::clicked, [&]() {
                // 执行删除操作
                scene->removeItem(selectedItem);
                delete selectedItem;
                dialog.accept();
                });

            QObject::connect(&hideButton, &QPushButton::clicked, [&]() {
                // 执行隐藏操作
                selectedItem->setVisible(false);
                dialog.accept();
                });

            dialog.exec();
        }
    }

}

void DrawingContext::mouseReleaseEvent(QMouseEvent* event) {
    if (type == 4 && isDrawing == 1 && isSelecting == 0)
    {
        QPointF scenePos = mapToScene(event->pos());
        QPen pen(Qt::black, 3);  // 设置画笔，线条宽度为3
        C.back().append(scenePos.toPoint());

        // 遍历 C 中的数组，添加图形项到场景
        foreach(const QVector<QPoint>&circlepoints, C) {
            if (circlepoints.size() < 2) continue;
            QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem();
            QPoint start = circlepoints.front();  // 使用 circlepoints.front() 获取起点坐标
            QPoint end = circlepoints.back();  // 使用 circlepoints.back() 获取终点坐标
            int radius = qSqrt(qPow(start.x() - end.x(), 2) + qPow(start.y() - end.y(), 2));
            QRectF circleRect(start.x() - radius, start.y() - radius, radius * 2, radius * 2);
            ellipseItem->setPen(pen);
            ellipseItem->setRect(circleRect);

            // 添加图形项到场景
            scene->addItem(ellipseItem);
        }
    }

}

void DrawingContext::mouseMoveEvent(QMouseEvent* event) {
    setMouseTracking(true);//实时检测鼠标位置
    if (type == 4 && isDrawing == 1)//用于圆形的实时绘制
    {
       
    }
    if (isSelecting == 1 && SEL.size() != 0)//处于选中状态且选中了图形
    {
        //线1 点2 多边形3 圆4 扇形5
        double dx, dy;
        if (event->buttons() & Qt::LeftButton)//左键一直按下
        {
            p2 = event->pos();//p2与p1有次序，p1每次会记录p2上次的位置，作为平移的x,y小量增加基准。
            if (p1.x() != 0 && p1.y() != 0)//跳过第一次，即让p1记录第一次p2的位置。
            {
                dx = p2.x() - p1.x();//标识平移距离
                dy = p2.y() - p1.y();//标识平移距离
                if (SEL[c][0] == 1)//线
                {
                    L[SEL[c][1]][0].rx() += dx;//rx可修改
                    L[SEL[c][1]][0].ry() += dy;
                    L[SEL[c][1]][1].rx() += dx;
                    L[SEL[c][1]][1].ry() += dy;
                }
                else if (SEL[c][0] == 4)//圆形
                {
                    C[SEL[c][1]][0].rx() += dx;
                    C[SEL[c][1]][0].ry() += dy;
                    C[SEL[c][1]][1].rx() += dx;
                    C[SEL[c][1]][1].ry() += dy;
                }
                else if (SEL[c][0] == 3)//多边形
                {
                    for (int i = 0; i < PL[SEL[c][1]].size(); i++)
                    {
                        PL[SEL[c][1]][i].rx() += dx;
                        PL[SEL[c][1]][i].ry() += dy;
                    }
                }
                /*else if (SEL[c][0] == 4)
                {
                    C[SEL[c][1]][0].rx() += dx;
                    R[SEL[c][1]][0].ry() += dy;
                    R[SEL[c][1]][1].rx() += dx;
                    R[SEL[c][1]][1].ry() += dy;
                    R[SEL[c][1]][2].rx() += dx;
                    R[SEL[c][1]][2].ry() += dy;
                    R[SEL[c][1]][3].rx() += dx;
                    R[SEL[c][1]][3].ry() += dy;
                }*/

            }
            p1 = p2;
            this->viewport()->update();//窗口重绘函数
        }
    }
    // 在图形项被选中后，使用鼠标移动事件进行移动
    if (event->buttons() && !(Qt::LeftButton&& scene->selectedItems().isEmpty())) {
       
        // 遍历选中的图形项
        for (QGraphicsItem* item : scene->selectedItems()) {
            // 将图形项移动到当前位置
            item->setPos(mapToScene(event->pos()));
        }
    }
    
}

void DrawingContext::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Plus) {//+号添加，回车结束绘制
        if (type == 3) {//多边形
            PL.push_back(QVector<QPoint>());//就加一个空栈
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            //this->viewport()->update();
        }
        if (type == 4) {//圆形
            C.push_back(QVector<QPoint>());//就加一个空栈
            isDrawing = 1;
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            this->viewport()->update();
        }
        if (type == 1) {//线
            L.push_back(QVector<QPoint>());//就加一个空栈
            isDrawing = 1;
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            this->viewport()->update();
        }
        if (type == 2) {//点
            P.push_back(QPoint());
            isDrawing = 1;
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            this->viewport()->update();
        }
    }

    if (event->key() == Qt::Key_Up)
    {
        QList<QGraphicsItem*> selectedItems = scene->selectedItems();
        for (QGraphicsItem* item : selectedItems) {
            QPointF itemCenter = item->boundingRect().center();
            item->setTransformOriginPoint(itemCenter);
            item->setRotation(item->rotation() - 15);
        }
    }
    if (event->key() == Qt::Key_Down) {
        
        QList<QGraphicsItem*> selectedItems = scene->selectedItems();
        for (QGraphicsItem* item : selectedItems) {
            QPointF itemCenter = item->boundingRect().center();
            item->setTransformOriginPoint(itemCenter);
            item->setRotation(item->rotation() + 15);
        }
    }



    if (event->key() == Qt::Key_Backspace) {
        // 获取场景中的选中项
        QList<QGraphicsItem*> selectedItems = scene->selectedItems();

        // 遍历选中项，从场景和数据模型中删除它们
        for (QGraphicsItem* item : selectedItems) {
            scene->removeItem(item);
           
        }
    }
    
    
}

void DrawingContext::wheelEvent(QWheelEvent* event)
{
    
    // 获取滚轮的滚动方向和滚动的步数
    int delta = event->angleDelta().y();

    // 定义缩放因子
    double scaleFactor = 1.2;

    // 获取鼠标在视图中的位置
    QPointF mousePos = mapToScene(event->pos());

    // 根据滚动方向调整缩放因子
    if (delta > 0) {
        // 向上滚动，放大视图
        scale(scaleFactor, scaleFactor);
    }
    else {
        // 向下滚动，缩小视图
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    

}

//void DrawingContext::contextMenuEvent(QContextMenuEvent* event)
//{
//    QMenu menu(this);
//
//    QAction* colorAction = menu.addAction("修改颜色");
//    QAction* fillStyleAction = menu.addAction("修改填充样式");
//
//    QAction* selectedItem = menu.exec(event->globalPos());
//
//    if (selectedItem == colorAction) {
//        // 处理修改颜色的操作
//        QColor newColor = QColorDialog::getColor(Qt::black, this, "选择颜色");
//        if (newColor.isValid()) {
//            
//        }
//    }
//    else if (selectedItem == fillStyleAction) {
//        // 处理修改填充样式的操作
//        // 这里可以使用类似的方法弹出对话框来选择填充样式，并将其应用到Painter中
//    }
//}
//
//
//void DrawingContext::mouseDoubleClickEvent(QMouseEvent* event)
//{
//    QPointF pointfScene = mapToScene(event->pos());
//    QGraphicsItem* itemScene = scene->itemAt(pointfScene, transform());
//    if (itemScene == nullptr)
//        return;
//
//    switch (itemScene->type())
//    {
//    case QGraphicsRectItem::Type: {
//        QGraphicsRectItem* item = qgraphicsitem_cast<QGraphicsRectItem*>(itemScene);
//        QColor fillColor = item->brush().color();
//        QColor penColor = item->pen().color();
//        fillColor = QColorDialog::getColor(fillColor, nullptr, "Choose a fill color");
//        penColor = QColorDialog::getColor(penColor, nullptr, "Choose a pen color");
//        if (fillColor.isValid())
//            item->setBrush(QBrush(fillColor));
//        if (penColor.isValid())
//            item->setPen(QPen(penColor));
//        break;
//    }
//    case QGraphicsEllipseItem::Type: {
//        QGraphicsEllipseItem* item = qgraphicsitem_cast<QGraphicsEllipseItem*>(itemScene);
//        QColor fillColor = item->brush().color();
//        QColor penColor = item->pen().color();
//        fillColor = QColorDialog::getColor(fillColor, nullptr, "Choose a fill color");
//        penColor = QColorDialog::getColor(penColor, nullptr, "Choose a pen color");
//        if (fillColor.isValid())
//            item->setBrush(QBrush(fillColor));
//        if (penColor.isValid())
//            item->setPen(QPen(penColor));
//        break;
//    }
//    case QGraphicsPolygonItem::Type: {
//        QGraphicsPolygonItem* item = qgraphicsitem_cast<QGraphicsPolygonItem*>(itemScene);
//        QColor fillColor = item->brush().color();
//        QColor penColor = item->pen().color();
//        fillColor = QColorDialog::getColor(fillColor, nullptr, "Choose a fill color");
//        penColor = QColorDialog::getColor(penColor, nullptr, "Choose a pen color");
//        if (fillColor.isValid())
//            item->setBrush(QBrush(fillColor));
//        if (penColor.isValid())
//            item->setPen(QPen(penColor));
//        break;
//    }
//    case QGraphicsLineItem::Type: {
//        QGraphicsLineItem* item = qgraphicsitem_cast<QGraphicsLineItem*>(itemScene);
//        QColor penColor = item->pen().color();
//        penColor = QColorDialog::getColor(penColor, nullptr, "Choose a pen color");
//        if (penColor.isValid())
//            item->setPen(QPen(penColor));
//        break;
//    }
//    case QGraphicsTextItem::Type: {
//        QGraphicsTextItem* item = qgraphicsitem_cast<QGraphicsTextItem*>(itemScene);
//        QColor penColor = item->defaultTextColor();
//        penColor = QColorDialog::getColor(penColor, nullptr, "Choose a pen color");
//        if (penColor.isValid())
//            item->setDefaultTextColor(penColor);
//        break;
//    }
//    default:
//        break;
//    }
//}


void DrawingContext::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPointF pointfScene = mapToScene(event->pos());
    QGraphicsItem* itemScene = scene->itemAt(pointfScene, transform());
    if (itemScene == nullptr)
        return;

    // 弹出选择对话框
    QMessageBox dialog;
    dialog.setText(QStringLiteral("请选择要修改的属性"));
    dialog.addButton(QStringLiteral("边框"), QMessageBox::AcceptRole);
    dialog.addButton(QStringLiteral("填充"), QMessageBox::AcceptRole);
    dialog.addButton(QStringLiteral("样式"), QMessageBox::AcceptRole);
    dialog.exec();

    QString selectedOption = dialog.clickedButton()->text();

    if (selectedOption == QStringLiteral("边框")) {
        // 修改填充颜色
        QColor penColor;

        // 获取图形项的类型
        switch (itemScene->type()) {
        case QGraphicsRectItem::Type: {
            QGraphicsRectItem* item = qgraphicsitem_cast<QGraphicsRectItem*>(itemScene);
            penColor = item->pen().color();
            break;
        }
        case QGraphicsEllipseItem::Type: {
            QGraphicsEllipseItem* item = qgraphicsitem_cast<QGraphicsEllipseItem*>(itemScene);
            penColor = item->pen().color();
            break;
        }
        case QGraphicsPolygonItem::Type: {
            QGraphicsPolygonItem* item = qgraphicsitem_cast<QGraphicsPolygonItem*>(itemScene);
            penColor = item->pen().color();
            break;
        }
        default:
            break;
        }

        penColor = QColorDialog::getColor(penColor, nullptr, QStringLiteral("选择边框颜色"));
        if (penColor.isValid()) {
            switch (itemScene->type()) {
            case QGraphicsRectItem::Type: {
                QGraphicsRectItem* item = qgraphicsitem_cast<QGraphicsRectItem*>(itemScene);
                item->setPen(QPen(penColor));
                break;
            }
            case QGraphicsEllipseItem::Type: {
                QGraphicsEllipseItem* item = qgraphicsitem_cast<QGraphicsEllipseItem*>(itemScene);
                item->setPen(QPen(penColor));
                break;
            }
            case QGraphicsPolygonItem::Type: {
                QGraphicsPolygonItem* item = qgraphicsitem_cast<QGraphicsPolygonItem*>(itemScene);
                item->setPen(QPen(penColor));
                break;
            }
            default:
                break;
            }
        }
    
    }
    else if (selectedOption == QStringLiteral("填充") ){
        // 修改填充颜色
        QColor fillColor;

        // 获取图形项的类型
        switch (itemScene->type()) {
        case QGraphicsRectItem::Type: {
            QGraphicsRectItem* item = qgraphicsitem_cast<QGraphicsRectItem*>(itemScene);
            fillColor = item->brush().color();
            break;
        }
        case QGraphicsEllipseItem::Type: {
            QGraphicsEllipseItem* item = qgraphicsitem_cast<QGraphicsEllipseItem*>(itemScene);
            fillColor = item->brush().color();
            break;
        }
        case QGraphicsPolygonItem::Type: {
            QGraphicsPolygonItem* item = qgraphicsitem_cast<QGraphicsPolygonItem*>(itemScene);
            fillColor = item->brush().color();
            break;
        }
        default:
            break;
        }

        fillColor = QColorDialog::getColor(fillColor, nullptr, QStringLiteral("选择填充颜色"));
        if (fillColor.isValid()) {
            switch (itemScene->type()) {
            case QGraphicsRectItem::Type: {
                QGraphicsRectItem* item = qgraphicsitem_cast<QGraphicsRectItem*>(itemScene);
                item->setBrush(QBrush(fillColor));
                break;
            }
            case QGraphicsEllipseItem::Type: {
                QGraphicsEllipseItem* item = qgraphicsitem_cast<QGraphicsEllipseItem*>(itemScene);
                item->setBrush(QBrush(fillColor));
                break;
            }
            case QGraphicsPolygonItem::Type: {
                QGraphicsPolygonItem* item = qgraphicsitem_cast<QGraphicsPolygonItem*>(itemScene);
                item->setBrush(QBrush(fillColor));
                break;
            }
            default:
                break;
            }
        }
    }
    else if (selectedOption == QStringLiteral("样式")) {
        // 修改填充样式
        QGraphicsItem* item = itemScene;
        QStringList styleOptions;
        styleOptions << QStringLiteral("无样式") << QStringLiteral("网纹") << QStringLiteral("水平线") << QStringLiteral("垂直线") << QStringLiteral("斜线");

        bool ok;
        QString selectedStyle = QInputDialog::getItem(this, QStringLiteral("选择填充样式"), QStringLiteral("填充样式:"), styleOptions, 3, false, &ok);

        if (ok) {
            Qt::BrushStyle brushStyle = Qt::NoBrush;

            if (selectedStyle == QStringLiteral("网纹")) {
                brushStyle = Qt::Dense1Pattern;
            }
            else if (selectedStyle == QStringLiteral("水平线")) {
                brushStyle = Qt::HorPattern;
            }
            else if (selectedStyle == QStringLiteral("垂直线")) {
                brushStyle = Qt::VerPattern;
            }
            else if (selectedStyle == QStringLiteral("斜线")) {
                brushStyle = Qt::BDiagPattern;
            }
            // 添加更多样式的处理


            switch (itemScene->type()) {
            case QGraphicsRectItem::Type: {
                QGraphicsRectItem* rectItem = qgraphicsitem_cast<QGraphicsRectItem*>(item);
                rectItem->setBrush(QBrush(rectItem->brush().color(), brushStyle));
                break;
            }
            case QGraphicsEllipseItem::Type: {
                QGraphicsEllipseItem* ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
                ellipseItem->setBrush(QBrush(ellipseItem->brush().color(), brushStyle));
                break;
            }
            case QGraphicsPolygonItem::Type: {
                QGraphicsPolygonItem* polygonItem = qgraphicsitem_cast<QGraphicsPolygonItem*>(item);
                polygonItem->setBrush(QBrush(polygonItem->brush().color(), brushStyle));
                break;
            }
            default:
                break;
            }
        }
    }


}

void DrawingContext::shuaxing()
{
    QPen pen(Qt::black, 3);  // 设置画笔，线条宽度为3
    scene->clear();
    //多边形
    foreach(const QVector<QPoint>&polygonPoints, PL) {
        QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem();
        QPolygonF polygon;
        foreach(const QPoint & point, polygonPoints) {
            polygon << point;
        }
        
        polygonItem->setPen(pen);
        polygonItem->setPolygon(polygon);
        scene->addItem(polygonItem);
    }
    //扇形
    for (int i = 0; i < SEC.size(); i++) {
        qreal x = SEC[i][0];
        qreal y = SEC[i][1];
        qreal r = SEC[i][2]; 
        qreal startAngle= SEC[i][3];
        qreal spanAngle= SEC[i][4];
        QGraphicsEllipseItem* sectorItem = new QGraphicsEllipseItem(x-r, y-r,2*r, 2*r);
        sectorItem->setStartAngle(startAngle * 16);
        sectorItem->setSpanAngle(spanAngle * 16);
        scene->addItem(sectorItem);
    }
    //圆形
    foreach(const QVector<QPoint>& circlepoints, C) {
        if (circlepoints.size() < 2) continue;
        QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem();
        QPoint start = circlepoints.front();  // 使用 circlepoints.front() 获取起点坐标
        QPoint end = circlepoints.back();  // 使用 circlepoints.back() 获取终点坐标
        int radius = qSqrt(qPow(start.x() - end.x(), 2) + qPow(start.y() - end.y(), 2));
        QRectF circleRect(start.x() - radius, start.y() - radius, radius * 2, radius * 2);
        ellipseItem->setPen(pen);
        ellipseItem->setRect(circleRect);

        // 添加图形项到场景
        scene->addItem(ellipseItem);
    }
    //折线
    
    for (int i = 0; i < L.size(); i++) {
        QPolygonF polyline;
        foreach(const QPoint & point, L[i]) {
            polyline << point;
        }
        PolylineItem* polylineItem = new PolylineItem(polyline);
        // 设置折线的样式，如颜色、线宽等
        QPen pen(Qt::black, 3);
        polylineItem->setPen(pen);

        // 添加折线图形项到场景
        scene->addItem(polylineItem);
    }



}

//void DrawingContext::shuaxing()
//{
//    QPen pen(Qt::black, 3);  // 设置画笔，线条宽度为3
//    scene->clear();
//
//    for (const auto& polygonPoints : PL) {
//        QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem();
//        QPolygonF polygon;
//        for (const auto& point : polygonPoints) {
//            polygon << point;
//        }
//
//        polygonItem->setPen(pen);
//        polygonItem->setPolygon(polygon);
//        scene->addItem(polygonItem);
//
//        layerStandardItem* item = new layerStandardItem("Polygon");
//        item->setGraphicsItem(polygonItem);
//        
//       
//        Dui->treeView->addItem(item);
//        QModelIndex newItemIndex = model->indexFromItem(item);
//        ui.treeView->setExpanded(newItemIndex, true);
//        ui.treeView->scrollTo(newItemIndex);
//        item->setCheckable(true);
//        item->setCheckState(Qt::Checked);
//    }
//
//    for (const auto& sec : SEC) {
//        qreal x = sec[0];
//        qreal y = sec[1];
//        qreal r = sec[2];
//        qreal startAngle = sec[3];
//        qreal spanAngle = sec[4];
//        QGraphicsEllipseItem* sectorItem = new QGraphicsEllipseItem(x - r, y - r, 2 * r, 2 * r);
//        sectorItem->setStartAngle(startAngle * 16);
//        sectorItem->setSpanAngle(spanAngle * 16);
//        scene->addItem(sectorItem);
//
//        layerStandardItem* item = new layerStandardItem("Sector");
//        item->setGraphicsItem(sectorItem);
//        treeView->addTopLevelItem(item);
//        item->setCheckable(true);
//        item->setCheckState(Qt::Checked);
//    }
//
//    for (const auto& circlePoints : C) {
//        if (circlePoints.size() < 2)
//            continue;
//
//        QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem();
//        QPoint start = circlePoints.front();
//        QPoint end = circlePoints.back();
//        int radius = qSqrt(qPow(start.x() - end.x(), 2) + qPow(start.y() - end.y(), 2));
//        QRectF circleRect(start.x() - radius, start.y() - radius, radius * 2, radius * 2);
//        ellipseItem->setPen(pen);
//        ellipseItem->setRect(circleRect);
//
//        scene->addItem(ellipseItem);
//
//        layerStandardItem* item = new layerStandardItem("Circle");
//        item->setGraphicsItem(ellipseItem);
//        treeView->addTopLevelItem(item);
//        item->setCheckable(true);
//        item->setCheckState(Qt::Checked);
//    }
//
//    for (const auto& polylinePoints : L) {
//        QPolygonF polyline;
//        for (const auto& point : polylinePoints) {
//            polyline << point;
//        }
//        PolylineItem* polylineItem = new PolylineItem(polyline);
//        QPen pen(Qt::black, 3);
//        polylineItem->setPen(pen);
//
//        scene->addItem(polylineItem);
//
//        layerStandardItem* item = new layerStandardItem("Polyline");
//        item->setGraphicsItem(polylineItem);
//        treeView->addTopLevelItem(item);
//        item->setCheckable(true);
//        item->setCheckState(Qt::Checked);
//    }
//}



void DrawingContext::outputArraysToTxt(const const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "无法打开文件：" << fileName;
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");  // 设置文本流的编码为UTF-8

    // 输出多边形数组
    out << QStringLiteral( "多边形数据：") << endl;
    int polygonIndex = 1;
    for (const QVector<QPoint>& polygonPoints : PL) {
        out << QStringLiteral("polygon ") << polygonIndex << QStringLiteral("：") << endl;
        for (const QPoint& point : polygonPoints) {
            out << QStringLiteral("x: ") << point.x() << QStringLiteral(", y: ") << point.y() << endl;
        }
        polygonIndex++;
    }


    // 输出扇形数组
    out << QStringLiteral("扇形数据：") << endl;
    int Index = 1;
    for (const QVector<int>& sectorData : SEC) {
        out << QStringLiteral( "sector：") << endl;
        out << QStringLiteral("x: ") << sectorData[0] << QStringLiteral(", y: ") << sectorData[1] << QStringLiteral(", r: ") << sectorData[2] << QStringLiteral(", startAngle: ") << sectorData[3] << QStringLiteral(", spanAngle: ") << sectorData[4] << endl;
    }

    // 输出圆形数组
    out << QStringLiteral("圆形数据：") << endl;
    for (const QVector<QPoint>& circlePoints : C) {
        if (circlePoints.size() < 2) continue;
        QPoint start = circlePoints.front();
        QPoint end = circlePoints.back();
        int radius = qSqrt(qPow(start.x() - end.x(), 2) + qPow(start.y() - end.y(), 2));
        out << QStringLiteral("start：x:") << start.x() << QStringLiteral(", y: ") << start.y() << endl;
        out << QStringLiteral("终点坐标：x: ") << end.x() << QStringLiteral(", y: ") << end.y() << endl;
        out << QStringLiteral("半径：") << radius << endl;
    }

    // 输出折线数组
    out << QStringLiteral( "折线数据：") << endl;
    for (const QVector<QPoint>& polylinePoints : L) {
        out << QStringLiteral("折线：") << endl;
        for (const QPoint& point : polylinePoints) {
            out << QStringLiteral("x: ") << point.x() << QStringLiteral(", y: ") << point.y() << endl;
        }
    }

    file.close();
    
}


//****************************************************//
//              判断是否在图形内                       //
//                                                    //
// ***************************************************//
bool DrawingPOLYGON::IsContain(QPoint& p, QVector<QPoint> s)
{
    if (s.size() > 2) {
        if (s[0].x() == s[1].x())
        {
            QPoint p1 = s[0];
            QPoint p2 = s[2];
            if (p1.x() < p2.x() && p1.y() < p2.y())
            {
                if (p.x() >= p1.x() && p.x() <= p2.x() && p.y() >= p1.y() && p.y() <= p2.y())
                    return true;
                else return false;
            }
            else if (p1.x() < p2.x() && p1.y() > p2.y())
            {
                if (p.x() >= p1.x() && p.x() <= p2.x() && p.y() >= p2.y() && p.y() <= p1.y())
                    return true;
                else return false;
            }
            else if (p1.x() > p2.x() && p1.y() > p2.y())
            {
                if (p.x() >= p2.x() && p.x() <= p1.x() && p.y() >= p2.y() && p.y() <= p1.y())
                    return true;
                else return false;
            }
            else if (p1.x() > p2.x() && p1.y() < p2.y())
            {
                if (p.x() >= p2.x() && p.x() <= p1.x() && p.y() >= p1.y() && p.y() <= p2.y())
                    return true;
                else return false;
            }
        }
        else
        {
            int i, j = s.size() - 1;
            bool oddNodes = false;
            for (i = 0; i < s.size(); i++)
            {
                if (s[i].ry() < p.ry() && s[j].ry() >= p.ry() || s[j].ry() < p.ry() && s[i].ry() >= p.ry())
                {
                    if (s[i].x() + (p.y() - s[i].y()) / (s[j].y() - s[i].y()) * (s[j].x() - s[i].x()) < p.x())
                        oddNodes = !oddNodes;
                }
                j = i;
            }
            return oddNodes;
        }
    }
}

bool DrawingCIRCLE::IsContain(QPoint& p, QPoint p1, QPoint p2)
{
    int radius0 = qSqrt(qPow(p1.x() - p2.x(), 2) + qPow(p1.y() - p2.y(), 2));
    int radius1 = qSqrt(qPow(p1.x() - p.x(), 2) + qPow(p1.y() - p.y(), 2));
    if (radius0 > radius1) {
        return true;
    }
    else return false;
}


