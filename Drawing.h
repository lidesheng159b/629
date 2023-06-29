#pragma once
#include "ui_IMGPro.h"
//#include"mainWindow.h"
#include "Useui.h"
#include <QtGui>
#include <QtWidgets>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QFile>
#include <QTextStream>
//#include<qlabel.h>

void ui_init(Ui::IMGProClass* ui_ptr);
extern Ui::IMGProClass* Dui;//������һ��


// ����״̬��
class DrawingState:public QLabel {
	Q_OBJECT
public:
    virtual void draw() = 0;
    DrawingState(QWidget* parent = 0)
    {
        m_StartPoint = m_EndPoint = QPoint(0, 0);
        //m_Pixmap = QPixmap(Dui->widget->width(), Dui->widget->height());
        m_Pixmap = QPixmap(1500, 1000);
    };
 

public://����ͼ��չ��
    QPixmap m_Pixmap;
    QPoint m_StartPoint;
    QPoint m_EndPoint;
    QPixmap GetPixmap() { return m_Pixmap; }

public:
  void setStartPoint(QPoint point) {
		m_StartPoint = point;
	}
    void setEndPoint(QPoint point) {
		m_EndPoint = point;
    }


};

// ����״̬��
class DrawingLINESTRING : public DrawingState {
public:
    void draw() override {};
    

};//��

class DrawingPOLYGON : public DrawingState {
public:
    //QVector<QPoint> polygonPoints; // ���ڴ洢����εĸ�������
    void draw() override {};
    bool IsContain(QPoint& p, QVector<QPoint> s);
};//�����

class DrawingPOINT:public DrawingState {
public:
    void draw() override {
        //QMessageBox::critical(Dui->centralWidget, QStringLiteral("��"), QStringLiteral("����"));
    };
};//��

class DrawingSECTOR:public DrawingState {
public:
    void draw() override {};
};//����

class DrawingCIRCLE :public DrawingState {
public:
    void draw() override {};
    bool IsContain(QPoint& p, QPoint p1, QPoint p2);//Բѡ��,��һ���ǵ���㣬�ڶ�����Բ�ģ���������Բ�ϵĵ�
};//Բ��

class DrawingTEXT :public DrawingState {
public:
    void draw() override {};
};//�ı�

class DrawingBITMAP :public DrawingState {
public:
    void draw() override {};
};//λͼ




// ��������
class DrawingContext:public QGraphicsView {
    Q_OBJECT
public:
    DrawingState* currentState;//��ǰ״̬
    QGraphicsItem* Item; // ������ʾ��ͼ״̬�Ķ���
    QGraphicsPixmapItem* pixmapItem; // ������ʾ��ͼ״̬��ͼ�����
    QGraphicsScene* scene; // ��������
    //QVector<QPoint> polygonPoints; // ���ڴ洢����εĸ�������
public:
    DrawingContext(QWidget* parent = 0) : currentState(nullptr) {
        scene = new QGraphicsScene(this);
        setScene(scene);
        setRenderHint(QPainter::Antialiasing, true);
        setFocusPolicy(Qt::StrongFocus);//��������������¼��Ͳ��ᱻTableWidget����
    }//��ʼ��

    // ���õ�ǰ״̬
    void setCurrentState(DrawingState* state) {
        currentState = state;
    }
    // ִ�л��Ʋ���
    void draw();
    // �¼���������
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    //void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event) override;//�����¼�
    void mouseDoubleClickEvent(QMouseEvent* event);//˫���¼�
    void shuaxing();//ˢ��    
    void outputArraysToTxt(const const QString& fileName);//������鵽txt

    //����
    int type;//��ʱ���Ƶ�����
    int c;//�����ѡ����
    int m_icount;//�������
    QPoint p1, p2;//ƽ�Ƽ�¼��
    QPoint init_1;//��ʼ�����¼�㡣
    qreal scaleFactor_=1.0; // ��������
    qreal rotationAngle_=0; // ��ת�Ƕ�
    QTransform transform_; // �任����洢
    QVector<QVector<QPoint>> C;//���Բ
    QList<QGraphicsEllipseItem*> circleItems;
    QVector<QVector<QPoint>> L;//�����
    QVector<QPoint> P;//��ŵ�
    QVector<QVector<QPoint>> T;//��������Ρ�
    QVector<QVector<int>> SEC;//������Ρ�
    QVector<QVector<QPoint>> PL;//��Ŷ���Ρ�
    QList<QGraphicsPolygonItem*> polygonItems;  // �洢�����ͼ����
    QVector<QVector<int>> SEL;//�洢ѡ����Ϣ,����Ϊ�����1Ϊline,2Ϊpoint,3Ϊpolygon,4Ϊcircle,5Ϊ����,�ڶ�λ��Ϊ�����б�š�
    //���ú�����Ҫ
    DrawingPOLYGON polygon;
    DrawingLINESTRING line;
    DrawingPOINT point;
    DrawingSECTOR sector;
    DrawingCIRCLE circle;
    DrawingTEXT text;
    DrawingBITMAP bitmap;
    //QPainter painter;//�ڹ��캯�������ʼ�������޸�
    //������������
    bool isDrawing=0;//�Ƿ����
    bool isSelecting=0;//�Ƿ�ѡ��
    bool isChangecolor = 0;//��ɫ�ǲ��ǻ���


};


class PolylineItem : public QGraphicsPolygonItem
{
public:
    explicit PolylineItem(const QPolygonF& polyline, QGraphicsPolygonItem* parent = nullptr)
        : QGraphicsPolygonItem(parent), m_polyline(polyline)
    {
    }

    QRectF boundingRect() const override
    {
        return m_polyline.boundingRect();
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override
    {
        painter->drawPolyline(m_polyline);
    }

private:
    QPolygonF m_polyline;
};