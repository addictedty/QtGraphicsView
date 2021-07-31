#pragma once
#include <QObject>
#include <QGraphicsScene>

class CGraphicsScene :
	public QGraphicsScene
{
public:
	CGraphicsScene(QObject *parent = nullptr);
	virtual ~CGraphicsScene();
};

