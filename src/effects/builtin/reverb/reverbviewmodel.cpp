#include "reverbviewmodel.h"

#include "global/translation.h"

#include "reverbeffect.h"

#include "log.h"

using namespace au::effects;

ReverbViewModel::ReverbViewModel()
{
}

ReverbEffect* ReverbViewModel::effect() const
{
    ReverbEffect* e = dynamic_cast<ReverbEffect*>(AbstractEffectModel::effect());
    IF_ASSERT_FAILED(e) {
        return nullptr;
    }
    return e;
}

const ReverbSettings& ReverbViewModel::settings() const
{
    return ReverbEffect::GetSettings(*AbstractEffectModel::settings());
}

ReverbSettings& ReverbViewModel::mutSettings()
{
    return ReverbEffect::GetSettings(*AbstractEffectModel::settings());
}

void ReverbViewModel::init()
{
    const ReverbSettings& rs = settings();

    auto makeItem = [this](const QString& key, const QString& title, double value, double min, double max, const Setter& s) {
        QVariantMap item;
        item["key"] = key;
        item["title"] = title;
        item["value"] = value;
        item["min"] = min;
        item["max"] = max;

        m_setters.insert(key, s);

        return item;
    };

    m_paramsList << makeItem("RoomSize",
                             muse::qtrc("effects", "Room Size (%)"),
                             rs.mRoomSize,
                             ReverbEffect::RoomSize.min,
                             ReverbEffect::RoomSize.max,
                             [this](double v) { mutSettings().mRoomSize = v; }
                             );

    m_paramsList << makeItem("PreDelay",
                             muse::qtrc("effects", "Pre-delay (ms)"),
                             rs.mPreDelay,
                             ReverbEffect::PreDelay.min,
                             ReverbEffect::PreDelay.max,
                             [this](double v) { mutSettings().mPreDelay = v; }
                             );

    m_paramsList << makeItem("Reverberance",
                             muse::qtrc("effects", "Reverberance (%)"),
                             rs.mReverberance,
                             ReverbEffect::Reverberance.min,
                             ReverbEffect::Reverberance.max,
                             [this](double v) { mutSettings().mReverberance = v; }
                             );

    m_paramsList << makeItem("HfDamping",
                             muse::qtrc("effects", "Damping (%)"),
                             rs.mHfDamping,
                             ReverbEffect::HfDamping.min,
                             ReverbEffect::HfDamping.max,
                             [this](double v) { mutSettings().mHfDamping = v; }
                             );

    m_paramsList << makeItem("ToneLow",
                             muse::qtrc("effects", "Tone Low (%)"),
                             rs.mToneLow,
                             ReverbEffect::ToneLow.min,
                             ReverbEffect::ToneLow.max,
                             [this](double v) { mutSettings().mToneLow = v; }
                             );

    m_paramsList << makeItem("ToneHigh",
                             muse::qtrc("effects", "Tone High (%)"),
                             rs.mToneHigh,
                             ReverbEffect::ToneHigh.min,
                             ReverbEffect::ToneHigh.max,
                             [this](double v) { mutSettings().mToneHigh = v; }
                             );

    m_paramsList << makeItem("WetGain",
                             muse::qtrc("effects", "Wet Gain (dB)"),
                             rs.mWetGain,
                             ReverbEffect::WetGain.min,
                             ReverbEffect::WetGain.max,
                             [this](double v) { mutSettings().mWetGain = v; }
                             );

    m_paramsList << makeItem("DryGain",
                             muse::qtrc("effects", "Dry Gain (dB)"),
                             rs.mDryGain,
                             ReverbEffect::DryGain.min,
                             ReverbEffect::DryGain.max,
                             [this](double v) { mutSettings().mDryGain = v; }
                             );

    m_paramsList << makeItem("StereoWidth",
                             muse::qtrc("effects", "Stereo Width (%)"),
                             rs.mStereoWidth,
                             ReverbEffect::StereoWidth.min,
                             ReverbEffect::StereoWidth.max,
                             [this](double v) { mutSettings().mStereoWidth = v; }
                             );

    emit paramsListChanged();
    emit wetOnlyChanged();
}

QVariantList ReverbViewModel::paramsList() const
{
    return m_paramsList;
}

void ReverbViewModel::setParam(const QString& key, double val)
{
    LOGD() << "param: " << key << ", new value: " << val;
    Setter s = m_setters.value(key, nullptr);
    IF_ASSERT_FAILED(s) {
        return;
    }
    s(val);
}

bool ReverbViewModel::wetOnly() const
{
    return settings().mWetOnly;
}

void ReverbViewModel::setWetOnly(bool newWetOnly)
{
    mutSettings().mWetOnly = newWetOnly;
    emit wetOnlyChanged();
}