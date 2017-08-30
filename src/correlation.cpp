/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#include <nan.h>
#include <string.h>

#include "correlation.hpp"

#include <qlo/qladdindefines.hpp>
#include <qlo/sequencestatistics.hpp>
#include <qlo/correlation.hpp>
#include <qlo/curvestate.hpp>
#include <qlo/evolutiondescription.hpp>
#include <qlo/indexes/iborindex.hpp>
#include <qlo/indexes/swapindex.hpp>
#include <ql/models/marketmodels/correlations/expcorrelations.hpp>
#include <ql/models/marketmodels/historicalforwardratesanalysis.hpp>
#include <ql/models/marketmodels/historicalratesanalysis.hpp>
 #include <oh/objecthandler.hpp>
#include <oh/conversions/getobjectvector.hpp>
#include <qlo/valueobjects/vo_all.hpp>
#include <qlo/conversions/all.hpp>
#include "../loop.hpp"


void MarketModelLmLinearExponentialCorrelationModelWorker::Execute(){

  try{
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlMarketModelLmLinearExponentialCorrelationModel(
          mObjectID,
          mSize,
          mRho,
          mBeta,
          mFactors,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::LmLinearExponentialCorrelationModel(
          valueObject,
          mSize,
          mRho,
          mBeta,
          mFactors,
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

NAN_METHOD(QuantLibXL::MarketModelLmLinearExponentialCorrelationModel) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("Size is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Rho is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Beta is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Factors is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long SizeCpp = Nan::To<int32_t>(info[1]).FromJust();

  // convert js argument to c++ type
  double RhoCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double BetaCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  long FactorsCpp = Nan::To<int32_t>(info[4]).FromJust();

 
  // launch worker
  MarketModelLmLinearExponentialCorrelationModelWorker* worker = new MarketModelLmLinearExponentialCorrelationModelWorker(
    ObjectIDCpp
,     SizeCpp
,     RhoCpp
,     BetaCpp
,     FactorsCpp
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

void HistoricalForwardRatesAnalysisWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(SequenceStatsLibObjPtr, mSequenceStats,
      QuantLibAddin::SequenceStatistics, QuantLib::SequenceStatistics)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEndDate, "EndDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period StepLib;
  QuantLibAddin::cppToLibrary(mStep, StepLib);


  // convert object IDs into library objects
  OH_GET_REFERENCE(IborIndexLibObjPtr, mIborIndex,
      QuantLibAddin::IborIndex, QuantLib::IborIndex)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period InitialGapLib;
  QuantLibAddin::cppToLibrary(mInitialGap, InitialGapLib);


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period HorizonLib;
  QuantLibAddin::cppToLibrary(mHorizon, HorizonLib);


  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLib::IborIndex> > IborIndexesLibObjPtr =
      ObjectHandler::getLibraryObjectVector<QuantLibAddin::IborIndex, QuantLib::IborIndex>(mIborIndexes);


  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLib::SwapIndex> > SwapIndexesLibObjPtr =
      ObjectHandler::getLibraryObjectVector<QuantLibAddin::SwapIndex, QuantLib::SwapIndex>(mSwapIndexes);


  // convert input datatypes to QuantLib enumerated datatypes
  QuantLib::DayCounter DayCounterEnum =
      ObjectHandler::Create<QuantLib::DayCounter>()(mDayCounter);


  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlHistoricalForwardRatesAnalysis(
          mObjectID,
          mSequenceStats,
          mStartDate,
          mEndDate,
          mStep,
          mIborIndex,
          mInitialGap,
          mHorizon,
          mIborIndexes,
          mSwapIndexes,
          mDayCounter,
          mTraitsID,
          mInterpolatorID,
          mBootstrapAccuracy,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::HistoricalForwardRatesAnalysis(
          valueObject,
          SequenceStatsLibObjPtr,
          StartDateLib,
          EndDateLib,
          StepLib,
          IborIndexLibObjPtr,
          InitialGapLib,
          HorizonLib,
          IborIndexesLibObjPtr,
          SwapIndexesLibObjPtr,
          DayCounterEnum,
          mTraitsID,
          mInterpolatorID,
          mBootstrapAccuracy,
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

NAN_METHOD(QuantLibXL::HistoricalForwardRatesAnalysis) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("SequenceStats is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Step is required.");
  }
  if (info.Length() == 5 || !info[5]->IsString()) {
      return Nan::ThrowError("IborIndex is required.");
  }
  if (info.Length() == 6 || !info[6]->IsString()) {
      return Nan::ThrowError("InitialGap is required.");
  }
  if (info.Length() == 7 || !info[7]->IsString()) {
      return Nan::ThrowError("Horizon is required.");
  }
  if (info.Length() == 8 || !info[8]->IsArray()) {
      return Nan::ThrowError("IborIndexes is required.");
  }
  if (info.Length() == 9 || !info[9]->IsArray()) {
      return Nan::ThrowError("SwapIndexes is required.");
  }
  if (info.Length() == 10 || !info[10]->IsString()) {
      return Nan::ThrowError("DayCounter is required.");
  }
  if (info.Length() == 11 || !info[11]->IsString()) {
      return Nan::ThrowError("TraitsID is required.");
  }
  if (info.Length() == 12 || !info[12]->IsString()) {
      return Nan::ThrowError("InterpolatorID is required.");
  }
  if (info.Length() == 13 || !info[13]->IsNumber()) {
      return Nan::ThrowError("BootstrapAccuracy is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strSequenceStats(info[1]->ToString());
  string SequenceStatsCpp(strdup(*strSequenceStats));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t EndDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strStep(info[4]->ToString());
  string StepCpp(strdup(*strStep));

  // convert js argument to c++ type
  String::Utf8Value strIborIndex(info[5]->ToString());
  string IborIndexCpp(strdup(*strIborIndex));

  // convert js argument to c++ type
  String::Utf8Value strInitialGap(info[6]->ToString());
  string InitialGapCpp(strdup(*strInitialGap));

  // convert js argument to c++ type
  String::Utf8Value strHorizon(info[7]->ToString());
  string HorizonCpp(strdup(*strHorizon));

  // convert js argument to c++ type
  std::vector<string>IborIndexesCpp;

  Local<Array> IborIndexesArray = info[8].As<Array>();
  for (unsigned int i = 0; i < IborIndexesArray->Length(); i++){
    String::Utf8Value strIborIndexes(Nan::Get(IborIndexesArray, i).ToLocalChecked()->ToString());
    IborIndexesCpp.push_back(strdup(*strIborIndexes));
  }

  // convert js argument to c++ type
  std::vector<string>SwapIndexesCpp;

  Local<Array> SwapIndexesArray = info[9].As<Array>();
  for (unsigned int i = 0; i < SwapIndexesArray->Length(); i++){
    String::Utf8Value strSwapIndexes(Nan::Get(SwapIndexesArray, i).ToLocalChecked()->ToString());
    SwapIndexesCpp.push_back(strdup(*strSwapIndexes));
  }

  // convert js argument to c++ type
  String::Utf8Value strDayCounter(info[10]->ToString());
  string DayCounterCpp(strdup(*strDayCounter));

  // convert js argument to c++ type
  String::Utf8Value strTraitsID(info[11]->ToString());
  string TraitsIDCpp(strdup(*strTraitsID));

  // convert js argument to c++ type
  String::Utf8Value strInterpolatorID(info[12]->ToString());
  string InterpolatorIDCpp(strdup(*strInterpolatorID));

  // convert js argument to c++ type
  double BootstrapAccuracyCpp = Nan::To<double>(info[13]).FromJust();

 
  // launch worker
  HistoricalForwardRatesAnalysisWorker* worker = new HistoricalForwardRatesAnalysisWorker(
    ObjectIDCpp
,     SequenceStatsCpp
,     StartDateCpp
,     EndDateCpp
,     StepCpp
,     IborIndexCpp
,     InitialGapCpp
,     HorizonCpp
,     IborIndexesCpp
,     SwapIndexesCpp
,     DayCounterCpp
,     TraitsIDCpp
,     InterpolatorIDCpp
,     BootstrapAccuracyCpp
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

void HistoricalRatesAnalysisWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(SequenceStatsLibObjPtr, mSequenceStats,
      QuantLibAddin::SequenceStatistics, QuantLib::SequenceStatistics)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date StartDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mStartDate, "StartDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Date EndDateLib = ObjectHandler::convert2<QuantLib::Date>(
      mEndDate, "EndDate");


  // convert input datatypes to QuantLib datatypes
  QuantLib::Period StepLib;
  QuantLibAddin::cppToLibrary(mStep, StepLib);


  // convert object IDs into library objects
  std::vector< boost::shared_ptr<QuantLib::InterestRateIndex> > InterestRateIndexesLibObjPtr =
      ObjectHandler::getLibraryObjectVector<QuantLibAddin::InterestRateIndex, QuantLib::InterestRateIndex>(mInterestRateIndexes);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlHistoricalRatesAnalysis(
          mObjectID,
          mSequenceStats,
          mStartDate,
          mEndDate,
          mStep,
          mInterestRateIndexes,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::HistoricalRatesAnalysis(
          valueObject,
          SequenceStatsLibObjPtr,
          StartDateLib,
          EndDateLib,
          StepLib,
          InterestRateIndexesLibObjPtr,
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

NAN_METHOD(QuantLibXL::HistoricalRatesAnalysis) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("SequenceStats is required.");
  }
  if (info.Length() == 4 || !info[4]->IsString()) {
      return Nan::ThrowError("Step is required.");
  }
  if (info.Length() == 5 || !info[5]->IsArray()) {
      return Nan::ThrowError("InterestRateIndexes is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strSequenceStats(info[1]->ToString());
  string SequenceStatsCpp(strdup(*strSequenceStats));

  // convert js argument to c++ type
  ObjectHandler::property_t StartDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[2]).FromJust()));

  // convert js argument to c++ type
  ObjectHandler::property_t EndDateCpp =
      ObjectHandler::property_t(static_cast<long>(Nan::To<int32_t>(info[3]).FromJust()));

  // convert js argument to c++ type
  String::Utf8Value strStep(info[4]->ToString());
  string StepCpp(strdup(*strStep));

  // convert js argument to c++ type
  std::vector<string>InterestRateIndexesCpp;

  Local<Array> InterestRateIndexesArray = info[5].As<Array>();
  for (unsigned int i = 0; i < InterestRateIndexesArray->Length(); i++){
    String::Utf8Value strInterestRateIndexes(Nan::Get(InterestRateIndexesArray, i).ToLocalChecked()->ToString());
    InterestRateIndexesCpp.push_back(strdup(*strInterestRateIndexes));
  }

 
  // launch worker
  HistoricalRatesAnalysisWorker* worker = new HistoricalRatesAnalysisWorker(
    ObjectIDCpp
,     SequenceStatsCpp
,     StartDateCpp
,     EndDateCpp
,     StepCpp
,     InterestRateIndexesCpp
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

void TimeHomogeneousForwardCorrelationWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes
  QuantLib::Matrix FwdCorrMatrixLib = QuantLibAddin::vvToQlMatrix(mFwdCorrMatrix);

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlTimeHomogeneousForwardCorrelation(
          mObjectID,
          mFwdCorrMatrix,
          mRateTimes,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::TimeHomogeneousForwardCorrelation(
          valueObject,
          FwdCorrMatrixLib,
          mRateTimes,
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

NAN_METHOD(QuantLibXL::TimeHomogeneousForwardCorrelation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("FwdCorrMatrix is required.");
  }
  if (info.Length() == 2 || !info[2]->IsArray()) {
      return Nan::ThrowError("RateTimes is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector< std::vector<double> >FwdCorrMatrixCpp;

  Local<Array> FwdCorrMatrixMatrix = info[1].As<Array>();
  for (unsigned int i = 0; i < FwdCorrMatrixMatrix->Length(); i++){
	  Local<Array> FwdCorrMatrixArray = FwdCorrMatrixMatrix->Get(i).As<Array>();
	  std::vector<double> tmp;
	  for (unsigned int j = 0; j < FwdCorrMatrixArray->Length(); j++){
		  tmp.push_back(Nan::To<double>(Nan::Get(FwdCorrMatrixArray, j).ToLocalChecked()).FromJust());
	  }
	  FwdCorrMatrixCpp.push_back(tmp);
  }

  // convert js argument to c++ type
  std::vector<double>RateTimesCpp;

  Local<Array> RateTimesArray = info[2].As<Array>();
  for (unsigned int i = 0; i < RateTimesArray->Length(); i++){
    RateTimesCpp.push_back(Nan::To<double>(Nan::Get(RateTimesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  TimeHomogeneousForwardCorrelationWorker* worker = new TimeHomogeneousForwardCorrelationWorker(
    ObjectIDCpp
,     FwdCorrMatrixCpp
,     RateTimesCpp
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

void ExponentialForwardCorrelationWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlExponentialForwardCorrelation(
          mObjectID,
          mRateTimes,
          mLongTermCorr,
          mBeta,
          mGamma,
          mTimes,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::ExponentialForwardCorrelation(
          valueObject,
          mRateTimes,
          mLongTermCorr,
          mBeta,
          mGamma,
          mTimes,
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

NAN_METHOD(QuantLibXL::ExponentialForwardCorrelation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsArray()) {
      return Nan::ThrowError("RateTimes is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("LongTermCorr is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Beta is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Gamma is required.");
  }
  if (info.Length() == 5 || !info[5]->IsArray()) {
      return Nan::ThrowError("Times is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  std::vector<double>RateTimesCpp;

  Local<Array> RateTimesArray = info[1].As<Array>();
  for (unsigned int i = 0; i < RateTimesArray->Length(); i++){
    RateTimesCpp.push_back(Nan::To<double>(Nan::Get(RateTimesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double LongTermCorrCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double BetaCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double GammaCpp = Nan::To<double>(info[4]).FromJust();

  // convert js argument to c++ type
  std::vector<double>TimesCpp;

  Local<Array> TimesArray = info[5].As<Array>();
  for (unsigned int i = 0; i < TimesArray->Length(); i++){
    TimesCpp.push_back(Nan::To<double>(Nan::Get(TimesArray, i).ToLocalChecked()).FromJust());
  }

 
  // launch worker
  ExponentialForwardCorrelationWorker* worker = new ExponentialForwardCorrelationWorker(
    ObjectIDCpp
,     RateTimesCpp
,     LongTermCorrCpp
,     BetaCpp
,     GammaCpp
,     TimesCpp
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

void CotSwapFromFwdCorrelationWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(FwdCorrLibObjPtr, mFwdCorr,
      QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)


  // convert object IDs into library objects
  OH_GET_UNDERLYING(CurveStateLibObj, mCurveState,
      QuantLibAddin::CurveState, QuantLib::CurveState)

 
    // Construct the Value Object
    boost::shared_ptr<ObjectHandler::ValueObject> valueObject(
      new QuantLibAddin::ValueObjects::qlCotSwapFromFwdCorrelation(
          mObjectID,
          mFwdCorr,
          mCurveState,
          mDisplacement,
          false
      ));

    // Construct the Object
    boost::shared_ptr<ObjectHandler::Object> object(
      new QuantLibAddin::CotSwapFromFwdCorrelation(
          valueObject,
          FwdCorrLibObjPtr,
          CurveStateLibObj,
          mDisplacement,
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

NAN_METHOD(QuantLibXL::CotSwapFromFwdCorrelation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsString()) {
      return Nan::ThrowError("FwdCorr is required.");
  }
  if (info.Length() == 2 || !info[2]->IsString()) {
      return Nan::ThrowError("CurveState is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Displacement is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  String::Utf8Value strFwdCorr(info[1]->ToString());
  string FwdCorrCpp(strdup(*strFwdCorr));

  // convert js argument to c++ type
  String::Utf8Value strCurveState(info[2]->ToString());
  string CurveStateCpp(strdup(*strCurveState));

  // convert js argument to c++ type
  double DisplacementCpp = Nan::To<double>(info[3]).FromJust();

 
  // launch worker
  CotSwapFromFwdCorrelationWorker* worker = new CotSwapFromFwdCorrelationWorker(
    ObjectIDCpp
,     FwdCorrCpp
,     CurveStateCpp
,     DisplacementCpp
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

void HistoricalForwardRatesAnalysisSkippedDatesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::HistoricalForwardRatesAnalysis, QuantLib::HistoricalForwardRatesAnalysis)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDLibObjPtr->skippedDates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::HistoricalForwardRatesAnalysisSkippedDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  HistoricalForwardRatesAnalysisSkippedDatesWorker* worker = new HistoricalForwardRatesAnalysisSkippedDatesWorker(
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

void HistoricalForwardRatesAnalysisSkippedDatesErrorMessageWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::HistoricalForwardRatesAnalysis, QuantLib::HistoricalForwardRatesAnalysis)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->skippedDatesErrorMessage(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::HistoricalForwardRatesAnalysisSkippedDatesErrorMessage) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  HistoricalForwardRatesAnalysisSkippedDatesErrorMessageWorker* worker = new HistoricalForwardRatesAnalysisSkippedDatesErrorMessageWorker(
    ObjectIDCpp
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

void HistoricalForwardRatesAnalysisFailedDatesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::HistoricalForwardRatesAnalysis, QuantLib::HistoricalForwardRatesAnalysis)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDLibObjPtr->failedDates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::HistoricalForwardRatesAnalysisFailedDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  HistoricalForwardRatesAnalysisFailedDatesWorker* worker = new HistoricalForwardRatesAnalysisFailedDatesWorker(
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

void HistoricalForwardRatesAnalysisFailedDatesErrorMessageWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::HistoricalForwardRatesAnalysis, QuantLib::HistoricalForwardRatesAnalysis)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->failedDatesErrorMessage(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::HistoricalForwardRatesAnalysisFailedDatesErrorMessage) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  HistoricalForwardRatesAnalysisFailedDatesErrorMessageWorker* worker = new HistoricalForwardRatesAnalysisFailedDatesErrorMessageWorker(
    ObjectIDCpp
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

void HistoricalForwardRatesAnalysisFixingPeriodsWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::HistoricalForwardRatesAnalysis, QuantLib::HistoricalForwardRatesAnalysis)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Period> returnValue = ObjectIDLibObjPtr->fixingPeriods(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::HistoricalForwardRatesAnalysisFixingPeriods) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  HistoricalForwardRatesAnalysisFixingPeriodsWorker* worker = new HistoricalForwardRatesAnalysisFixingPeriodsWorker(
    ObjectIDCpp
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

void HistoricalRatesAnalysisSkippedDatesWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::HistoricalRatesAnalysis, QuantLib::HistoricalRatesAnalysis)


  // loop on the input parameter and populate the return vector
  std::vector<QuantLib::Date> returnValue = ObjectIDLibObjPtr->skippedDates(
      );


  mReturnValue = QuantLibAddin::libraryToVector(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::HistoricalRatesAnalysisSkippedDates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  HistoricalRatesAnalysisSkippedDatesWorker* worker = new HistoricalRatesAnalysisSkippedDatesWorker(
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

void HistoricalRatesAnalysisSkippedDatesErrorMessageWorker::Execute(){

  try{
       // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::HistoricalRatesAnalysis, QuantLib::HistoricalRatesAnalysis)


  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->skippedDatesErrorMessage(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::HistoricalRatesAnalysisSkippedDatesErrorMessage) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  HistoricalRatesAnalysisSkippedDatesErrorMessageWorker* worker = new HistoricalRatesAnalysisSkippedDatesErrorMessageWorker(
    ObjectIDCpp
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

void PiecewiseConstantCorrelationCorrelationWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)


  // convert input datatypes to QuantLib datatypes
  QuantLib::Size TimeIndexLib;
  QuantLibAddin::cppToLibrary(mTimeIndex, TimeIndexLib);

       QuantLib::Matrix returnValue;


  // invoke the member function
  returnValue = ObjectIDLibObjPtr->correlation(
        TimeIndexLib
       );


  mReturnValue = QuantLibAddin::qlMatrixToVv(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PiecewiseConstantCorrelationCorrelation) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("TimeIndex is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

  // convert js argument to c++ type
  long TimeIndexCpp = Nan::To<int32_t>(info[1]).FromJust();

 
  // launch worker
  PiecewiseConstantCorrelationCorrelationWorker* worker = new PiecewiseConstantCorrelationCorrelationWorker(
    ObjectIDCpp
,     TimeIndexCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<Number>(worker->mReturnValue[i][j]));
      }
      Nan::Set(tmpMatrix,i,tmpArray);
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpMatrix
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}

void PiecewiseConstantCorrelationTimesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

     
  // loop on the input parameter and populate the return vector
  mReturnValue = ObjectIDLibObjPtr->times(
      );

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PiecewiseConstantCorrelationTimes) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  PiecewiseConstantCorrelationTimesWorker* worker = new PiecewiseConstantCorrelationTimesWorker(
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

void PiecewiseConstantCorrelationNumberOfRatesWorker::Execute(){

  try{

  // convert object IDs into library objects
  OH_GET_REFERENCE(ObjectIDLibObjPtr, mObjectID,
      QuantLibAddin::PiecewiseConstantCorrelation, QuantLib::PiecewiseConstantCorrelation)

     
  // invoke the member function
  QuantLib::Size returnValue = ObjectIDLibObjPtr->numberOfRates(
      );


  mReturnValue = QuantLibAddin::libraryToScalar(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::PiecewiseConstantCorrelationNumberOfRates) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsString()) {
      return Nan::ThrowError("ObjectID is required.");
  }
  // convert js argument to c++ type
  String::Utf8Value strObjectID(info[0]->ToString());
  string ObjectIDCpp(strdup(*strObjectID));

 
  // launch worker
  PiecewiseConstantCorrelationNumberOfRatesWorker* worker = new PiecewiseConstantCorrelationNumberOfRatesWorker(
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

void ExponentialCorrelationsWorker::Execute(){

  try{

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes

  // convert input datatypes to QuantLib datatypes
       QuantLib::Matrix returnValue;


  // invoke the utility function
  returnValue = QuantLib::exponentialCorrelations(
        mRateTimes
       ,
         mLongTermCorr
       ,
         mBeta
       ,
         mGamma
       ,
         mTime
       );


  mReturnValue = QuantLibAddin::qlMatrixToVv(returnValue);

   }catch(const std::exception &e){
    mError = e.what();
  }catch (...){
    mError = "unkown error";
  }

}

NAN_METHOD(QuantLibXL::ExponentialCorrelations) {

  // validate js arguments
  if (info.Length() == 0 || !info[0]->IsArray()) {
      return Nan::ThrowError("RateTimes is required.");
  }
  if (info.Length() == 1 || !info[1]->IsNumber()) {
      return Nan::ThrowError("LongTermCorr is required.");
  }
  if (info.Length() == 2 || !info[2]->IsNumber()) {
      return Nan::ThrowError("Beta is required.");
  }
  if (info.Length() == 3 || !info[3]->IsNumber()) {
      return Nan::ThrowError("Gamma is required.");
  }
  if (info.Length() == 4 || !info[4]->IsNumber()) {
      return Nan::ThrowError("Time is required.");
  }
  // convert js argument to c++ type
  std::vector<double>RateTimesCpp;

  Local<Array> RateTimesArray = info[0].As<Array>();
  for (unsigned int i = 0; i < RateTimesArray->Length(); i++){
    RateTimesCpp.push_back(Nan::To<double>(Nan::Get(RateTimesArray, i).ToLocalChecked()).FromJust());
  }

  // convert js argument to c++ type
  double LongTermCorrCpp = Nan::To<double>(info[1]).FromJust();

  // convert js argument to c++ type
  double BetaCpp = Nan::To<double>(info[2]).FromJust();

  // convert js argument to c++ type
  double GammaCpp = Nan::To<double>(info[3]).FromJust();

  // convert js argument to c++ type
  double TimeCpp = Nan::To<double>(info[4]).FromJust();

 
  // launch worker
  ExponentialCorrelationsWorker* worker = new ExponentialCorrelationsWorker(
    RateTimesCpp
,     LongTermCorrCpp
,     BetaCpp
,     GammaCpp
,     TimeCpp
   );

  worker->Execute();

    Local<Array> tmpMatrix = Nan::New<Array>(worker->mReturnValue.size());
    for (unsigned int i = 0; i < worker->mReturnValue.size(); i++) {
      Local<Array> tmpArray = Nan::New<Array>(worker->mReturnValue[i].size());
      for (unsigned int j = 0; j < worker->mReturnValue[i].size(); j++) {
        Nan::Set(tmpArray,j,Nan::New<Number>(worker->mReturnValue[i][j]));
      }
      Nan::Set(tmpMatrix,i,tmpArray);
    }

  Local<v8::Value> argv[2] = {
		  Nan::New<String>(worker->mError).ToLocalChecked(),
      tmpMatrix
	};

  v8::Local<v8::Array> results = Nan::New<v8::Array>();
  Nan::Set(results, 0, argv[0]);
  Nan::Set(results, 1, argv[1]);
  info.GetReturnValue().Set(results);
}
 