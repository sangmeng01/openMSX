// $Id$

// This class implements a 16 bit signed DAC

#ifndef DACSOUND16S_HH
#define DACSOUND16S_HH

#include "SoundDevice.hh"
#include "BlipBuffer.hh"
#include "EmuTime.hh"
#include <deque>

namespace openmsx {

class DACSound16S : public SoundDevice
{
public:
	DACSound16S(MSXMixer& mixer, const std::string& name,
	            const std::string& desc, const XMLElement& config);
	virtual ~DACSound16S();

	void reset(const EmuTime& time);
	void writeDAC(short value, const EmuTime& time);

private:
	// SoundDevice
	virtual void setOutputRate(unsigned sampleRate);
	virtual void generateChannels(int** bufs, unsigned num);
	virtual bool updateBuffer(unsigned length, int* buffer,
	        const EmuTime& start, const EmuDuration& sampDur);

	struct Sample {
		Sample(const EmuTime& time_, int value_)
			: time(time_), value(value_) {}
		EmuTime time;
		int value;
	};
	typedef std::deque<Sample> Queue;
	Queue queue;

	BlipBuffer blip;
	EmuTime start;
	EmuDuration sampDur;
	short lastWrittenValue;
};

} // namespace openmsx

#endif
