#include "CGraphicsTextItem.h"
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

#define     MINWIDTH    200
#define     MINHEIGHT   200

CGraphicsTextItem::CGraphicsTextItem(QGraphicsTextItem *parent)
	:QGraphicsTextItem(parent)
{
	m_pen.setColor(Qt::red);
	m_pen.setWidth(4);

	setFlag(QGraphicsItem::ItemIsSelectable);
	setAcceptHoverEvents(true);
}

CGraphicsTextItem::~CGraphicsTextItem()
{
}

void CGraphicsTextItem::SetRect(QRectF rect)
{
	m_rect = mapRectFromScene(rect);
}

QRectF CGraphicsTextItem::boundingRect() const
{
	if (m_rect != QRectF())
		return m_rect;
	return QRectF();
}
QPainterPath CGraphicsTextItem::shape() const
{
	QPainterPath path;
	path.addRect(m_rect);
	return path;

}

QVector<QRectF> CGraphicsTextItem::anchorItem(const QRectF &rectf)
{
	QVector<QRectF> anchor;

	qreal width = rectf.width() / 10;
	qreal height = rectf.height() / 10;

	anchor.append(QRectF(rectf.topLeft().x(), rectf.topLeft().y(),
		width, height));
	anchor.append(QRectF(rectf.topRight().x() - width, rectf.topRight().y(),
		width, height));
	anchor.append(QRectF(rectf.bottomLeft().x(), rectf.bottomLeft().y() - height,
		width, height));
	anchor.append(QRectF(rectf.bottomRight().x() - width, rectf.bottomRight().y() - height,
		width, height));

	return anchor;
}

void CGraphicsTextItem::adjustRect()
{
	qreal left = m_rect.left();
	qreal right = m_rect.right();
	qreal top = m_rect.top();
	qreal bottom = m_rect.bottom();
	m_rect.setLeft(qMin(left, right));
	m_rect.setRight(qMax(left, right));
	m_rect.setTop(qMin(top, bottom));
	m_rect.setBottom(qMax(top, bottom));
	setTextWidth(m_rect.width());
}

void CGraphicsTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF pos = event->pos();
	QVector<QRectF> set = anchorItem(m_rect);

	do
	{
		if (set[0].contains(pos))
		{
			m_edge = Edge::TopLeft;
			break;
		}
		if (set[1].contains(pos))
		{
			m_edge = Edge::TopRight;
			break;
		}
		if (set[2].contains(pos))
		{
			m_edge = Edge::BottomLeft;
			break;
		}
		if (set[3].contains(pos))
		{
			m_edge = Edge::BottomRight;
			break;
		}
		m_edge = Edge::Center;

	} while (false);

	setFlag(QGraphicsItem::ItemIsMovable, false);

	QGraphicsTextItem::mousePressEvent(event);
}

void CGraphicsTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		switch (m_edge)
		{
		case Edge::TopLeft:
		case Edge::TopRight:
		case Edge::BottomLeft:
		case Edge::BottomRight:
			adjustRect();
			break;
		case Edge::Center:
			setFlag(QGraphicsItem::ItemIsMovable, true);
			break;
		default:
			break;
		}
	}

	setFlag(QGraphicsItem::ItemIsMovable, true);

	QGraphicsTextItem::mouseReleaseEvent(event);
}

void CGraphicsTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QPointF tmpPos = event->pos();
	QRectF rectF;
	if (nullptr != parentItem())
	{
		rectF = mapFromParent(parentItem()->boundingRect()).boundingRect();
	}
	else
	{
		rectF = mapFromScene(scene()->sceneRect()).boundingRect();
	}
	if (tmpPos.x() < rectF.x())
	{
		tmpPos.setX(rectF.x());
	}
	if (tmpPos.x() > rectF.right())
	{
		tmpPos.setX(rectF.right());
	}
	if (tmpPos.y() < rectF.y())
	{
		tmpPos.setY(rectF.y());
	}
	if (tmpPos.y() > rectF.bottom())
	{
		tmpPos.setY(rectF.bottom());
	}

	switch (m_edge) {
	case Edge::TopLeft:
		if (tmpPos.x() + MINWIDTH > m_rect.right())
		{
			tmpPos.setX(m_rect.right() - MINWIDTH);
		}
		if (tmpPos.y() + MINHEIGHT > m_rect.bottom())
		{
			tmpPos.setY(m_rect.bottom() - MINHEIGHT);
		}
		m_rect.setTopLeft(tmpPos);
		adjustRect();
		break;
	case Edge::TopRight:
		if (tmpPos.x() < m_rect.left() + MINWIDTH)
		{
			tmpPos.setX(m_rect.left() + MINWIDTH);
		}
		if (tmpPos.y() + MINHEIGHT > m_rect.bottom())
		{
			tmpPos.setY(m_rect.bottom() - MINHEIGHT);
		}
		m_rect.setTopRight(tmpPos);
		adjustRect();
		break;
	case Edge::BottomLeft:
		if (tmpPos.x() + MINWIDTH > m_rect.right())
		{
			tmpPos.setX(m_rect.right() - MINWIDTH);
		}
		if (tmpPos.y() < m_rect.top() + MINHEIGHT)
		{
			tmpPos.setY(m_rect.top() + MINHEIGHT);
		}
		m_rect.setBottomLeft(tmpPos);
		adjustRect();
		break;
	case Edge::BottomRight:
		if (tmpPos.x() < m_rect.left() + MINWIDTH)
		{
			tmpPos.setX(m_rect.left() + MINWIDTH);
		}
		if (tmpPos.y() < m_rect.top() + MINHEIGHT)
		{
			tmpPos.setY(m_rect.top() + MINHEIGHT);
		}
		m_rect.setBottomRight(tmpPos);
		adjustRect();
		break;
	case Edge::Center:
		setFlag(QGraphicsItem::ItemIsMovable, true);
		break;
	default:
		break;
	}

	prepareGeometryChange();
	QGraphicsTextItem::mouseMoveEvent(event);
}

void CGraphicsTextItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	QPointF pos = event->pos();
	QVector<QRectF> set = anchorItem(m_rect);

	if (set[0].contains(pos))
		setCursor(Qt::SizeFDiagCursor);
	else if (set[1].contains(pos))
		setCursor(Qt::SizeBDiagCursor);
	else if (set[2].contains(pos))
		setCursor(Qt::SizeBDiagCursor);
	else if (set[3].contains(pos))
		setCursor(Qt::SizeFDiagCursor);
	else
		setCursor(Qt::SizeAllCursor);

	QGraphicsTextItem::hoverMoveEvent(event);
}

void CGraphicsTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	setTextInteractionFlags(Qt::TextEditorInteraction);
	QGraphicsTextItem::mouseDoubleClickEvent(event);
}

void CGraphicsTextItem::focusOutEvent(QFocusEvent *event)
{
	setTextInteractionFlags(Qt::NoTextInteraction);
	QGraphicsTextItem::focusOutEvent(event);
}

void CGraphicsTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

	QVector<QRectF> set = anchorItem(m_rect);
	m_pen.setColor(Qt::green);
	painter->setPen(m_pen);
	for (int i = 0; i < set.count(); i++)
	{
		painter->drawRect(set[i]);
	}

	painter->drawLine(m_rect.left(), m_rect.center().y(), m_rect.right(), m_rect.center().y());
	painter->drawLine(m_rect.center().x(), m_rect.top(), m_rect.center().x(), m_rect.bottom());

	m_pen.setColor(Qt::red);
	painter->setPen(m_pen);
	painter->drawRect(m_rect);
	QGraphicsTextItem::paint(painter, option, widget);

}