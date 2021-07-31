#pragma once
#include <QGraphicsView>

class CGraphicsView :
	public QGraphicsView
{
public:
	CGraphicsView(QWidget *parent = nullptr);
	virtual ~CGraphicsView();
};

