#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class AdsrData : public juce::ADSR
{
    public:

        AdsrData();
        ~AdsrData();

        void updateAdsr(const float attack, const float decay, 
            const float sustain, const float release);

    private:

        juce::ADSR::Parameters adsrParams;
        
};

