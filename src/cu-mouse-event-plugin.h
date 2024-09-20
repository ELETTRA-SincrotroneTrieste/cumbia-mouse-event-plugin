#ifndef CUMOUSEEVENT_H
#define CUMOUSEEVENT_H

#include <cumouseevhandlerplugin_i.h>
#include <QList>
#include <QObject>

class CuContext;

class CuMouseEvPlugin : public QObject, public CuMouseEvHandlerPlugin_I
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "cumbia-mouse-event-plugin.json")

public:
    explicit CuMouseEvPlugin(QObject *parent = nullptr);
    ~CuMouseEvPlugin();

    Q_INTERFACES(CuMouseEvHandlerPlugin_I)

public:

protected slots:
    void onActionTriggered();

private:
    const CuContextI *m_ctxi;

    QString m_get_point(const CuContext *ctx, bool ensure_tghost) const;


    // CuMouseEvHandlerPlugin_I interface
public:
    void pressed(QMouseEvent *e, QWidget *w, CuContextI *ctx);
    void released(QMouseEvent *e, QWidget *w, CuContextI *ctx);
    void moved(QMouseEvent *e, QWidget *w, CuContextI *ctx);
    void doubleClicked(QMouseEvent *e, QWidget *w, CuContextI *ctx);
};






#endif // CUMBIACOPYSOURCECTXMENUACTION_H
