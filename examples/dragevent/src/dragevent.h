#ifndef Dragevent_H
#define Dragevent_H

#include <QWidget>

// cumbia
#include <qulogimpl.h>
#include <cucontrolsfactorypool.h>
class CumbiaPool;
// cumbia

namespace Ui {
class Dragevent;
}

class Dragevent : public QWidget
{
    Q_OBJECT

public:
    explicit Dragevent(CumbiaPool *cu_p, QWidget *parent = 0);
    ~Dragevent();

private:
    Ui::Dragevent *ui;

    // cumbia
    CumbiaPool *cu_pool;
    QuLogImpl m_log_impl;
    CuControlsFactoryPool m_ctrl_factory_pool;
    // cumbia
};

#endif // Dragevent_H
