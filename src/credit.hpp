/* 
  Copyright (C) 2016 -2017 Jerry Jin
*/

#ifndef credit_h
#define credit_h
#include <nan.h>
#include <string>
#include <queue>
#include <utility>

#include "../quantlibxl.hpp"

#include <oh/objecthandler.hpp>

using namespace node;
using namespace v8;
using namespace std;


class CreditDefaultSwapWorker {
  public:
    string mObjectID;
    string mBuyerSeller;
    double mNotional;
    double mUpfront;
    double mSpread;
    string mPremiumSchedule;
    string mPaymentConvention;
    string mDayCounter;
    bool mSettlesAccrual;
    bool mPayAtDefault;
    ObjectHandler::property_t mProtectionStart;
    ObjectHandler::property_t mUpfrontDate;

    string mReturnValue;

    string mError;

    CreditDefaultSwapWorker(
      string ObjectID
,       string BuyerSeller
,       double Notional
,       double Upfront
,       double Spread
,       string PremiumSchedule
,       string PaymentConvention
,       string DayCounter
,       bool SettlesAccrual
,       bool PayAtDefault
,       ObjectHandler::property_t ProtectionStart
,       ObjectHandler::property_t UpfrontDate
     )
      {
        mObjectID = ObjectID;
        mBuyerSeller = BuyerSeller;
        mNotional = Notional;
        mUpfront = Upfront;
        mSpread = Spread;
        mPremiumSchedule = PremiumSchedule;
        mPaymentConvention = PaymentConvention;
        mDayCounter = DayCounter;
        mSettlesAccrual = SettlesAccrual;
        mPayAtDefault = PayAtDefault;
        mProtectionStart = ProtectionStart;
        mUpfrontDate = UpfrontDate;
      };

    void Execute();
};

class MidPointCdsEngineWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mDefaultCurve;
    double mRecoveryRate;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    MidPointCdsEngineWorker(
      string ObjectID
,       ObjectHandler::property_t DefaultCurve
,       double RecoveryRate
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mDefaultCurve = DefaultCurve;
        mRecoveryRate = RecoveryRate;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class HazardRateCurveWorker {
  public:
    string mObjectID;
    std::vector<ObjectHandler::property_t> mCurveDates;
    std::vector<double> mCurveRates;
    string mDayCounter;

    string mReturnValue;

    string mError;

    HazardRateCurveWorker(
      string ObjectID
,       std::vector<ObjectHandler::property_t> CurveDates
,       std::vector<double> CurveRates
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mCurveDates = CurveDates;
        mCurveRates = CurveRates;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class SpreadCdsHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mRunningSpread;
    string mTenor;
    ObjectHandler::property_t mSettlementDays;
    string mCalendar;
    string mFrequency;
    string mPaymentConvention;
    string mGenRule;
    string mDayCounter;
    double mRecoveryRate;
    ObjectHandler::property_t mDiscountingCurve;
    bool mSettleAccrual;
    bool mPayAtDefault;

    string mReturnValue;

    string mError;

    SpreadCdsHelperWorker(
      string ObjectID
,       ObjectHandler::property_t RunningSpread
,       string Tenor
,       ObjectHandler::property_t SettlementDays
,       string Calendar
,       string Frequency
,       string PaymentConvention
,       string GenRule
,       string DayCounter
,       double RecoveryRate
,       ObjectHandler::property_t DiscountingCurve
,       bool SettleAccrual
,       bool PayAtDefault
     )
      {
        mObjectID = ObjectID;
        mRunningSpread = RunningSpread;
        mTenor = Tenor;
        mSettlementDays = SettlementDays;
        mCalendar = Calendar;
        mFrequency = Frequency;
        mPaymentConvention = PaymentConvention;
        mGenRule = GenRule;
        mDayCounter = DayCounter;
        mRecoveryRate = RecoveryRate;
        mDiscountingCurve = DiscountingCurve;
        mSettleAccrual = SettleAccrual;
        mPayAtDefault = PayAtDefault;
      };

    void Execute();
};

class UpfrontCdsHelperWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mUpfrontSpread;
    double mRunningSpread;
    string mTenor;
    ObjectHandler::property_t mSettlementDays;
    string mCalendar;
    string mFrequency;
    string mPaymentConvention;
    string mGenRule;
    string mDayCounter;
    double mRecRate;
    ObjectHandler::property_t mDiscCurve;
    ObjectHandler::property_t mUpfSettlDays;
    bool mSettlAccr;
    bool mPayAtDefault;

    string mReturnValue;

    string mError;

    UpfrontCdsHelperWorker(
      string ObjectID
,       ObjectHandler::property_t UpfrontSpread
,       double RunningSpread
,       string Tenor
,       ObjectHandler::property_t SettlementDays
,       string Calendar
,       string Frequency
,       string PaymentConvention
,       string GenRule
,       string DayCounter
,       double RecRate
,       ObjectHandler::property_t DiscCurve
,       ObjectHandler::property_t UpfSettlDays
,       bool SettlAccr
,       bool PayAtDefault
     )
      {
        mObjectID = ObjectID;
        mUpfrontSpread = UpfrontSpread;
        mRunningSpread = RunningSpread;
        mTenor = Tenor;
        mSettlementDays = SettlementDays;
        mCalendar = Calendar;
        mFrequency = Frequency;
        mPaymentConvention = PaymentConvention;
        mGenRule = GenRule;
        mDayCounter = DayCounter;
        mRecRate = RecRate;
        mDiscCurve = DiscCurve;
        mUpfSettlDays = UpfSettlDays;
        mSettlAccr = SettlAccr;
        mPayAtDefault = PayAtDefault;
      };

    void Execute();
};

class PiecewiseHazardRateCurveWorker {
  public:
    string mObjectID;
    std::vector<string> mHelpers;
    string mDayCounter;
    string mCalendar;
    string mInterpolation;
    double mAccuracy;

    string mReturnValue;

    string mError;

    PiecewiseHazardRateCurveWorker(
      string ObjectID
,       std::vector<string> Helpers
,       string DayCounter
,       string Calendar
,       string Interpolation
,       double Accuracy
     )
      {
        mObjectID = ObjectID;
        mHelpers = Helpers;
        mDayCounter = DayCounter;
        mCalendar = Calendar;
        mInterpolation = Interpolation;
        mAccuracy = Accuracy;
      };

    void Execute();
};

class PiecewiseFlatForwardCurveWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mReferenceDate;
    std::vector<string> mRateHelpers;
    string mDayCounter;
    double mAccuracy;

    string mReturnValue;

    string mError;

    PiecewiseFlatForwardCurveWorker(
      string ObjectID
,       ObjectHandler::property_t ReferenceDate
,       std::vector<string> RateHelpers
,       string DayCounter
,       double Accuracy
     )
      {
        mObjectID = ObjectID;
        mReferenceDate = ReferenceDate;
        mRateHelpers = RateHelpers;
        mDayCounter = DayCounter;
        mAccuracy = Accuracy;
      };

    void Execute();
};

class RiskyFixedBondWorker {
  public:
    string mObjectID;
    string mBondname;
    string mCurrency;
    double mRecovery;
    ObjectHandler::property_t mDefaultCurve;
    string mSchedule;
    double mRate;
    string mDayCounter;
    string mPaymentConvention;
    double mNotional;
    ObjectHandler::property_t mDiscountingCurve;
    ObjectHandler::property_t mPricingDate;

    string mReturnValue;

    string mError;

    RiskyFixedBondWorker(
      string ObjectID
,       string Bondname
,       string Currency
,       double Recovery
,       ObjectHandler::property_t DefaultCurve
,       string Schedule
,       double Rate
,       string DayCounter
,       string PaymentConvention
,       double Notional
,       ObjectHandler::property_t DiscountingCurve
,       ObjectHandler::property_t PricingDate
     )
      {
        mObjectID = ObjectID;
        mBondname = Bondname;
        mCurrency = Currency;
        mRecovery = Recovery;
        mDefaultCurve = DefaultCurve;
        mSchedule = Schedule;
        mRate = Rate;
        mDayCounter = DayCounter;
        mPaymentConvention = PaymentConvention;
        mNotional = Notional;
        mDiscountingCurve = DiscountingCurve;
        mPricingDate = PricingDate;
      };

