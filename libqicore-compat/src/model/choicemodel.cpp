/**
* @author Aldebaran Robotics
* Aldebaran Robotics (c) 2012 All Rights Reserved
*/

#include <qicore-compat/model/parametermodel.hpp>
#include <qicore-compat/model/choicemodel.hpp>
#include "choicemodel_p.hpp"

#include <qi/log.hpp>
qiLogCategory("QiCore-Compat.ChoiceModel");

namespace qi {

  //----------------------------------------Private Class------------------------------------------//

  ChoiceModelPrivate::ChoiceModelPrivate(AutoGenericValuePtr value) :
    _value(value.clone()),
    _isValid(true)
  {
  }

  ChoiceModelPrivate::ChoiceModelPrivate(boost::shared_ptr<const AL::XmlElement> elt,
                                         const Signature& type) :
    _value(),
    _isValid(true)
  {
    if(type.isConvertibleTo(Signature::fromType(Signature::Type_Bool)))
    {
      bool valueBool;
      elt->getAttribute("value", valueBool);
      _value = GenericValuePtr(&valueBool).clone();
    }
    else if(type.isConvertibleTo(Signature::fromType(Signature::Type_Int32)))
    {
      int valueInt;
      elt->getAttribute("value", valueInt);
      _value = GenericValuePtr(&valueInt).clone();
    }
    else if(type.isConvertibleTo(Signature::fromType(Signature::Type_Double)))
    {
      double valueDouble;
      elt->getAttribute("value", valueDouble);
      _value = GenericValuePtr(&valueDouble).clone();
    }
    else if(type.isConvertibleTo(Signature::fromType(Signature::Type_String)))
    {
      std::string valueString;
      elt->getAttribute("value", valueString);
      _value = GenericValuePtr(&valueString).clone();
    }
    else
    {
      _isValid = false;
    }
  }

  //-----------------------------------------Public Class------------------------------------------//

  ChoiceModel::ChoiceModel(AutoGenericValuePtr value) :
    _p(new ChoiceModelPrivate(value))
  {
  }

  ChoiceModel::ChoiceModel(boost::shared_ptr<const AL::XmlElement> elt, const Signature &type) :
    _p(new ChoiceModelPrivate(elt, type))
  {
  }

  ChoiceModel::~ChoiceModel()
  {
    delete _p;
  }

  GenericValuePtr ChoiceModel::getValue() const
  {
    return _p->_value;
  }

  void ChoiceModel::setValue(AutoGenericValuePtr value)
  {
    _p->_value = value.clone();
  }
}
