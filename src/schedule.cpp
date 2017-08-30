/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "schedule.hpp"

#include <qlo/qladdindefines.hpp>
#include <ql/time/schedule.hpp>
#include <qlo/schedule.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void ScheduleWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EffectiveDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEffectiveDate, "EffectiveDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date TerminationDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mTerminationDate, "TerminationDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention ConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mConvention);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention TermDateConvEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mTermDateConv);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DateGeneration::Rule GenRuleEnum =
      ObjectHandler::Create<QuantLib::DateGeneration::Rule>()(mGenRule);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date FirstDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mFirstDate, "FirstDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date NextToLastDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mNextToLastDate, "NextToLastDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSchedule(
          mObjectID,
          mEffectiveDate,
          mTerminationDate,
          mTenor,
          mCalendar,
          mConvention,
          mTermDateConv,
          mGenRule,
          mEndOfMonth,
          mFirstDate,
          mNextToLastDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Schedule(
          valueObject,
          EffectiveDateLib,
          TerminationDateLib,
          TenorLib,
          CalendarEnum,
          ConventionEnum,
          TermDateConvEnum,
          GenRuleEnum,
          mEndOfMonth,
          FirstDateLib,
          NextToLastDateLib,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::Schedule) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Convention is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("TermDateConv is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("GenRule is required.");
  }
  if (info.Length() == 8 || !info[8]->IsBoolean()) {
      return Nan::ThrowError("EndOfMonth is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t EffectiveDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t TerminationDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[3]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[4]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strConvention(info[5]->ToString());
  string ConventionCpp(strdup(*strConvention));

  // convert js argument to c++ type
  String::Utf8Value strTermDateConv(info[6]->ToString());
  string TermDateConvCpp(strdup(*strTermDateConv));

  // convert js argument to c++ type
  String::Utf8Value strGenRule(info[7]->ToString());
  string GenRuleCpp(strdup(*strGenRule));

  // convert js argument to c++ type
  bool EndOfMonthCpp = Nan::To<bool>(info[8]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t FirstDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[9]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NextToLastDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[10]).FromJust()));

 
  // launch worker
  ScheduleWorker* worker = new ScheduleWorker(
    ObjectIDCpp
,     EffectiveDateCpp
,     TerminationDateCpp
,     TenorCpp
,     CalendarCpp
,     ConventionCpp
,     TermDateConvCpp
,     GenRuleCpp
,     EndOfMonthCpp
,     FirstDateCpp
,     NextToLastDateCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<String>(worker->mReturnValue).ToLocalChecked()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleFromDateVectorWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  std::vector<QuantLib::Date> EffectiveDateLib = ObjectHandler::vector::convert2<QuantLib::Date>(
      mEffectiveDate, "EffectiveDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlScheduleFromDateVector(
          mObjectID,
          mEffectiveDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Schedule(
          valueObject,
          EffectiveDateLib,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleFromDateVector) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("EffectiveDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>EffectiveDateCpp;

  Local<Array> EffectiveDateArray = info[1].As<Array>();
  for (unsigned int i = 0; i < EffectiveDateArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(EffectiveDateArray, i).ToLocalChecked()).FromJust()));
    EffectiveDateCpp.push_back(tmp);
  }

 
  // launch worker
  ScheduleFromDateVectorWorker* worker = new ScheduleFromDateVectorWorker(
    ObjectIDCpp
,     EffectiveDateCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<String>(worker->mReturnValue).ToLocalChecked()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleTruncatedWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(OriginalScheduleLibObjPtr, mOriginalSchedule,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date TruncationDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mTruncationDate, "TruncationDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlScheduleTruncated(
          mObjectID,
          mOriginalSchedule,
          mTruncationDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::Schedule(
          valueObject,
          OriginalScheduleLibObjPtr,
          TruncationDateLib,
          false
      ));

    // Store the Object in the Repository
    mReturnValue = ObjectHandler::Repository::instance().storeObject(mObjectID, object, false, valueObject);
    
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleTruncated) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("OriginalSchedule is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strOriginalSchedule(info[1]->ToString());
  string OriginalScheduleCpp(strdup(*strOriginalSchedule));

  // convert js argument to c++ type
  ObjectHandler::property_t TruncationDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

 
  // launch worker
  ScheduleTruncatedWorker* worker = new ScheduleTruncatedWorker(
    ObjectIDCpp
,     OriginalScheduleCpp
,     TruncationDateCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<String>(worker->mReturnValue).ToLocalChecked()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleSizeWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // invoke the member function
  QuantLib::Size returnValue = ObjectIDLibObjPtr->size(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleSize) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleSizeWorker* worker = new ScheduleSizeWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void SchedulePreviousDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

     
  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->previousDate(
        RefDateLib
       );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SchedulePreviousDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  SchedulePreviousDateWorker* worker = new SchedulePreviousDateWorker(
    ObjectIDCpp
,     RefDateCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleNextDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date RefDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mRefDate, "RefDate");

     
  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->nextDate(
        RefDateLib
       );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleNextDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t RefDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

 
  // launch worker
  ScheduleNextDateWorker* worker = new ScheduleNextDateWorker(
    ObjectIDCpp
,     RefDateCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleDatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDLibObjPtr->dates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleDatesWorker* worker = new ScheduleDatesWorker(
    ObjectIDCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<Number>(worker->mReturnValue[i]));
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpArray
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleIsRegularWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size IndexLib;
  QuantLibAddin::cppToLibrary(mIndex, IndexLib);

     
  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->isRegular(
        IndexLib
       );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleIsRegular) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Index is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long IndexCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  ScheduleIsRegularWorker* worker = new ScheduleIsRegularWorker(
    ObjectIDCpp
,     IndexCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Boolean>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleEmptyWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->empty(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleEmpty) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleEmptyWorker* worker = new ScheduleEmptyWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Boolean>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleCalendarWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // invoke the member function
  QuantLib::Calendar returnValue = ObjectIDLibObjPtr->calendar(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleCalendar) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleCalendarWorker* worker = new ScheduleCalendarWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<String>(worker->mReturnValue).ToLocalChecked()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleStartDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->startDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleStartDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleStartDateWorker* worker = new ScheduleStartDateWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleEndDateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->endDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleEndDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleEndDateWorker* worker = new ScheduleEndDateWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Number>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleTenorWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // invoke the member function
  QuantLib::Period returnValue = ObjectIDLibObjPtr->tenor(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleTenor) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleTenorWorker* worker = new ScheduleTenorWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<String>(worker->mReturnValue).ToLocalChecked()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleBDCWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // invoke the member function
  QuantLib::BusinessDayConvention returnValue = ObjectIDLibObjPtr->businessDayConvention(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleBDC) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleBDCWorker* worker = new ScheduleBDCWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<String>(worker->mReturnValue).ToLocalChecked()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleTerminationDateBDCWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // invoke the member function
  QuantLib::BusinessDayConvention returnValue = ObjectIDLibObjPtr->businessDayConvention(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleTerminationDateBDC) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleTerminationDateBDCWorker* worker = new ScheduleTerminationDateBDCWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<String>(worker->mReturnValue).ToLocalChecked()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleRuleWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // invoke the member function
  QuantLib::DateGeneration::Rule returnValue = ObjectIDLibObjPtr->rule(
      );


  std::ostringstream os;
  os << returnValue;
  mReturnValue = os.str();

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleRule) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleRuleWorker* worker = new ScheduleRuleWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<String>(worker->mReturnValue).ToLocalChecked()
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void ScheduleEndOfMonthWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::Schedule, QuantLib::Schedule)

     
  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->endOfMonth(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ScheduleEndOfMonth) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  ScheduleEndOfMonthWorker* worker = new ScheduleEndOfMonthWorker(
    ObjectIDCpp
   );

  worker->Execute();


  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      Nan::New<Boolean>(worker->mReturnValue)
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}
 