    void Execute();
};

class IssuerWorker {
  public:
    string mObjectID;
    string mDefaultCurves;
    string mDefaultEvents;

    string mReturnValue;

    string mError;

    IssuerWorker(
      string ObjectID
,       string DefaultCurves
,       string DefaultEvents
     )
      {
        mObjectID = ObjectID;
        mDefaultCurves = DefaultCurves;
        mDefaultEvents = DefaultEvents;
      };

    void Execute();
};

class DefaultEventWorker {
  public:
    string mObjectID;
    string mEventType;
    ObjectHandler::property_t mEventDate;
    string mCurrency;
    string mSeniority;
    ObjectHandler::property_t mSettlementDate;
    double mSettledRecovery;

    string mReturnValue;

    string mError;

    DefaultEventWorker(
      string ObjectID
,       string EventType
,       ObjectHandler::property_t EventDate
,       string Currency
,       string Seniority
,       ObjectHandler::property_t SettlementDate
,       double SettledRecovery
     )
      {
        mObjectID = ObjectID;
        mEventType = EventType;
        mEventDate = EventDate;
        mCurrency = Currency;
        mSeniority = Seniority;
        mSettlementDate = SettlementDate;
        mSettledRecovery = SettledRecovery;
      };

    void Execute();
};

class SyntheticCDOWorker {
  public:
    string mObjectID;
    string mBasket;
    string mBuyerSeller;
    string mPremiumSchedule;
    double mUpfront;
    double mSpread;
    string mDayCounter;
    string mPaymentConvention;

    string mReturnValue;

    string mError;

    SyntheticCDOWorker(
      string ObjectID
,       string Basket
,       string BuyerSeller
,       string PremiumSchedule
,       double Upfront
,       double Spread
,       string DayCounter
,       string PaymentConvention
     )
      {
        mObjectID = ObjectID;
        mBasket = Basket;
        mBuyerSeller = BuyerSeller;
        mPremiumSchedule = PremiumSchedule;
        mUpfront = Upfront;
        mSpread = Spread;
        mDayCounter = DayCounter;
        mPaymentConvention = PaymentConvention;
      };

    void Execute();
};

class MidPointCDOEngineWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    MidPointCDOEngineWorker(
      string ObjectID
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class NthToDefaultWorker {
  public:
    string mObjectID;
    string mBasket;
    long mOrder;
    string mBuyerSeller;
    string mPremiumSchedule;
    double mUpfront;
    double mSpread;
    string mDayCounter;
    double mNotional;
    bool mSettlesAccrual;

    string mReturnValue;

    string mError;

    NthToDefaultWorker(
      string ObjectID
,       string Basket
,       long Order
,       string BuyerSeller
,       string PremiumSchedule
,       double Upfront
,       double Spread
,       string DayCounter
,       double Notional
,       bool SettlesAccrual
     )
      {
        mObjectID = ObjectID;
        mBasket = Basket;
        mOrder = Order;
        mBuyerSeller = BuyerSeller;
        mPremiumSchedule = PremiumSchedule;
        mUpfront = Upfront;
        mSpread = Spread;
        mDayCounter = DayCounter;
        mNotional = Notional;
        mSettlesAccrual = SettlesAccrual;
      };

    void Execute();
};

class IntegralNtdEngineWorker {
  public:
    string mObjectID;
    string mIntegrationStep;
    ObjectHandler::property_t mYieldCurve;

    string mReturnValue;

    string mError;

    IntegralNtdEngineWorker(
      string ObjectID
,       string IntegrationStep
,       ObjectHandler::property_t YieldCurve
     )
      {
        mObjectID = ObjectID;
        mIntegrationStep = IntegrationStep;
        mYieldCurve = YieldCurve;
      };

    void Execute();
};

class BlackCdsOptionEngineWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mDefaultCurve;
    double mRecoveryRate;
    ObjectHandler::property_t mYieldCurve;
    ObjectHandler::property_t mBlackVol;

    string mReturnValue;

    string mError;

    BlackCdsOptionEngineWorker(
      string ObjectID
,       ObjectHandler::property_t DefaultCurve
,       double RecoveryRate
,       ObjectHandler::property_t YieldCurve
,       ObjectHandler::property_t BlackVol
     )
      {
        mObjectID = ObjectID;
        mDefaultCurve = DefaultCurve;
        mRecoveryRate = RecoveryRate;
        mYieldCurve = YieldCurve;
        mBlackVol = BlackVol;
      };

    void Execute();
};

