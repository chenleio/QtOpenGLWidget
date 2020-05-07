#ifndef MYQOPENGLWIDGET_H
#define MYQOPENGLWIDGET_H
#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include <QtWidgets/QOpenGLWidget>
#include <QOpenGLVertexArrayObject>
#include <QPainter>
#include <QOpenGLContext>
#include <QOpenGLPaintDevice>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QTimer>
#include <QVector3D>
#include <QQuaternion>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTime>
#include <QScopedPointer>
#include "MinBoundingBox.h"

using namespace std;

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
class QOpenGLShaderProgram;
class QOpenGLShader;
QT_END_NAMESPACE

class MyQOpenglWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyQOpenglWidget(QWidget *parent = 0);
    ~MyQOpenglWidget();
    void showPointCloud(const std::vector<QVector3D>& cloud);
    virtual void resizeGL(int w, int h);
    void setBackgroundColor(QVector3D color);

protected:
    virtual void initializeGL(void);
    virtual void paintGL(void);

    struct VertexInfo
    {
        float pos[3] = {0.0,0.0,0.0};
        float normal[3] = {0.0,0.0,1.0};
        float color[4] = {1.0,1.0,1.0,1.0};
    };
private slots:
    void onTimerOut(void);
    virtual void mousePressEvent(QMouseEvent * e);
    virtual void mouseMoveEvent(QMouseEvent * e);
    virtual void mouseReleaseEvent(QMouseEvent * e);
    virtual void wheelEvent(QWheelEvent * e);
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void leaveEvent(QEvent *);
    virtual void enterEvent(QEvent *);

private:
    QTimer *m_Timer;
    QScopedPointer<QOpenGLContext> m_context;
    QScopedPointer<QOpenGLShaderProgram> m_Program;
    QScopedPointer<QOpenGLShader> m_VertexShader;
    QScopedPointer<QOpenGLShader> m_FragmentShader;

	// shader spara
    GLuint m_posAttr;                           
    GLuint m_colAttr;                          
    GLuint m_norAttr;                           
    GLuint m_matrixUniform;						
	GLuint m_VBO;
    GLuint m_EBO;
    QScopedPointer<QOpenGLVertexArrayObject> m_VAO;
    QVector4D m_backgroundColor;

	//store points
	QVector<VertexInfo> m_PointsVertex;				
    MinBoundingBox m_box;                           
   
    QVector3D m_lineMove;
    QQuaternion m_rotate;
	QVector3D m_rotationAxis;
    float m_scale;
    bool m_bShowAxis;
    GLuint m_Axisindices[6];

    QVector2D m_lastPoint;

    GLuint createGPUProgram(QString nVertexShaderFile, QString nFragmentShaderFile);
    void GetShaderUniformPara();
    bool InitShader();                    

    void LineMove(QVector2D posOrgin, QVector2D posEnd);
    void Rotate(QVector2D posOrgin, QVector2D posEnd);
    void modelZoomInOrOut(bool ZoomInOrOut);
    QVector3D pixelPosToViewPos(const QVector2D& p);
    void calRotation(QVector2D posOrgin, QVector2D posEnd);
    void initPointCloud(const std::vector<QVector3D>& cloud);
    void gray2Pseudocolor(const QVector3D pos, float color[4]);
    void changePointCloud();
    void setMatrixUniform();
    void ResetView();
    void initCloud();
    void addAxisData();

    //debug
    void debugMsg(QString msg,QTime start);

};

#endif // MYQOPENGLWIDGET_H
