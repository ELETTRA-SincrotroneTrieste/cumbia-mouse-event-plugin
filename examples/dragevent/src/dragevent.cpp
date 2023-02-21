#include "dragevent.h"
// cumbia
#include <cumbiapool.h>
#include <cuserviceprovider.h>
#include <cumacros.h>
#include <quapps.h>
// cumbia

#include <QVBoxLayout>
#include <qulabel.h>
#include <QLabel>

Dragevent::Dragevent(CumbiaPool *cumbia_pool, QWidget *parent) :
    QWidget(parent)
{
    // cumbia
    CuModuleLoader mloader(cumbia_pool, &m_ctrl_factory_pool, &m_log_impl);
    cu_pool = cumbia_pool;

    QVBoxLayout *vlo = new QVBoxLayout(this);
    QuLabel *la = new QuLabel(this, cu_pool, m_ctrl_factory_pool);
    la->setSource("$1/double_scalar");
    QLabel *ql = new QLabel(la->source(), this);
    vlo->addWidget(ql);
    vlo->addWidget(la);

    foreach(const QString &m, mloader.modules())
        printf("cumbia module: %s available\n", qstoc(m));
    // mloader.modules() to get the list of loaded modules
    // cumbia
}

Dragevent::~Dragevent() {
}
