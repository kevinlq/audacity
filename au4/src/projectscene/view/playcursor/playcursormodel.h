#pragma once

#include <QObject>

#include "global/async/asyncable.h"

#include "modularity/ioc.h"
#include "context/iglobalcontext.h"

#include "../clipsview/timelinecontext.h"

namespace au::projectscene {
class PlayCursorModel : public QObject, public muse::async::Asyncable
{
    Q_OBJECT

    Q_PROPERTY(TimelineContext * context READ timelineContext WRITE setTimelineContext NOTIFY timelineContextChanged FINAL)

    Q_PROPERTY(double positionX READ positionX NOTIFY positionXChanged FINAL)

    muse::Inject<context::IGlobalContext> globalContext;

public:
    PlayCursorModel(QObject* parent = nullptr);

    TimelineContext* timelineContext() const;
    void setTimelineContext(TimelineContext* newContext);
    double positionX() const;

    Q_INVOKABLE void init();

signals:
    void timelineContextChanged();
    void positionXChanged();

private:

    playback::IPlayerPtr player() const;

    void updatePositionX(audio::secs_t secs);

    TimelineContext* m_context = nullptr;
    double m_positionX = 0.0;
};
}