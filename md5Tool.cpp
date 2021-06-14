#include "md5Tool.h"
#include <QList>
#include <QDragLeaveEvent>
#include <QMimeData>
#include <QDebug>
#include <QCryptographicHash>
#include <QFileInfo>
#include <QtConcurrent/QtConcurrent>

md5Tool::md5Tool(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setAcceptDrops(true);//启用放下操作
    connect(this, &md5Tool::sigPro, this, &md5Tool::slotPro);
}

void md5Tool::slotPro(QString filePath, QString fileName, qint64 ss, QString md5)
{
    ui.textBrowser->append("path: " + filePath);
    ui.textBrowser->append("fileName: " + fileName);
    ui.textBrowser->append(QString("size: %1").arg(ss));
    ui.textBrowser->append("md5: " + md5);
    ui.textBrowser->append("\r\n");
}

QString md5Tool::fileMd5(const QString &filePath)
{
    QString sMd5;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray bArray = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5);
        sMd5 = QString(bArray.toHex()).toUpper();
    }
    file.close();
    return sMd5;
}

void md5Tool::dragEnterEvent(QDragEnterEvent * event)
{
    event->acceptProposedAction(); //可以在这个窗口部件上拖放对象
}

void md5Tool::dragLeaveEvent(QDragLeaveEvent *event)
{
    
}

void md5Tool::dragMoveEvent(QDragMoveEvent *event)
{

}

void md5Tool::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;

    QString firstfileName = urls.first().toLocalFile();
    if (firstfileName.isEmpty())
        return;

    QtConcurrent::run([this, urls]() {
        for (QUrl url : urls) {
            qDebug() << url.toString();
            QFile file(url.toLocalFile());
            if (file.open(QIODevice::OpenModeFlag::ReadOnly)) {
                QString filePath = file.fileName();
                QFileInfo info(filePath);
                if (!info.isFile())
                    continue;
                QString fileName = info.fileName();
                qint64 ss = info.size();
                QString md5 = fileMd5(filePath);
                emit sigPro(filePath, fileName, ss, md5);
            }
        }
    });
    qDebug() << urls.size();
    //setWindowTitle(tr("%1 - %2").arg(fileName).arg("Drag File"));
    
}
