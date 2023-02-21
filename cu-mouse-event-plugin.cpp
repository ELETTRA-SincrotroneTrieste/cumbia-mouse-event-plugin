#include "cu-mouse-event-plugin.h"
#include <QClipboard>
#include <cucontrolsreader_abs.h>
#include <cucontrolswriter_abs.h>
#include <QApplication>
#include <cucontexti.h>
#include <cucontext.h>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QWidget>
#include <QRegularExpression>
#include <QProcessEnvironment>
#include <QPixmap>
#include <QPainter>

CuMouseEvPlugin::CuMouseEvPlugin(QObject *parent) : QObject(parent)
{
    m_ctxi = nullptr;
}

CuMouseEvPlugin::~CuMouseEvPlugin()
{
}

QString CuMouseEvPlugin::m_get_point(const CuContext* ctx, bool ensure_tghost) const
{
    QList<CuControlsReaderA *> rs = ctx->readers();
    QList<CuControlsWriterA *> ws;
    if(rs.isEmpty())
        ws = ctx->writers();
    QString s;
    if(rs.size() > 0) {
        s += rs[0]->source();
        for(int i = 1; i < rs.size(); i++)
            s += "," + rs[i]->source();
    }
    else if(ws.size() > 0) {
        s += ws[0]->target();
        for(int i = 1; i < ws.size(); i++)
            s += "," + ws[i]->target();
    }
    if(!s.isEmpty() && ensure_tghost && !s.contains(QRegularExpression(".*:\\d+/"))) {
        QString tgh = QProcessEnvironment::systemEnvironment().value("TANGO_HOST");
        printf("TANGO_HOST is %s\n", qstoc(tgh));
        if(!tgh.isEmpty())
            s = tgh + "/" + s;
    }
    return s;
}


void CuMouseEvPlugin::pressed(QMouseEvent *e, QWidget *w, CuContextI *ctxi) {
    if (e->button() == Qt::LeftButton)  {
        bool ensure_tghost = e->modifiers() == Qt::ShiftModifier;
        const CuContext *ctx = ctxi->getContext();
        const QString s = m_get_point(ctx, ensure_tghost);
        if(!s.isEmpty()) {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            mimeData->setText(s);
            drag->setMimeData(mimeData);
            // draw a pixmap with the source (target) during drag
            QFont f = w->font();
            f.setFamily("Sans Serif");
            f.setPointSize(f.pointSizeF() - 1);
            QFontMetrics fontMetrics(f);
            QSize fontSize(fontMetrics.horizontalAdvance(s), fontMetrics.height());
            QPixmap dragPix(fontSize);
            QColor pixColor = Qt::white;
            pixColor.setAlpha(50);
            dragPix.fill(pixColor);
            QPainter painter(&dragPix);
            painter.setRenderHints(QPainter::TextAntialiasing);
            painter.setPen(Qt::blue);
            painter.setFont(f);
            painter.drawText(dragPix.rect(), Qt::AlignLeft|Qt::AlignVCenter, s);
            drag->setPixmap(dragPix);
            drag->exec(Qt::CopyAction);
        }
    }
}

void CuMouseEvPlugin::released(QMouseEvent *e, QWidget *w, CuContextI *ctx) {
    Q_UNUSED(w);
    Q_UNUSED(e);
    Q_UNUSED(ctx);
}

void CuMouseEvPlugin::moved(QMouseEvent *e, QWidget *w, CuContextI *ctx) {
    Q_UNUSED(w);
    Q_UNUSED(e);
    Q_UNUSED(ctx);
}

void CuMouseEvPlugin::doubleClicked(QMouseEvent *e, QWidget *w, CuContextI *ctx) {
    Q_UNUSED(w);
    Q_UNUSED(e);
    Q_UNUSED(ctx);
}
