/**
* @author Aldebaran Robotics
* Aldebaran Robotics (c) 2013 All Rights Reserved
*/

#ifndef BEHAVIORLOADER_P_HPP_
#define BEHAVIORLOADER_P_HPP_

#include <qimessaging/session.hpp>
#include <qi/atomic.hpp>
#include <qitype/anyobject.hpp>
#include <qicore/behavior.hpp>
#include <qicore-compat/model/flowdiagrammodel.hpp>
#include <qicore-compat/model/choregrapheprojectmodel.hpp>
#include <qicore-compat/model/boxinstancemodel.hpp>
#include "python/pythonloader.hpp"
#include "asyncexecuter.hpp"

namespace qi
{
  namespace compat {
    class BehaviorExecuterPrivate
    {
      friend class BehaviorExecuter;
    public:
      BehaviorExecuterPrivate(const std::string &dir, qi::Session &session, bool debug);
      ~BehaviorExecuterPrivate();

      bool loadFlowDiagram(FlowDiagramModel *diagram,
                           bool behaviorsequence = false,
                           int index = 0,
                           const std::string &prefix = "");
      bool loadBehaviorSequence(BehaviorSequenceModel *behaviorSequence);
      bool declaredBox(BoxInstanceModelPtr instance);
      bool declaredPythonBox(BoxInstanceModelPtr instance);
      void initialiseBox(BoxInstanceModelPtr instance, bool rootBox = false);
      void initialiseFlowDiagram(FlowDiagramModel* diagram);
      std::map<std::string, int> initialiseBehaviorSequence(BehaviorSequenceModel* seq,
                                                            const std::string &uid);
      void addTransition(BehaviorModel::Transition &t);
      void connect(qi::AnyObject src,
                   qi::AnyObject dst,
                   const std::string &signal,
                   const std::string &method);

    private:
      ChoregrapheProjectModel _project;
      qi::BehaviorModel _model;
      qi::PythonBoxLoader _pythonCreator;
      qi::AnyObject _behaviorService;
      qi::AnyObject _alresourcemanager;
      qi::AnyObject _almotion;
      qi::AnyObject _almemory;
      boost::mutex _waiter;
      boost::condition_variable _waitcondition;
      std::map<std::string, qi::AnyObject> _timelines;
      std::vector<std::string> _stmvalues;
      bool _debug;
      qi::Atomic<int> _running;

      qi::Promise<void> _finished;

      void onFinished(AnyValue v);
    };
    typedef std::map<std::string, qi::AnyObject> TimlineMap;
  }
}

#endif
