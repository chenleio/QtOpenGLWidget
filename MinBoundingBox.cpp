
#include "MinBoundingBox.h"

MinBoundingBox::MinBoundingBox(void):
	m_finvalidDis(90000.0f)
{
	zerolize();
}

MinBoundingBox::~MinBoundingBox(void)
{
}

bool MinBoundingBox::calculateMinBoundingBox(const std::vector<QVector3D>& cloud)
{
	zerolize();
    int size =(int) cloud.size();
	if (size == 0)
	{
		return false;
	}
	else if (size ==1)
	{
        firstPoint(cloud[0]);
		return false;
	}
	else
	{
		bool bfirst = false;		
		for (int i = 0; i < size; i++)
		{
			if (!bfirst)
			{
                if (isValid(cloud[i]))
				{
                    firstPoint(cloud[i]);
					bfirst = true;
				}
			}
			else
			{
                nextPoint(cloud[i]);
			}			
		}
        m_center = QVector3D(midX(), midY(), midZ());
	}
    return true;
}

void MinBoundingBox::setMinMax(QVector3D point, QVector3D &min, QVector3D &max)
{
    min.setX(std::min(point.x(),min.x()));
    min.setY(std::min(point.y(),min.y()));
    min.setZ(std::min(point.z(),min.z()));

    max.setX(std::max(point.x(),max.x()));
    max.setY(std::max(point.y(),max.y()));
    max.setZ(std::max(point.z(),max.z()));
}

MinBoundingBox& MinBoundingBox::operator = (MinBoundingBox &box)
{
	this->m_min = box.m_min;
	this->m_max = box.m_max;
	this->m_mean = box.m_mean;
	this->m_center = box.m_center;
	this->index = box.index;
	return *this;
}
void MinBoundingBox::nextPoint(QVector3D p)
{
	if (!isValid(p))
	{
		return;
	}
    setMinMax(p, m_min, m_max);  
	index++;
}

bool MinBoundingBox::isContain(QVector3D point)
{
    return (	point.x() <= m_max.x() && point.x() >= m_min.x()
            &&	point.y() <= m_max.y() && point.y() >= m_min.y()
            &&	point.z() <= m_max.z() && point.z() >= m_min.z());
}

bool MinBoundingBox::isValid(QVector3D point)
{
    if (abs(point.z())>m_finvalidDis || abs(point.y())>m_finvalidDis || abs(point.x())>m_finvalidDis)
	{
		return false;
	}
	return true;
}

