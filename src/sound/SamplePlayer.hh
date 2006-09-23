// $Id: $

#ifndef SAMPLEPLAYER_HH
#define SAMPLEPLAYER_HH

#include "SoundDevice.hh"

namespace openmsx {

class SamplePlayer : public SoundDevice
{
public:
	SamplePlayer(Mixer& mixer, const std::string& name,
	             const std::string& desc, const XMLElement& config);
	~SamplePlayer();

	void reset();
	void play(const void* buffer, unsigned bufferSize,
	          unsigned bits, unsigned inFreq);
	bool isPlaying() const;

private:
	inline int getSample(unsigned index);

	// SoundDevice
	virtual void setVolume(int newVolume);
	virtual void setSampleRate(int sampleRate);
	virtual void updateBuffer(unsigned length, int* buffer,
	        const EmuTime& start, const EmuDuration& sampDur);
    
	int volume;
	unsigned outFreq;
	bool bits8;
	const void* sampBuf;
	unsigned count;
	unsigned step;
	unsigned end;
	bool playing;
};

} // namespace openmsx

#endif
