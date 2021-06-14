#pragma once

#include <QtWidgets/QWidget>
#include "ui_md5Tool.h"

class md5Tool : public QWidget
{
    Q_OBJECT

public:
    md5Tool(QWidget *parent = Q_NULLPTR);
signals:
    void sigPro(QString filePath, QString fileName, qint64 ss, QString md5);
public slots:
    void slotPro(QString filePath, QString fileName, qint64 ss, QString md5);
private:
    QString fileMd5(const QString &filePath);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
private:
    Ui::md5ToolClass ui;
};
