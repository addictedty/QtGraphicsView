#pragma once
#include <qgraphicsitem.h>
#include "CGraphicsItemBase.h"
#include <QPen>

class CGraphicsTextItem :
	public QGraphicsTextItem
{
	enum class Edge {
		None = 0x0,
		Top = 0x1,
		Bottom = 0x2,
		Left = 0x4,
		Right = 0x8,
		Center = 0x10,
		TopLeft = Edge::Top | Edge::Left,
		BottomLeft = Edge::Bottom | Edge::Left,
		TopRight = Edge::Top | Edge::Right,
		BottomRight = Edge::Bottom | Edge::Right
	};

public:
	CGraphicsTextItem(QGraphicsTextItem *parent = nullptr);
	virtual ~CGraphicsTextItem();

	void SetRect(QRectF rect);

private:
	//获取描点
	QVector<QRectF> anchorItem(const QRectF &rectf);
	//调整矩形四个点，避免出现宽度或高度为负数的情况
	void adjustRect();

private:
	Edge m_edge;
	QRectF m_rect;
	QPen m_pen;

protected:
	QRectF boundingRect() const override;
	QPainterPath shape() const;
	void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
	void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
	void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
	void focusOutEvent(QFocusEvent *event) override;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

};

