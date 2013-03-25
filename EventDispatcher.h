/** \file EventDispatcher.h
\brief Define the class of the event dispatcher
\author alpha_one_x86
\licence GPL3, see the file COPYING */

#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include <QObject>
#include <QStringList>
#include <QString>
#include <QTimer>
#include <QList>
#include <QUrl>

#include "Environment.h"
#include "Core.h"
#include "SystrayIcon.h"
#include "OptionEngine.h"
#include "HelpDialog.h"
#ifndef ULTRACOPIER_VERSION_PORTABLE
#include "SessionLoader.h"
#endif
#include "CopyListener.h"
#include "OptionDialog.h"
#include "CopyEngineManager.h"
#include "LocalListener.h"
#include "CliParser.h"

/** \brief Define the class of the event dispatcher

This class provide a core for dispatch the event of signal/slot, it checks too if not other instance is running */
class EventDispatcher : public QObject
{
    Q_OBJECT
    public:
        /// \brief Initiate the ultracopier event dispatcher and check if no other session is running
        EventDispatcher();
        /// \brief Destroy the ultracopier event dispatcher
        ~EventDispatcher();
        /// \brief return if need be close
        bool shouldBeClosed();
    public slots:
        /// \brief Quit ultracopier
        void quit();
    signals:
        /** \brief Send that's caught state have changed for CatchedState::Uncatched or CatchedState::Semicatched or CatchedState::Catched
        \see CatchState
        \see tryCatchCopy()
        \see tryUncatchCopy()
        \param State is the new state */
        void catchCopyStateChanged(Ultracopier::CatchState state);
        /** \brief Send that's copy/move task is finished in returning the copyMoveEventId
        \see routeCopyMoveEvent()
        \param copyMoveEventId The task id generated by routeCopyMoveEvent() */
        void copyMoveEventIsFinish(int copyMoveEventId);
    private:
        /// \brief To have counter for increment the copyMoveEventId at each request
        int copyMoveEventIdIndex;
        /// \brief To store windows windows session
        struct CoreSession
        {
            Core * CoreWindow;
            QList<int> copyMoveEventIdManaged;
        };
        /// \brief the systray icon
        SystrayIcon *backgroundIcon;
        /// \brief To lunch event only when the event loop is setup
        QTimer lunchInitFunction;
        /// \brief the help dialog
        HelpDialog theHelp;
        #ifndef ULTRACOPIER_VERSION_PORTABLE
        /// \brief the session loader
        SessionLoader *sessionloader;
        #endif
        bool stopIt;
        CopyListener *copyServer;
        Core *core;
        OptionDialog optionDialog;
        CopyEngineManager *copyEngineList;
        LocalListener localListener;
        CliParser cliParser;
        #ifdef Q_OS_WIN32
        QString GetOSDisplayString();
        #endif
    private slots:
        /// \brief Called when event loop is setup
        void initFunction();
};

#endif // EVENT_DISPATCHER_H