class CDSOptionWorker {
  public:
    string mObjectID;
    string mUnderlyingCDS;
    string mExercise;

    string mReturnValue;

    string mError;

    CDSOptionWorker(
      string ObjectID
,       string UnderlyingCDS
,       string Exercise
     )
      {
        mObjectID = ObjectID;
        mUnderlyingCDS = UnderlyingCDS;
        mExercise = Exercise;
      };

    void Execute();
};

class BaseCorrelationTermStructureWorker {
  public:
    string mObjectID;
    string mInterpolatorType;
    long mSettlementDays;
    string mCalendar;
    string mConvention;
    std::vector<ObjectHandler::property_t> mTenors;
    std::vector<double> mLossLevel;
    std::vector< std::vector<ObjectHandler::property_t> > mCorrelations;
    string mDayCounter;

    string mReturnValue;

    string mError;

    BaseCorrelationTermStructureWorker(
      string ObjectID
,       string InterpolatorType
,       long SettlementDays
,       string Calendar
,       string Convention
,       std::vector<ObjectHandler::property_t> Tenors
,       std::vector<double> LossLevel
,       std::vector< std::vector<ObjectHandler::property_t> > Correlations
,       string DayCounter
     )
      {
        mObjectID = ObjectID;
        mInterpolatorType = InterpolatorType;
        mSettlementDays = SettlementDays;
        mCalendar = Calendar;
        mConvention = Convention;
        mTenors = Tenors;
        mLossLevel = LossLevel;
        mCorrelations = Correlations;
        mDayCounter = DayCounter;
      };

    void Execute();
};

class CdsCouponLegNPVWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CdsCouponLegNPVWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CdsDefaultLegNPVWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CdsDefaultLegNPVWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CdsFairSpreadWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CdsFairSpreadWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CdsFairUpfrontWorker {
  public:
    string mObjectID;

    double mReturnValue;

    string mError;

    CdsFairUpfrontWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class HRDatesWorker {
  public:
    string mObjectID;

    std::vector<long> mReturnValue;

    string mError;

    HRDatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class HRatesWorker {
  public:
    string mObjectID;

    std::vector<double> mReturnValue;

    string mError;

    HRatesWorker(
      string ObjectID
     )
      {
        mObjectID = ObjectID;
      };

    void Execute();
};

class CdsOptionImpliedVolWorker {
  public:
    string mObjectID;
    double mPrice;
    ObjectHandler::property_t mYieldCurve;
    ObjectHandler::property_t mDefaultCurve;
    double mRecoveryRate;

    double mReturnValue;

    string mError;

    CdsOptionImpliedVolWorker(
      string ObjectID
,       double Price
,       ObjectHandler::property_t YieldCurve
,       ObjectHandler::property_t DefaultCurve
,       double RecoveryRate
     )
      {
        mObjectID = ObjectID;
        mPrice = Price;
        mYieldCurve = YieldCurve;
        mDefaultCurve = DefaultCurve;
        mRecoveryRate = RecoveryRate;
      };

    void Execute();
};

class BaseCorrelationValueWorker {
  public:
    string mObjectID;
    ObjectHandler::property_t mDate;
    double mLossLevel;

    double mReturnValue;

    string mError;

    BaseCorrelationValueWorker(
      string ObjectID
,       ObjectHandler::property_t Date
,       double LossLevel
     )
      {
        mObjectID = ObjectID;
        mDate = Date;
        mLossLevel = LossLevel;
      };

    void Execute();
};
 
#endif
