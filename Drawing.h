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
extern Ui::IMGProClass* Dui;//声明有一个


// 抽象状态类
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
 

public://用于图像展现
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

// 具体状态类
class DrawingLINESTRING : public DrawingState {
public:
    void draw() override {};
    

};//线

class DrawingPOLYGON : public DrawingState {
public:
    //QVector<QPoint> polygonPoints; // 用于存储多边形的各个顶点
    void draw() override {};
    bool IsContain(QPoint& p, QVector<QPoint> s);
};//多边形

class DrawingPOINT:public DrawingState {
public:
    void draw() override {
        //QMessageBox::critical(Dui->centralWidget, QStringLiteral("点"), QStringLiteral("错误"));
    };
};//点

class DrawingSECTOR:public DrawingState {
public:
    void draw() override {};
};//扇形

class DrawingCIRCLE :public DrawingState {
public:
    void draw() override {};
    bool IsContain(QPoint& p, QPoint p1, QPoint p2);//圆选中,第一个是点击点，第二个是圆心，第三个是圆上的点
};//圆形

class DrawingTEXT :public DrawingState {
public:
    void draw() override {};
};//文本

class DrawingBITMAP :public DrawingState {
public:
    void draw() override {};
};//位图




// 上下文类
class DrawingContext:public QGraphicsView {
    Q_OBJECT
public:
    DrawingState* currentState;//当前状态
    QGraphicsItem* Item; // 用于显示绘图状态的对象
    QGraphicsPixmapItem* pixmapItem; // 用于显示绘图状态的图像对象
    QGraphicsScene* scene; // 场景对象
    //QVector<QPoint> polygonPoints; // 用于存储多边形的各个顶点
public:
    DrawingContext(QWidget* parent = 0) : currentState(nullptr) {
        scene = new QGraphicsScene(this);
        setScene(scene);
        setRenderHint(QPainter::Antialiasing, true);
        setFocusPolicy(Qt::StrongFocus);//设置了这个键盘事件就不会被TableWidget抢走
    }//初始化

    // 设置当前状态
    void setCurrentState(DrawingState* state) {
        currentState = state;
    }
    // 执行绘制操作
    void draw();
    // 事件处理函数
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    //void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event) override;//滚轮事件
    void mouseDoubleClickEvent(QMouseEvent* event);//双击事件
    void shuaxing();//刷新    
    void outputArraysToTxt(const const QString& fileName);//输出数组到txt

    //数据
    int type;//此时绘制的种类
    int c;//随机数选种类
    int m_icount;//点击个数
    QPoint p1, p2;//平移记录点
    QPoint init_1;//初始点击记录点。
    qreal scaleFactor_=1.0; // 缩放因子
    qreal rotationAngle_=0; // 旋转角度
    QTransform transform_; // 变换矩阵存储
    QVector<QVector<QPoint>> C;//存放圆
    QList<QGraphicsEllipseItem*> circleItems;
    QVector<QVector<QPoint>> L;//存放线
    QVector<QPoint> P;//存放点
    QVector<QVector<QPoint>> T;//存放三角形。
    QVector<QVector<int>> SEC;//存放扇形。
    QVector<QVector<QPoint>> PL;//存放多边形。
    QList<QGraphicsPolygonItem*> polygonItems;  // 存储多边形图形项
    QVector<QVector<int>> SEL;//存储选中信息,行数为随机，1为line,2为point,3为polygon,4为circle,5为扇形,第二位则为数组行编号。
    //调用函数需要
    DrawingPOLYGON polygon;
    DrawingLINESTRING line;
    DrawingPOINT point;
    DrawingSECTOR sector;
    DrawingCIRCLE circle;
    DrawingTEXT text;
    DrawingBITMAP bitmap;
    //QPainter painter;//在构造函数里面初始化，可修改
    //布尔类型数据
    bool isDrawing=0;//是否绘制
    bool isSelecting=0;//是否选中
    bool isChangecolor = 0;//颜色是不是换了


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
