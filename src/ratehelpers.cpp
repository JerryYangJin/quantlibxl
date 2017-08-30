/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "ratehelpers.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/ratehelpers.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <qlo/schedule.hpp>
#include <qlo/bonds.hpp>
#include <qlo/yieldtermstructures.hpp>
#include <qlo/indexes/ibor/euribor.hpp>
#include <ql/termstructures/yield/ratehelpers.hpp>
#include <ql/indexes/swapindex.hpp>
#include <ql/instruments/bonds/fixedratebond.hpp>
#include <ql/indexes/ibor/euribor.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void DepositRateHelperWorker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> RateLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mRate, "Rate");


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlDepositRateHelper(
          mObjectID,
          mRate,
          mIborIndex,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::DepositRateHelper(
          valueObject,
          RateLibObj,
          IborIndexLibObjPtr,
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

NAN_METHOD(QuantLibXL::DepositRateHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t RateCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[2]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

 
  // launch worker
  DepositRateHelperWorker* worker = new DepositRateHelperWorker(
    ObjectIDCpp
,     RateCpp
,     IborIndexCpp
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

void DepositRateHelper2Worker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> RateLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mRate, "Rate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
      mFixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention ConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mConvention);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlDepositRateHelper2(
          mObjectID,
          mRate,
          mTenor,
          mFixingDays,
          mCalendar,
          mConvention,
          mEndOfMonth,
          mDayCounter,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::DepositRateHelper(
          valueObject,
          RateLibObj,
          TenorLib,
          FixingDaysLib,
          CalendarEnum,
          ConventionEnum,
          mEndOfMonth,
          DayCounterEnum,
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

NAN_METHOD(QuantLibXL::DepositRateHelper2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Convention is required.");
  }
  if (info.Length() == 6 || !info[6]->IsBoolean()) {
      return Nan::ThrowError("EndOfMonth is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t RateCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[2]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[4]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strConvention(info[5]->ToString());
  string ConventionCpp(strdup(*strConvention));

  // convert js argument to c++ type
  bool EndOfMonthCpp = Nan::To<bool>(info[6]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[7]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

 
  // launch worker
  DepositRateHelper2Worker* worker = new DepositRateHelper2Worker(
    ObjectIDCpp
,     RateCpp
,     TenorCpp
,     FixingDaysCpp
,     CalendarCpp
,     ConventionCpp
,     EndOfMonthCpp
,     DayCounterCpp
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

void SwapRateHelperWorker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> RateLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mRate, "Rate");


  // convert object IDs into library objects
  OH_GET_REFERENCE(SwapIndexLibObjPtr, mSwapIndex,
      QuantLibAddin::SwapIndex, QuantLib::SwapIndex)


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> SpreadLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mSpread, "Spread");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period ForwardStartLib;
  QuantLibAddin::cppToLibrary(mForwardStart, ForwardStartLib);


  // convert object IDs into library objects
  OH_GET_OBJECT(DiscountingCurveCoerce, mDiscountingCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              DiscountingCurveCoerce);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Pillar::Choice PillarDateEnum =
      ObjectHandler::Create<QuantLib::Pillar::Choice>()(mPillarDate);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date CustomPillarDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mCustomPillarDate, "CustomPillarDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSwapRateHelper(
          mObjectID,
          mRate,
          mSwapIndex,
          mSpread,
          mForwardStart,
          mDiscountingCurve,
          mPillarDate,
          mCustomPillarDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::SwapRateHelper(
          valueObject,
          RateLibObj,
          SwapIndexLibObjPtr,
          SpreadLibObj,
          ForwardStartLib,
          DiscountingCurveLibObj,
          PillarDateEnum,
          CustomPillarDateLib,
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

NAN_METHOD(QuantLibXL::SwapRateHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("SwapIndex is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("ForwardStart is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("PillarDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t RateCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strSwapIndex(info[2]->ToString());
  string SwapIndexCpp(strdup(*strSwapIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t SpreadCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strForwardStart(info[4]->ToString());
  string ForwardStartCpp(strdup(*strForwardStart));

  // convert js argument to c++ type
  ObjectHandler::property_t DiscountingCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[5]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strPillarDate(info[6]->ToString());
  string PillarDateCpp(strdup(*strPillarDate));

  // convert js argument to c++ type
  ObjectHandler::property_t CustomPillarDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[7]).FromJust()));

 
  // launch worker
  SwapRateHelperWorker* worker = new SwapRateHelperWorker(
    ObjectIDCpp
,     RateCpp
,     SwapIndexCpp
,     SpreadCpp
,     ForwardStartCpp
,     DiscountingCurveCpp
,     PillarDateCpp
,     CustomPillarDateCpp
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

void SwapRateHelper2Worker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> RateLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mRate, "Rate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural SettlDaysLib = ObjectHandler::convert2<long>(
      mSettlDays, "SettlDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Frequency FixedLegFrequencyEnum =
      ObjectHandler::Create<QuantLib::Frequency>()(mFixedLegFrequency);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention FixedLegConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mFixedLegConvention);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter FixedLegDayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mFixedLegDayCounter);


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> SpreadLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mSpread, "Spread");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period ForwardStartLib;
  QuantLibAddin::cppToLibrary(mForwardStart, ForwardStartLib);


  // convert object IDs into library objects
  OH_GET_OBJECT(DiscountingCurveCoerce, mDiscountingCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              DiscountingCurveCoerce);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Pillar::Choice PillarDateEnum =
      ObjectHandler::Create<QuantLib::Pillar::Choice>()(mPillarDate);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date CustomPillarDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mCustomPillarDate, "CustomPillarDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlSwapRateHelper2(
          mObjectID,
          mRate,
          mSettlDays,
          mTenor,
          mCalendar,
          mFixedLegFrequency,
          mFixedLegConvention,
          mFixedLegDayCounter,
          mIborIndex,
          mSpread,
          mForwardStart,
          mDiscountingCurve,
          mPillarDate,
          mCustomPillarDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::SwapRateHelper(
          valueObject,
          RateLibObj,
          SettlDaysLib,
          TenorLib,
          CalendarEnum,
          FixedLegFrequencyEnum,
          FixedLegConventionEnum,
          FixedLegDayCounterEnum,
          IborIndexLibObjPtr,
          SpreadLibObj,
          ForwardStartLib,
          DiscountingCurveLibObj,
          PillarDateEnum,
          CustomPillarDateLib,
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

NAN_METHOD(QuantLibXL::SwapRateHelper2) {

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
      return Nan::ThrowError("FixedLegFrequency is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("FixedLegConvention is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("FixedLegDayCounter is required.");
  }
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 10 || !info[10]->IsString()) {
      return Nan::ThrowError("ForwardStart is required.");
  }
  if (info.Length() == 12 || !info[12]->IsString()) {
      return Nan::ThrowError("PillarDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t RateCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[3]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[4]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strFixedLegFrequency(info[5]->ToString());
  string FixedLegFrequencyCpp(strdup(*strFixedLegFrequency));

  // convert js argument to c++ type
  String::Utf8Value strFixedLegConvention(info[6]->ToString());
  string FixedLegConventionCpp(strdup(*strFixedLegConvention));

  // convert js argument to c++ type
  String::Utf8Value strFixedLegDayCounter(info[7]->ToString());
  string FixedLegDayCounterCpp(strdup(*strFixedLegDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[8]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t SpreadCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[9]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strForwardStart(info[10]->ToString());
  string ForwardStartCpp(strdup(*strForwardStart));

  // convert js argument to c++ type
  ObjectHandler::property_t DiscountingCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[11]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strPillarDate(info[12]->ToString());
  string PillarDateCpp(strdup(*strPillarDate));

  // convert js argument to c++ type
  ObjectHandler::property_t CustomPillarDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[13]).FromJust()));

 
  // launch worker
  SwapRateHelper2Worker* worker = new SwapRateHelper2Worker(
    ObjectIDCpp
,     RateCpp
,     SettlDaysCpp
,     TenorCpp
,     CalendarCpp
,     FixedLegFrequencyCpp
,     FixedLegConventionCpp
,     FixedLegDayCounterCpp
,     IborIndexCpp
,     SpreadCpp
,     ForwardStartCpp
,     DiscountingCurveCpp
,     PillarDateCpp
,     CustomPillarDateCpp
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

void OISRateHelperWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural SettlDaysLib = ObjectHandler::convert2<long>(
      mSettlDays, "SettlDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> FixedRateLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mFixedRate, "FixedRate");


  // convert object IDs into library objects
  OH_GET_REFERENCE(ONIndexLibObjPtr, mONIndex,
      QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)


  // convert object IDs into library objects
  OH_GET_OBJECT(DiscountingCurveCoerce, mDiscountingCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              DiscountingCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlOISRateHelper(
          mObjectID,
          mSettlDays,
          mTenor,
          mFixedRate,
          mONIndex,
          mDiscountingCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::OISRateHelper(
          valueObject,
          SettlDaysLib,
          TenorLib,
          FixedRateLibObj,
          ONIndexLibObjPtr,
          DiscountingCurveLibObj,
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

NAN_METHOD(QuantLibXL::OISRateHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("ONIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t SettlDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[2]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t FixedRateCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strONIndex(info[4]->ToString());
  string ONIndexCpp(strdup(*strONIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t DiscountingCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[5]).FromJust()));

 
  // launch worker
  OISRateHelperWorker* worker = new OISRateHelperWorker(
    ObjectIDCpp
,     SettlDaysCpp
,     TenorCpp
,     FixedRateCpp
,     ONIndexCpp
,     DiscountingCurveCpp
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

void DatedOISRateHelperWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEndDate, "EndDate");


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> FixedRateLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mFixedRate, "FixedRate");


  // convert object IDs into library objects
  OH_GET_REFERENCE(ONIndexLibObjPtr, mONIndex,
      QuantLibAddin::OvernightIndex, QuantLib::OvernightIndex)


  // convert object IDs into library objects
  OH_GET_OBJECT(DiscountingCurveCoerce, mDiscountingCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> DiscountingCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              DiscountingCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlDatedOISRateHelper(
          mObjectID,
          mStartDate,
          mEndDate,
          mFixedRate,
          mONIndex,
          mDiscountingCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::DatedOISRateHelper(
          valueObject,
          StartDateLib,
          EndDateLib,
          FixedRateLibObj,
          ONIndexLibObjPtr,
          DiscountingCurveLibObj,
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

NAN_METHOD(QuantLibXL::DatedOISRateHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("ONIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t EndDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t FixedRateCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strONIndex(info[4]->ToString());
  string ONIndexCpp(strdup(*strONIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t DiscountingCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[5]).FromJust()));

 
  // launch worker
  DatedOISRateHelperWorker* worker = new DatedOISRateHelperWorker(
    ObjectIDCpp
,     StartDateCpp
,     EndDateCpp
,     FixedRateCpp
,     ONIndexCpp
,     DiscountingCurveCpp
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

void FraRateHelperWorker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> RateLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mRate, "Rate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period PeriodToStartLib;
  QuantLibAddin::cppToLibrary(mPeriodToStart, PeriodToStartLib);


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Pillar::Choice PillarDateEnum =
      ObjectHandler::Create<QuantLib::Pillar::Choice>()(mPillarDate);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date CustomPillarDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mCustomPillarDate, "CustomPillarDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFraRateHelper(
          mObjectID,
          mRate,
          mPeriodToStart,
          mIborIndex,
          mPillarDate,
          mCustomPillarDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FraRateHelper(
          valueObject,
          RateLibObj,
          PeriodToStartLib,
          IborIndexLibObjPtr,
          PillarDateEnum,
          CustomPillarDateLib,
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

NAN_METHOD(QuantLibXL::FraRateHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("PeriodToStart is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("PillarDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t RateCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strPeriodToStart(info[2]->ToString());
  string PeriodToStartCpp(strdup(*strPeriodToStart));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[3]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  String::Utf8Value strPillarDate(info[4]->ToString());
  string PillarDateCpp(strdup(*strPillarDate));

  // convert js argument to c++ type
  ObjectHandler::property_t CustomPillarDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[5]).FromJust()));

 
  // launch worker
  FraRateHelperWorker* worker = new FraRateHelperWorker(
    ObjectIDCpp
,     RateCpp
,     PeriodToStartCpp
,     IborIndexCpp
,     PillarDateCpp
,     CustomPillarDateCpp
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

void FraRateHelper2Worker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> RateLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mRate, "Rate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period PeriodToStartLib;
  QuantLibAddin::cppToLibrary(mPeriodToStart, PeriodToStartLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural LengthInMonthsLib = ObjectHandler::convert2<long>(
      mLengthInMonths, "LengthInMonths", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
      mFixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention ConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mConvention);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Pillar::Choice PillarDateEnum =
      ObjectHandler::Create<QuantLib::Pillar::Choice>()(mPillarDate);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date CustomPillarDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mCustomPillarDate, "CustomPillarDate");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFraRateHelper2(
          mObjectID,
          mRate,
          mPeriodToStart,
          mLengthInMonths,
          mFixingDays,
          mCalendar,
          mConvention,
          mEndOfMonth,
          mDayCounter,
          mPillarDate,
          mCustomPillarDate,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FraRateHelper(
          valueObject,
          RateLibObj,
          PeriodToStartLib,
          LengthInMonthsLib,
          FixingDaysLib,
          CalendarEnum,
          ConventionEnum,
          mEndOfMonth,
          DayCounterEnum,
          PillarDateEnum,
          CustomPillarDateLib,
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

NAN_METHOD(QuantLibXL::FraRateHelper2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("PeriodToStart is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("Convention is required.");
  }
  if (info.Length() == 7 || !info[7]->IsBoolean()) {
      return Nan::ThrowError("EndOfMonth is required.");
  }
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 9 || !info[9]->IsString()) {
      return Nan::ThrowError("PillarDate is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t RateCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strPeriodToStart(info[2]->ToString());
  string PeriodToStartCpp(strdup(*strPeriodToStart));

  // convert js argument to c++ type
  ObjectHandler::property_t LengthInMonthsCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[5]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strConvention(info[6]->ToString());
  string ConventionCpp(strdup(*strConvention));

  // convert js argument to c++ type
  bool EndOfMonthCpp = Nan::To<bool>(info[7]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[8]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strPillarDate(info[9]->ToString());
  string PillarDateCpp(strdup(*strPillarDate));

  // convert js argument to c++ type
  ObjectHandler::property_t CustomPillarDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[10]).FromJust()));

 
  // launch worker
  FraRateHelper2Worker* worker = new FraRateHelper2Worker(
    ObjectIDCpp
,     RateCpp
,     PeriodToStartCpp
,     LengthInMonthsCpp
,     FixingDaysCpp
,     CalendarCpp
,     ConventionCpp
,     EndOfMonthCpp
,     DayCounterCpp
,     PillarDateCpp
,     CustomPillarDateCpp
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

void BondHelperWorker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> PriceLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mPrice, "Price");


  // convert object IDs into library objects
  OH_GET_REFERENCE(BondLibObjPtr, mBond,
      QuantLibAddin::Bond, QuantLib::Bond)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlBondHelper(
          mObjectID,
          mPrice,
          mBond,
          mUseCleanPrice,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::BondHelper(
          valueObject,
          PriceLibObj,
          BondLibObjPtr,
          mUseCleanPrice,
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

NAN_METHOD(QuantLibXL::BondHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("Bond is required.");
  }
  if (info.Length() == 3 || !info[3]->IsBoolean()) {
      return Nan::ThrowError("UseCleanPrice is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t PriceCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strBond(info[2]->ToString());
  string BondCpp(strdup(*strBond));

  // convert js argument to c++ type
  bool UseCleanPriceCpp = Nan::To<bool>(info[3]).FromJust();

 
  // launch worker
  BondHelperWorker* worker = new BondHelperWorker(
    ObjectIDCpp
,     PriceCpp
,     BondCpp
,     UseCleanPriceCpp
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

void FixedRateBondHelperWorker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> PriceLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mPrice, "Price");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size SettlementDaysLib;
  QuantLibAddin::cppToLibrary(mSettlementDays, SettlementDaysLib);


  // convert object IDs into library objects
  OH_GET_REFERENCE(ScheduleIDLibObjPtr, mScheduleID,
      QuantLibAddin::Schedule, QuantLib::Schedule)


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention PaymentBDCEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mPaymentBDC);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date IssueDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mIssueDate, "IssueDate");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar PaymentCalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mPaymentCalendar);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period ExCouponPeriodLib;
  QuantLibAddin::cppToLibrary(mExCouponPeriod, ExCouponPeriodLib);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar ExCouponCalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mExCouponCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention ExCouponBDCEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mExCouponBDC);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFixedRateBondHelper(
          mObjectID,
          mPrice,
          mSettlementDays,
          mFaceAmount,
          mScheduleID,
          mCoupons,
          mDayCounter,
          mPaymentBDC,
          mRedemption,
          mIssueDate,
          mPaymentCalendar,
          mExCouponPeriod,
          mExCouponCalendar,
          mExCouponBDC,
          mExCouponEndOfMonth,
          mUseCleanPrice,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FixedRateBondHelper(
          valueObject,
          PriceLibObj,
          SettlementDaysLib,
          mFaceAmount,
          ScheduleIDLibObjPtr,
          mCoupons,
          DayCounterEnum,
          PaymentBDCEnum,
          mRedemption,
          IssueDateLib,
          PaymentCalendarEnum,
          ExCouponPeriodLib,
          ExCouponCalendarEnum,
          ExCouponBDCEnum,
          mExCouponEndOfMonth,
          mUseCleanPrice,
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

NAN_METHOD(QuantLibXL::FixedRateBondHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("SettlementDays is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("FaceAmount is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("ScheduleID is required.");
  }
  if (info.Length() == 5 || !info[5]->IsArray()) {
      return Nan::ThrowError("Coupons is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("PaymentBDC is required.");
  }
  if (info.Length() == 8 || !info[8]->IsNumber()) {
      return Nan::ThrowError("Redemption is required.");
  }
  if (info.Length() == 10 || !info[10]->IsString()) {
      return Nan::ThrowError("PaymentCalendar is required.");
  }
  if (info.Length() == 11 || !info[11]->IsString()) {
      return Nan::ThrowError("ExCouponPeriod is required.");
  }
  if (info.Length() == 12 || !info[12]->IsString()) {
      return Nan::ThrowError("ExCouponCalendar is required.");
  }
  if (info.Length() == 13 || !info[13]->IsString()) {
      return Nan::ThrowError("ExCouponBDC is required.");
  }
  if (info.Length() == 14 || !info[14]->IsBoolean()) {
      return Nan::ThrowError("ExCouponEndOfMonth is required.");
  }
  if (info.Length() == 15 || !info[15]->IsBoolean()) {
      return Nan::ThrowError("UseCleanPrice is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t PriceCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  long SettlementDaysCpp = Nan::To<int32_t>(info[2]).FromJust();

  // convert js argument to c++ type
  double FaceAmountCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strScheduleID(info[4]->ToString());
  string ScheduleIDCpp(strdup(*strScheduleID));

  // convert js argument to c++ type
  std::vector<double>CouponsCpp;

  Local<Array> CouponsArray = info[5].As<Array>();
  for (unsigned int i = 0; i < CouponsArray->Length(); i++){
    CouponsCpp.push_back(Nan::To<double>(Nan::Get(CouponsArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[6]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strPaymentBDC(info[7]->ToString());
  string PaymentBDCCpp(strdup(*strPaymentBDC));

  // convert js argument to c++ type
  double RedemptionCpp = Nan::To<double>(info[8]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t IssueDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[9]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strPaymentCalendar(info[10]->ToString());
  string PaymentCalendarCpp(strdup(*strPaymentCalendar));

  // convert js argument to c++ type
  String::Utf8Value strExCouponPeriod(info[11]->ToString());
  string ExCouponPeriodCpp(strdup(*strExCouponPeriod));

  // convert js argument to c++ type
  String::Utf8Value strExCouponCalendar(info[12]->ToString());
  string ExCouponCalendarCpp(strdup(*strExCouponCalendar));

  // convert js argument to c++ type
  String::Utf8Value strExCouponBDC(info[13]->ToString());
  string ExCouponBDCCpp(strdup(*strExCouponBDC));

  // convert js argument to c++ type
  bool ExCouponEndOfMonthCpp = Nan::To<bool>(info[14]).FromJust();

  // convert js argument to c++ type
  bool UseCleanPriceCpp = Nan::To<bool>(info[15]).FromJust();

 
  // launch worker
  FixedRateBondHelperWorker* worker = new FixedRateBondHelperWorker(
    ObjectIDCpp
,     PriceCpp
,     SettlementDaysCpp
,     FaceAmountCpp
,     ScheduleIDCpp
,     CouponsCpp
,     DayCounterCpp
,     PaymentBDCCpp
,     RedemptionCpp
,     IssueDateCpp
,     PaymentCalendarCpp
,     ExCouponPeriodCpp
,     ExCouponCalendarCpp
,     ExCouponBDCCpp
,     ExCouponEndOfMonthCpp
,     UseCleanPriceCpp
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

void FuturesRateHelperWorker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> PriceLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mPrice, "Price");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Futures::Type FuturesTypeEnum =
      ObjectHandler::Create<QuantLib::Futures::Type>()(mFuturesType);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date FuturesDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mFuturesDate, "FuturesDate");


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mConvexityAdjQuote, "ConvexityAdjQuote");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFuturesRateHelper(
          mObjectID,
          mPrice,
          mFuturesType,
          mFuturesDate,
          mIborIndex,
          mConvexityAdjQuote,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FuturesRateHelper(
          valueObject,
          PriceLibObj,
          FuturesTypeEnum,
          FuturesDateLib,
          IborIndexLibObjPtr,
          ConvexityAdjQuoteLibObj,
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

NAN_METHOD(QuantLibXL::FuturesRateHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("FuturesType is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t PriceCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strFuturesType(info[2]->ToString());
  string FuturesTypeCpp(strdup(*strFuturesType));

  // convert js argument to c++ type
  ObjectHandler::property_t FuturesDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[4]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  ObjectHandler::property_t ConvexityAdjQuoteCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[5]).FromJust()));

 
  // launch worker
  FuturesRateHelperWorker* worker = new FuturesRateHelperWorker(
    ObjectIDCpp
,     PriceCpp
,     FuturesTypeCpp
,     FuturesDateCpp
,     IborIndexCpp
,     ConvexityAdjQuoteCpp
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

void FuturesRateHelper2Worker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> PriceLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mPrice, "Price");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Futures::Type FuturesTypeEnum =
      ObjectHandler::Create<QuantLib::Futures::Type>()(mFuturesType);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date FuturesDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mFuturesDate, "FuturesDate");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention ConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mConvention);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mConvexityAdjQuote, "ConvexityAdjQuote");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFuturesRateHelper2(
          mObjectID,
          mPrice,
          mFuturesType,
          mFuturesDate,
          mLengthInMonths,
          mCalendar,
          mConvention,
          mEndOfMonth,
          mDayCounter,
          mConvexityAdjQuote,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FuturesRateHelper(
          valueObject,
          PriceLibObj,
          FuturesTypeEnum,
          FuturesDateLib,
          mLengthInMonths,
          CalendarEnum,
          ConventionEnum,
          mEndOfMonth,
          DayCounterEnum,
          ConvexityAdjQuoteLibObj,
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

NAN_METHOD(QuantLibXL::FuturesRateHelper2) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("FuturesType is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("LengthInMonths is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("Convention is required.");
  }
  if (info.Length() == 7 || !info[7]->IsBoolean()) {
      return Nan::ThrowError("EndOfMonth is required.");
  }
  if (info.Length() == 8 || !info[8]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t PriceCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strFuturesType(info[2]->ToString());
  string FuturesTypeCpp(strdup(*strFuturesType));

  // convert js argument to c++ type
  ObjectHandler::property_t FuturesDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  long LengthInMonthsCpp = Nan::To<int32_t>(info[4]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[5]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strConvention(info[6]->ToString());
  string ConventionCpp(strdup(*strConvention));

  // convert js argument to c++ type
  bool EndOfMonthCpp = Nan::To<bool>(info[7]).FromJust();

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[8]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  ObjectHandler::property_t ConvexityAdjQuoteCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[9]).FromJust()));

 
  // launch worker
  FuturesRateHelper2Worker* worker = new FuturesRateHelper2Worker(
    ObjectIDCpp
,     PriceCpp
,     FuturesTypeCpp
,     FuturesDateCpp
,     LengthInMonthsCpp
,     CalendarCpp
,     ConventionCpp
,     EndOfMonthCpp
,     DayCounterCpp
,     ConvexityAdjQuoteCpp
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

void FuturesRateHelper3Worker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> PriceLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mPrice, "Price");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Futures::Type FuturesTypeEnum =
      ObjectHandler::Create<QuantLib::Futures::Type>()(mFuturesType);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date FuturesDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mFuturesDate, "FuturesDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEndDate, "EndDate");


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> ConvexityAdjQuoteLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mConvexityAdjQuote, "ConvexityAdjQuote");

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFuturesRateHelper3(
          mObjectID,
          mPrice,
          mFuturesType,
          mFuturesDate,
          mEndDate,
          mDayCounter,
          mConvexityAdjQuote,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FuturesRateHelper(
          valueObject,
          PriceLibObj,
          FuturesTypeEnum,
          FuturesDateLib,
          EndDateLib,
          DayCounterEnum,
          ConvexityAdjQuoteLibObj,
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

NAN_METHOD(QuantLibXL::FuturesRateHelper3) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("FuturesType is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t PriceCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strFuturesType(info[2]->ToString());
  string FuturesTypeCpp(strdup(*strFuturesType));

  // convert js argument to c++ type
  ObjectHandler::property_t FuturesDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t EndDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[5]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  ObjectHandler::property_t ConvexityAdjQuoteCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[6]).FromJust()));

 
  // launch worker
  FuturesRateHelper3Worker* worker = new FuturesRateHelper3Worker(
    ObjectIDCpp
,     PriceCpp
,     FuturesTypeCpp
,     FuturesDateCpp
,     EndDateCpp
,     DayCounterCpp
,     ConvexityAdjQuoteCpp
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

void FxSwapRateHelperWorker::Execute(){

  try{

  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> FwdPointLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mFwdPoint, "FwdPoint");


  // convert object IDs into library objects
  QuantLib::Handle<QuantLib::Quote> SpotFxLibObj =
      ObjectHandler::convert2< QuantLib::Handle<QuantLib::Quote> >(mSpotFx, "SpotFx");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period TenorLib;
  QuantLibAddin::cppToLibrary(mTenor, TenorLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural FixingDaysLib = ObjectHandler::convert2<long>(
      mFixingDays, "FixingDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::Calendar CalendarEnum =
      ObjectHandler::Create<QuantLib::Calendar>()(mCalendar);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::BusinessDayConvention ConventionEnum =
      ObjectHandler::Create<QuantLib::BusinessDayConvention>()(mConvention);


  // convert object IDs into library objects
  OH_GET_OBJECT(CollateralCurveCoerce, mCollateralCurve, ObjectHandler::Object)
  QuantLib::Handle<QuantLib::YieldTermStructure> CollateralCurveLibObj =
      QuantLibAddin::CoerceHandle<
          QuantLibAddin::YieldTermStructure,
          QuantLib::YieldTermStructure>()(
              CollateralCurveCoerce);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlFxSwapRateHelper(
          mObjectID,
          mFwdPoint,
          mSpotFx,
          mTenor,
          mFixingDays,
          mCalendar,
          mConvention,
          mEndOfMonth,
          mIsFxBaseCurrencyCollateralCurrency,
          mCollateralCurve,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::FxSwapRateHelper(
          valueObject,
          FwdPointLibObj,
          SpotFxLibObj,
          TenorLib,
          FixingDaysLib,
          CalendarEnum,
          ConventionEnum,
          mEndOfMonth,
          mIsFxBaseCurrencyCollateralCurrency,
          CollateralCurveLibObj,
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

NAN_METHOD(QuantLibXL::FxSwapRateHelper) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 3 || !info[3]->IsString()) {
      return Nan::ThrowError("Tenor is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("Calendar is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("Convention is required.");
  }
  if (info.Length() == 7 || !info[7]->IsBoolean()) {
      return Nan::ThrowError("EndOfMonth is required.");
  }
  if (info.Length() == 8 || !info[8]->IsBoolean()) {
      return Nan::ThrowError("IsFxBaseCurrencyCollateralCurrency is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  ObjectHandler::property_t FwdPointCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[1]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t SpotFxCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[2]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strTenor(info[3]->ToString());
  string TenorCpp(strdup(*strTenor));

  // convert js argument to c++ type
  ObjectHandler::property_t FixingDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strCalendar(info[5]->ToString());
  string CalendarCpp(strdup(*strCalendar));

  // convert js argument to c++ type
  String::Utf8Value strConvention(info[6]->ToString());
  string ConventionCpp(strdup(*strConvention));

  // convert js argument to c++ type
  bool EndOfMonthCpp = Nan::To<bool>(info[7]).FromJust();

  // convert js argument to c++ type
  bool IsFxBaseCurrencyCollateralCurrencyCpp = Nan::To<bool>(info[8]).FromJust();

  // convert js argument to c++ type
  ObjectHandler::property_t CollateralCurveCpp =
      ObjectHandler::property_t(static_cast<double>(Nan::To<double>(info[9]).FromJust()));

 
  // launch worker
  FxSwapRateHelperWorker* worker = new FxSwapRateHelperWorker(
    ObjectIDCpp
,     FwdPointCpp
,     SpotFxCpp
,     TenorCpp
,     FixingDaysCpp
,     CalendarCpp
,     ConventionCpp
,     EndOfMonthCpp
,     IsFxBaseCurrencyCollateralCurrencyCpp
,     CollateralCurveCpp
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

void RateHelperEarliestDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RateHelper, QuantLib::RateHelper)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->earliestDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperEarliestDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RateHelperEarliestDateWorker* worker = new RateHelperEarliestDateWorker(
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

void RateHelperLatestRelevantDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RateHelper, QuantLib::RateHelper)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->latestRelevantDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperLatestRelevantDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RateHelperLatestRelevantDateWorker* worker = new RateHelperLatestRelevantDateWorker(
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

void RateHelperPillarDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RateHelper, QuantLib::RateHelper)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->pillarDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperPillarDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RateHelperPillarDateWorker* worker = new RateHelperPillarDateWorker(
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

void RateHelperMaturityDateWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RateHelper, QuantLib::RateHelper)


  // invoke the member function
  QuantLib::Date returnValue = ObjectIDLibObjPtr->maturityDate(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperMaturityDate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RateHelperMaturityDateWorker* worker = new RateHelperMaturityDateWorker(
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

void RateHelperQuoteNameWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_OBJECT(ObjectIDObjPtr, mObjectID, QuantLibAddin::RateHelper)


  // invoke the member function
  mReturnValue = ObjectIDObjPtr->quoteName(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperQuoteName) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RateHelperQuoteNameWorker* worker = new RateHelperQuoteNameWorker(
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

void RateHelperQuoteValueWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RateHelper, QuantLib::RateHelper)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->quote()->value(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperQuoteValue) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RateHelperQuoteValueWorker* worker = new RateHelperQuoteValueWorker(
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

void RateHelperQuoteIsValidWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RateHelper, QuantLib::RateHelper)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->quote()->isValid(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperQuoteIsValid) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RateHelperQuoteIsValidWorker* worker = new RateHelperQuoteIsValidWorker(
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

void RateHelperImpliedQuoteWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RateHelper, QuantLib::RateHelper)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->impliedQuote(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperImpliedQuote) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RateHelperImpliedQuoteWorker* worker = new RateHelperImpliedQuoteWorker(
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

void RateHelperQuoteErrorWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::RateHelper, QuantLib::RateHelper)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->quoteError(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperQuoteError) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  RateHelperQuoteErrorWorker* worker = new RateHelperQuoteErrorWorker(
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

void SwapRateHelperSpreadWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::SwapRateHelper, QuantLib::SwapRateHelper)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->spread(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SwapRateHelperSpread) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  SwapRateHelperSpreadWorker* worker = new SwapRateHelperSpreadWorker(
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

void SwapRateHelperForwardStartWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::SwapRateHelper, QuantLib::SwapRateHelper)


  // invoke the member function
  QuantLib::Period returnValue = ObjectIDLibObjPtr->forwardStart(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::SwapRateHelperForwardStart) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  SwapRateHelperForwardStartWorker* worker = new SwapRateHelperForwardStartWorker(
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

void FuturesRateHelperConvexityAdjustmentWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FuturesRateHelper, QuantLib::FuturesRateHelper)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->convexityAdjustment(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FuturesRateHelperConvexityAdjustment) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FuturesRateHelperConvexityAdjustmentWorker* worker = new FuturesRateHelperConvexityAdjustmentWorker(
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

void FxSwapRateHelperSpotValueWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FxSwapRateHelper, QuantLib::FxSwapRateHelper)


  // invoke the member function
  QuantLib::Real returnValue = ObjectIDLibObjPtr->spot(
      );


  mReturnValue = returnValue;

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FxSwapRateHelperSpotValue) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FxSwapRateHelperSpotValueWorker* worker = new FxSwapRateHelperSpotValueWorker(
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

void FxSwapRateHelperTenorWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FxSwapRateHelper, QuantLib::FxSwapRateHelper)


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

NAN_METHOD(QuantLibXL::FxSwapRateHelperTenor) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FxSwapRateHelperTenorWorker* worker = new FxSwapRateHelperTenorWorker(
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

void FxSwapRateHelperFixingDaysWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FxSwapRateHelper, QuantLib::FxSwapRateHelper)


  // invoke the member function
  QuantLib::Natural returnValue = ObjectIDLibObjPtr->fixingDays(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FxSwapRateHelperFixingDays) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FxSwapRateHelperFixingDaysWorker* worker = new FxSwapRateHelperFixingDaysWorker(
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

void FxSwapRateHelperCalendarWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FxSwapRateHelper, QuantLib::FxSwapRateHelper)


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

NAN_METHOD(QuantLibXL::FxSwapRateHelperCalendar) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FxSwapRateHelperCalendarWorker* worker = new FxSwapRateHelperCalendarWorker(
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

void FxSwapRateHelperBDCWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FxSwapRateHelper, QuantLib::FxSwapRateHelper)


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

NAN_METHOD(QuantLibXL::FxSwapRateHelperBDC) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FxSwapRateHelperBDCWorker* worker = new FxSwapRateHelperBDCWorker(
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

void FxSwapRateHelperEOMWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FxSwapRateHelper, QuantLib::FxSwapRateHelper)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->endOfMonth(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FxSwapRateHelperEOM) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FxSwapRateHelperEOMWorker* worker = new FxSwapRateHelperEOMWorker(
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

void FxSwapRateHelperIsBaseCurrencyCollateralCurrencyWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::FxSwapRateHelper, QuantLib::FxSwapRateHelper)


  // invoke the member function
  mReturnValue = ObjectIDLibObjPtr->isFxBaseCurrencyCollateralCurrency(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::FxSwapRateHelperIsBaseCurrencyCollateralCurrency) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  FxSwapRateHelperIsBaseCurrencyCollateralCurrencyWorker* worker = new FxSwapRateHelperIsBaseCurrencyCollateralCurrencyWorker(
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

void RateHelperSelectionWorker::Execute(){

  try{

  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLibAddin::RateHelper> > RateHelpersObjPtr =
      ObjectHandler::getObjectVector<QuantLibAddin::RateHelper>(mRateHelpers);


  // convert input datatypes to QuantLib datatypes
  std::vector<long> PriorityCpp;
  std::vector<QuantLib::Natural> PriorityLib =
      QuantLibAddin::convertVector<long, QuantLib::Natural>(PriorityCpp);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural NImmFuturesLib = ObjectHandler::convert2<long>(
      mNImmFutures, "NImmFutures", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural NSerialFuturesLib = ObjectHandler::convert2<long>(
      mNSerialFutures, "NSerialFutures", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib datatypes
  QuantLib::Natural FutureRollDaysLib = ObjectHandler::convert2<long>(
      mFutureRollDays, "FutureRollDays", QuantLib::Null<QuantLib::Natural>());


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLibAddin::RateHelper::DepoInclusionCriteria DepoInclusionEnum =
      ObjectHandler::Create<QuantLibAddin::RateHelper::DepoInclusionCriteria>()(mDepoInclusion);


  // convert input datatypes to QuantLib datatypes
  std::vector<long> MinDistanceCpp;
  std::vector<QuantLib::Natural> MinDistanceLib =
      QuantLibAddin::convertVector<long, QuantLib::Natural>(MinDistanceCpp);

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlRateHelperSelection(
      RateHelpersObjPtr
      ,
       PriorityLib
      ,
       NImmFuturesLib
      ,
       NSerialFuturesLib
      ,
       FutureRollDaysLib
      ,
       DepoInclusionEnum
      ,
       MinDistanceLib
   );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperSelection) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("RateHelpers is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("Priority is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("DepoInclusion is required.");
  }
  if (info.Length() == 6 || !info[6]->IsArray()) {
      return Nan::ThrowError("MinDistance is required.");
  }
  // convert js argument to c++ type
  std::vector<string>RateHelpersCpp;

  Local<Array> RateHelpersArray = info[0].As<Array>();
  for (unsigned int i = 0; i < RateHelpersArray->Length(); i++){
    String::Utf8Value strRateHelpers(Nan::Get(RateHelpersArray, i).ToLocalChecked()->ToString());
    RateHelpersCpp.push_back(strdup(*strRateHelpers));
  }

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>PriorityCpp;

  Local<Array> PriorityArray = info[1].As<Array>();
  for (unsigned int i = 0; i < PriorityArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(PriorityArray, i).ToLocalChecked()).FromJust()));
    PriorityCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  ObjectHandler::property_t NImmFuturesCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t NSerialFuturesCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t FutureRollDaysCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[4]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strDepoInclusion(info[5]->ToString());
  string DepoInclusionCpp(strdup(*strDepoInclusion));

  // convert js argument to c++ type
  std::vector<ObjectHandler::property_t>MinDistanceCpp;

  Local<Array> MinDistanceArray = info[6].As<Array>();
  for (unsigned int i = 0; i < MinDistanceArray->Length(); i++){
    ObjectHandler::property_t tmp =
        ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(Nan::Get(MinDistanceArray, i).ToLocalChecked()).FromJust()));
    MinDistanceCpp.push_back(tmp);
  }

 
  // launch worker
  RateHelperSelectionWorker* worker = new RateHelperSelectionWorker(
    RateHelpersCpp
,     PriorityCpp
,     NImmFuturesCpp
,     NSerialFuturesCpp
,     FutureRollDaysCpp
,     DepoInclusionCpp
,     MinDistanceCpp
   );

  worker->Execute();

    Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Nan::Set(tmpArray,i,Nan::New<String>(worker->mReturnValue[i]).ToLocalChecked());
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

void RateHelperRateWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_OBJECT(RateHelperObjPtr, mRateHelper, QuantLibAddin::RateHelper)

       // invoke the utility function
  mReturnValue = QuantLibAddin::qlRateHelperRate(
      RateHelperObjPtr
     );
   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::RateHelperRate) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("RateHelper is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strRateHelper(info[0]->ToString());
  string RateHelperCpp(strdup(*strRateHelper));

 
  // launch worker
  RateHelperRateWorker* worker = new RateHelperRateWorker(
    RateHelperCpp
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
 