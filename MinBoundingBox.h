#pragma once
#include <vector>
#include <math.h>
#include <QVector3D>

class MinBoundingBox
{
public:
	MinBoundingBox(void);
	~MinBoundingBox(void);
	
public:
	
    bool calculateMinBoundingBox(const std::vector<QVector3D>& cloud);

    inline QVector3D getMinPoint() { return m_min; }
    inline QVector3D getMaxPoint() { return m_max; }
    inline QVector3D getMeanPoint() { return m_mean; }
    inline QVector3D getCenterPoint() { return m_center; }
	
    inline void firstPoint(QVector3D p) { m_min = m_max = m_mean= p; }
    inline float width(void) const { return m_max.x() - m_min.x(); }
    inline float height(void) const { return m_max.y() - m_min.y(); }
    inline float depth(void) const { return m_max.z() - m_min.z(); }
    float midX(void) const { return (m_min.x() + m_max.x()) / 2; }
    float midY(void) const { return (m_min.y() + m_max.y()) / 2; }
    float midZ(void) const { return (m_min.z() + m_max.z()) / 2; }
    inline void zerolize(void) {
        m_min = m_max = m_center = m_mean = QVector3D(0.0, 0.0, 0.0);
        index = 1;
    }
    inline void setMin(QVector3D point) { m_min = point; }
    inline void setMax(QVector3D point) { m_max = point; }
	
	inline bool Iszerolized() {
        return	(abs(m_min.x()) < 0.00001 && abs(m_min.y()) < 0.00001 && abs(m_min.z()) < 0.00001 &&
                 abs(m_max.x()) < 0.00001 && abs(m_max.y()) < 0.00001 && abs(m_max.z()) < 0.00001);
	}

	inline void setMinMax(float x, float &min, float &max)
	{
		if (x > max) max = x;
		if (x < min) min = x;
	}
    void setMinMax(QVector3D point, QVector3D &min, QVector3D &max);
    void nextPoint(QVector3D p);

	MinBoundingBox& operator = (MinBoundingBox &box);
private:
	int index;
	const float m_finvalidDis;
    QVector3D m_min;
    QVector3D m_max;
    QVector3D m_center;
    QVector3D m_mean;

    bool isContain(QVector3D point);
    bool isValid(QVector3D point);
};
//end min bounding box

