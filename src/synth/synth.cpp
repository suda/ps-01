#include "synth.h"

Synth::Synth() {
#if defined(PARTICLE)
    __timer = IntervalTimer();
    __output = DacSoundOutput();
#else
    __output = FileSoundOutput();
#endif
}

Synth::~Synth() {
}

void Synth::begin() {
	// ~20kHz sampling
#if defined(PARTICLE)
    __timer.begin(renderSample, 50, uSec);
#else
    boost::asio::io_service::work work(io);
    __timer.expires_from_now(boost::posix_time::seconds(1));
    __timer.async_wait(boost::bind(&Synth::onTimer, this));
#endif
}

void Synth::renderSample(void) {
	// Render each voice
	// Mix voices
	// Output to channels
}

#if defined(PARTICLE)

#else
void Synth::onTimer(const boost::system::error_code& error)
{
    __timer.expires_from_now(boost::posix_time::seconds(1));
    __timer.async_wait(boost::bind(&Synth::onTimer, this));
}
#endif