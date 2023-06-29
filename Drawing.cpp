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
        QMessageBox::critical(Dui->centralWidget, QStringLiteral("����"), QStringLiteral("��δѡ�����ģʽ"));
    }
}

void DrawingContext::mousePressEvent(QMouseEvent* event) {

    //��1 ��2 �����3 Բ4 ����5
    if (isSelecting == 0) {
        if (event->button() == Qt::LeftButton && currentState) {
            QPointF scenePos = mapToScene(event->pos());
            //�����
            if (type == 3 && isDrawing == 1) {
                // ���ƶ����
                QPen pen(Qt::black, 3);  // ���û��ʣ���������Ϊ3
                if (PL.isEmpty()) {
                    PL.push_back(QVector<QPoint>());
                }
                PL.back().append(scenePos.toPoint());
                 //���������ͼ����
                QGraphicsPolygonItem* polygonItem = new QGraphicsPolygonItem();

                // ��������е�������
                polygonItem->setPolygon(QPolygonF());
                scene->clear();
               
                QPolygonF polygon;
                foreach(const QPoint & point, PL.back()) {
                    polygon << point;
                }
                polygonItem->setPolygon(polygon);
                // ����ͼ�������
                // ����֮ǰ�Ķ����ͼ�������
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
            //����
            else if (type == 5 && isDrawing == 1) {//����
                if (event->button() == Qt::LeftButton) {
                    // ��ȡ���λ��
                    QPointF clickPos = mapToScene(event->pos());
                    QVector<int> sectorData;
                    // �����Ի������û����������������
                    QDialog dialog;
                    QVBoxLayout layout(&dialog);
                    QLabel radiusLabel(QStringLiteral("�뾶:"));
                    QLineEdit radiusLineEdit;
                    QLabel startAngleLabel(QStringLiteral("��ʼ�Ƕ�:"));
                    QLineEdit startAngleLineEdit;
                    QLabel spanAngleLabel(QStringLiteral("���νǶ�:"));
                    QLineEdit spanAngleLineEdit;
                    QPushButton okButton(QStringLiteral("ȷ��"));

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

                    // ��ȡ���������
                    bool ok;
                    qreal radius = radiusLineEdit.text().toDouble(&ok);
                    if (!ok) {
                        QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("�뾶ֵ��Ч"));
                        return;
                    }

                    int startAngle = startAngleLineEdit.text().toInt(&ok);
                    if (!ok) {
                        QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("�뾶ֵ��Ч"));
                        return;
                    }

                    int spanAngle = spanAngleLineEdit.text().toInt(&ok);
                    if (!ok) {
                        QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("�뾶ֵ��Ч"));
                        return;
                    }

                    // ��������ͼԪ�����ӵ�������
                    QGraphicsEllipseItem* sectorItem = new QGraphicsEllipseItem(clickPos.x() - radius, clickPos.y() - radius, 2 * radius, 2 * radius);
                    sectorItem->setStartAngle(startAngle * 16);
                    sectorItem->setSpanAngle(spanAngle * 16);
                    scene->addItem(sectorItem);
                    // ���������κ����ݴ洢��sectorData
                    sectorData.append(clickPos.x());
                    sectorData.append(clickPos.y());
                    sectorData.append(radius);
                    sectorData.append(startAngle);
                    sectorData.append(spanAngle);

                    // ��sectorData���ӵ���������SEC
                    SEC.append(sectorData);
                }
            }
            //Բ��
            else if (type == 4 && isDrawing == 1) {
                // Բ�λ���
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

            //����
            else if (type == 1 && isDrawing == 1) {
                // �������λ��ת��Ϊ��������
                QPointF scenePos = mapToScene(event->pos());
                if (L.isEmpty()) { L.append(QVector<QPoint>()); }

                L.back().append(scenePos.toPoint());


                // ��������е�������
                scene->clear();

                // ��������ͼ����
                for (int i = 0; i < L.size(); i++) {
                    QPolygonF polyline;
                    foreach(const QPoint & point, L[i]) {
                        polyline << point;
                    }
                    PolylineItem* polylineItem = new PolylineItem(polyline);
                    // �������ߵ���ʽ������ɫ���߿���
                    QPen pen(Qt::black, 3);
                    polylineItem->setPen(pen);

                    // ��������ͼ�������
                    scene->addItem(polylineItem);
                }

            }
            //��
            else if (type == 2 && isDrawing == 1) {//��

                QPointF scenePos = mapToScene(event->pos());
                P.append(scenePos.toPoint());
                for (int i = 0; i < P.size(); i++) {
                    QPointF point; // �������
                    point= P[i];
                    QGraphicsEllipseItem* pointItem = new QGraphicsEllipseItem(point.x() - 2, point.y() - 2, 4, 4); // ����һ����Բͼ�����СΪ4x4
                    pointItem->setBrush(Qt::black); // ������Բ�������ɫ
                    scene->addItem(pointItem); // ��ͼ�������ӵ�������
                }

            }
            //�ı�
            else if (type == 6 && isDrawing == 1) {
                // ��ȡ�����λ��
                QPointF mousePos = mapToScene(event->pos());

                // �����Ի����ȡ�û�������ı�
                QString userInput = QInputDialog::getText(this, QStringLiteral("�����ı�"), QStringLiteral("�������ı�:"));

                // �����ı���
                QGraphicsTextItem* textItem = new QGraphicsTextItem(userInput);
                textItem->setPos(mousePos);

                // ���ı������ӵ�������
                scene->addItem(textItem);
            }
            //λͼ
            else if (type == 7 && isDrawing == 1) {
                // ����λͼ�ļ�
               // ���ļ��Ի���ѡ��λͼ�ļ�
               QString filePath = QFileDialog::getOpenFileName(this, QStringLiteral( "ѡ��λͼ�ļ�"), "", QStringLiteral("λͼ�ļ� (*.png *.jpg *.bmp)"));

               // ����λͼ�ļ�
               if (!filePath.isEmpty()) {
                   QPixmap pixmap(filePath);

                   // ����λͼͼ����
                   QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);

                   // ����λͼ��λ��
                   pixmapItem->setPos(scenePos);

                   // ����λͼͼ�������
                   scene->addItem(pixmapItem);
               }

            }
        }
    }
    if (isSelecting == 1) {
        if (event->button() == Qt::LeftButton) {
            // ��ȡ�����λ��
            QPointF scenePos = mapToScene(event->pos());

            // ��ȡλ�ڵ��λ�õ�ͼ����
            QList<QGraphicsItem*> items = scene->items(scenePos);

            // ����ͼ����ж��Ƿ�ѡ��
            for (QGraphicsItem* item : items) {
                // �ж�ͼ�����Ƿ�������Ƶ��ض����ͣ����Ը����Լ�����������ж�
                if (1) {
                    // ��ͼ������Ϊѡ��״̬
                    item->setSelected(true);
                    
                    // ��������Խ���ѡ��ͼ����Ĵ���������ı���ɫ���߱߿���ʽ
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
            // ����һ���Զ���Ի���
            QDialog dialog;
            dialog.setWindowTitle(QStringLiteral("ѡ�����"));

            QVBoxLayout layout(&dialog);
            QLabel label(QStringLiteral("��ѡ��Ҫִ�еĲ���:"));
            layout.addWidget(&label);

            QPushButton deleteButton(QStringLiteral("ɾ��"));
            QPushButton hideButton(QStringLiteral("����"));

            layout.addWidget(&deleteButton);
            layout.addWidget(&hideButton);

            QObject::connect(&deleteButton, &QPushButton::clicked, [&]() {
                // ִ��ɾ������
                scene->removeItem(selectedItem);
                delete selectedItem;
                dialog.accept();
                });

            QObject::connect(&hideButton, &QPushButton::clicked, [&]() {
                // ִ�����ز���
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
        QPen pen(Qt::black, 3);  // ���û��ʣ���������Ϊ3
        C.back().append(scenePos.toPoint());

        // ���� C �е����飬����ͼ�������
        foreach(const QVector<QPoint>&circlepoints, C) {
            if (circlepoints.size() < 2) continue;
            QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem();
            QPoint start = circlepoints.front();  // ʹ�� circlepoints.front() ��ȡ�������
            QPoint end = circlepoints.back();  // ʹ�� circlepoints.back() ��ȡ�յ�����
            int radius = qSqrt(qPow(start.x() - end.x(), 2) + qPow(start.y() - end.y(), 2));
            QRectF circleRect(start.x() - radius, start.y() - radius, radius * 2, radius * 2);
            ellipseItem->setPen(pen);
            ellipseItem->setRect(circleRect);

            // ����ͼ�������
            scene->addItem(ellipseItem);
        }
    }

}

void DrawingContext::mouseMoveEvent(QMouseEvent* event) {
    setMouseTracking(true);//ʵʱ������λ��
    if (type == 4 && isDrawing == 1)//����Բ�ε�ʵʱ����
    {
       
    }
    if (isSelecting == 1 && SEL.size() != 0)//����ѡ��״̬��ѡ����ͼ��
    {
        //��1 ��2 �����3 Բ4 ����5
        double dx, dy;
        if (event->buttons() & Qt::LeftButton)//���һֱ����
        {
            p2 = event->pos();//p2��p1�д���p1ÿ�λ��¼p2�ϴε�λ�ã���Ϊƽ�Ƶ�x,yС�����ӻ�׼��
            if (p1.x() != 0 && p1.y() != 0)//������һ�Σ�����p1��¼��һ��p2��λ�á�
            {
                dx = p2.x() - p1.x();//��ʶƽ�ƾ���
                dy = p2.y() - p1.y();//��ʶƽ�ƾ���
                if (SEL[c][0] == 1)//��
                {
                    L[SEL[c][1]][0].rx() += dx;//rx���޸�
                    L[SEL[c][1]][0].ry() += dy;
                    L[SEL[c][1]][1].rx() += dx;
                    L[SEL[c][1]][1].ry() += dy;
                }
                else if (SEL[c][0] == 4)//Բ��
                {
                    C[SEL[c][1]][0].rx() += dx;
                    C[SEL[c][1]][0].ry() += dy;
                    C[SEL[c][1]][1].rx() += dx;
                    C[SEL[c][1]][1].ry() += dy;
                }
                else if (SEL[c][0] == 3)//�����
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
            this->viewport()->update();//�����ػ溯��
        }
    }
    // ��ͼ���ѡ�к�ʹ������ƶ��¼������ƶ�
    if (event->buttons() && !(Qt::LeftButton&& scene->selectedItems().isEmpty())) {
       
        // ����ѡ�е�ͼ����
        for (QGraphicsItem* item : scene->selectedItems()) {
            // ��ͼ�����ƶ�����ǰλ��
            item->setPos(mapToScene(event->pos()));
        }
    }
    
}

void DrawingContext::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter || event->key() == Qt::Key_Plus) {//+�����ӣ��س���������
        if (type == 3) {//�����
            PL.push_back(QVector<QPoint>());//�ͼ�һ����ջ
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            //this->viewport()->update();
        }
        if (type == 4) {//Բ��
            C.push_back(QVector<QPoint>());//�ͼ�һ����ջ
            isDrawing = 1;
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            this->viewport()->update();
        }
        if (type == 1) {//��
            L.push_back(QVector<QPoint>());//�ͼ�һ����ջ
            isDrawing = 1;
            if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
                type = 0;
                isDrawing = 0;
            }
            this->viewport()->update();
        }
        if (type == 2) {//��
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
        // ��ȡ�����е�ѡ����
        QList<QGraphicsItem*> selectedItems = scene->selectedItems();

        // ����ѡ����ӳ���������ģ����ɾ������
        for (QGraphicsItem* item : selectedItems) {
            scene->removeItem(item);
           
        }
    }
    
    
}

void DrawingContext::wheelEvent(QWheelEvent* event)
{
    
    // ��ȡ���ֵĹ�������͹����Ĳ���
    int delta = event->angleDelta().y();

    // ������������
    double scaleFactor = 1.2;

    // ��ȡ�������ͼ�е�λ��
    QPointF mousePos = mapToScene(event->pos());

    // ���ݹ������������������
    if (delta > 0) {
        // ���Ϲ������Ŵ���ͼ
        scale(scaleFactor, scaleFactor);
    }
    else {
        // ���¹�������С��ͼ
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }

    

}

//void DrawingContext::contextMenuEvent(QContextMenuEvent* event)
//{
//    QMenu menu(this);
//
//    QAction* colorAction = menu.addAction("�޸���ɫ");
//    QAction* fillStyleAction = menu.addAction("�޸������ʽ");
//
//    QAction* selectedItem = menu.exec(event->globalPos());
//
//    if (selectedItem == colorAction) {
//        // �����޸���ɫ�Ĳ���
//        QColor newColor = QColorDialog::getColor(Qt::black, this, "ѡ����ɫ");
//        if (newColor.isValid()) {
//            
//        }
//    }
//    else if (selectedItem == fillStyleAction) {
//        // �����޸������ʽ�Ĳ���
//        // �������ʹ�����Ƶķ��������Ի�����ѡ�������ʽ��������Ӧ�õ�Painter��
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

    // ����ѡ��Ի���
    QMessageBox dialog;
    dialog.setText(QStringLiteral("��ѡ��Ҫ�޸ĵ�����"));
    dialog.addButton(QStringLiteral("�߿�"), QMessageBox::AcceptRole);
    dialog.addButton(QStringLiteral("���"), QMessageBox::AcceptRole);
    dialog.addButton(QStringLiteral("��ʽ"), QMessageBox::AcceptRole);
    dialog.exec();

    QString selectedOption = dialog.clickedButton()->text();

    if (selectedOption == QStringLiteral("�߿�")) {
        // �޸������ɫ
        QColor penColor;

        // ��ȡͼ���������
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

        penColor = QColorDialog::getColor(penColor, nullptr, QStringLiteral("ѡ��߿���ɫ"));
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
    else if (selectedOption == QStringLiteral("���") ){
        // �޸������ɫ
        QColor fillColor;

        // ��ȡͼ���������
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

        fillColor = QColorDialog::getColor(fillColor, nullptr, QStringLiteral("ѡ�������ɫ"));
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
    else if (selectedOption == QStringLiteral("��ʽ")) {
        // �޸������ʽ
        QGraphicsItem* item = itemScene;
        QStringList styleOptions;
        styleOptions << QStringLiteral("����ʽ") << QStringLiteral("����") << QStringLiteral("ˮƽ��") << QStringLiteral("��ֱ��") << QStringLiteral("б��");

        bool ok;
        QString selectedStyle = QInputDialog::getItem(this, QStringLiteral("ѡ�������ʽ"), QStringLiteral("�����ʽ:"), styleOptions, 3, false, &ok);

        if (ok) {
            Qt::BrushStyle brushStyle = Qt::NoBrush;

            if (selectedStyle == QStringLiteral("����")) {
                brushStyle = Qt::Dense1Pattern;
            }
            else if (selectedStyle == QStringLiteral("ˮƽ��")) {
                brushStyle = Qt::HorPattern;
            }
            else if (selectedStyle == QStringLiteral("��ֱ��")) {
                brushStyle = Qt::VerPattern;
            }
            else if (selectedStyle == QStringLiteral("б��")) {
                brushStyle = Qt::BDiagPattern;
            }
            // ���Ӹ�����ʽ�Ĵ���


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
    QPen pen(Qt::black, 3);  // ���û��ʣ���������Ϊ3
    scene->clear();
    //�����
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
    //����
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
    //Բ��
    foreach(const QVector<QPoint>& circlepoints, C) {
        if (circlepoints.size() < 2) continue;
        QGraphicsEllipseItem* ellipseItem = new QGraphicsEllipseItem();
        QPoint start = circlepoints.front();  // ʹ�� circlepoints.front() ��ȡ�������
        QPoint end = circlepoints.back();  // ʹ�� circlepoints.back() ��ȡ�յ�����
        int radius = qSqrt(qPow(start.x() - end.x(), 2) + qPow(start.y() - end.y(), 2));
        QRectF circleRect(start.x() - radius, start.y() - radius, radius * 2, radius * 2);
        ellipseItem->setPen(pen);
        ellipseItem->setRect(circleRect);

        // ����ͼ�������
        scene->addItem(ellipseItem);
    }
    //����
    
    for (int i = 0; i < L.size(); i++) {
        QPolygonF polyline;
        foreach(const QPoint & point, L[i]) {
            polyline << point;
        }
        PolylineItem* polylineItem = new PolylineItem(polyline);
        // �������ߵ���ʽ������ɫ���߿���
        QPen pen(Qt::black, 3);
        polylineItem->setPen(pen);

        // ��������ͼ�������
        scene->addItem(polylineItem);
    }



}

//void DrawingContext::shuaxing()
//{
//    QPen pen(Qt::black, 3);  // ���û��ʣ���������Ϊ3
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
        qDebug() << "�޷����ļ���" << fileName;
        return;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");  // �����ı����ı���ΪUTF-8

    // ������������
    out << QStringLiteral( "��������ݣ�") << endl;
    int polygonIndex = 1;
    for (const QVector<QPoint>& polygonPoints : PL) {
        out << QStringLiteral("polygon ") << polygonIndex << QStringLiteral("��") << endl;
        for (const QPoint& point : polygonPoints) {
            out << QStringLiteral("x: ") << point.x() << QStringLiteral(", y: ") << point.y() << endl;
        }
        polygonIndex++;
    }


    // �����������
    out << QStringLiteral("�������ݣ�") << endl;
    int Index = 1;
    for (const QVector<int>& sectorData : SEC) {
        out << QStringLiteral( "sector��") << endl;
        out << QStringLiteral("x: ") << sectorData[0] << QStringLiteral(", y: ") << sectorData[1] << QStringLiteral(", r: ") << sectorData[2] << QStringLiteral(", startAngle: ") << sectorData[3] << QStringLiteral(", spanAngle: ") << sectorData[4] << endl;
    }

    // ���Բ������
    out << QStringLiteral("Բ�����ݣ�") << endl;
    for (const QVector<QPoint>& circlePoints : C) {
        if (circlePoints.size() < 2) continue;
        QPoint start = circlePoints.front();
        QPoint end = circlePoints.back();
        int radius = qSqrt(qPow(start.x() - end.x(), 2) + qPow(start.y() - end.y(), 2));
        out << QStringLiteral("start��x:") << start.x() << QStringLiteral(", y: ") << start.y() << endl;
        out << QStringLiteral("�յ����꣺x: ") << end.x() << QStringLiteral(", y: ") << end.y() << endl;
        out << QStringLiteral("�뾶��") << radius << endl;
    }

    // �����������
    out << QStringLiteral( "�������ݣ�") << endl;
    for (const QVector<QPoint>& polylinePoints : L) {
        out << QStringLiteral("���ߣ�") << endl;
        for (const QPoint& point : polylinePoints) {
            out << QStringLiteral("x: ") << point.x() << QStringLiteral(", y: ") << point.y() << endl;
        }
    }

    file.close();
    
}


//****************************************************//
//              �ж��Ƿ���ͼ����                       //
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

