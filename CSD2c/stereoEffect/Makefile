OUTDIR  = build/
OUT     = $(OUTDIR)stereoEffect
CXX     = g++
CFLAGS  := -Wall -std=c++17
LDFLAGS = -ljack
ODIR    = $(OUTDIR)obj
SDIR    = src
INC     = -Iinc

all: $(OUT)

_OBJS = \
	main.o \
	jack/ringbuffer.o \
	jack/jack_module.o \
	jack/jack_module_stereo.o \
	tools/tools.o \
	tools/circBuffer.o \
	tools/writeToFile.o \
	tools/bufferDebugger.o \
	oscillators/voice.o \
	oscillators/oscillator.o \
	oscillators/waveforms/sine.o \
	oscillators/waveforms/square.o \
	oscillators/waveforms/saw.o \
	oscillators/waveforms/triangle.o \
	oscillators/waveforms/fm_osc.o \
	effects/Effect.o \
	effects/GainEffect.o \
	effects/DelayEffect.o \
	effects/TremoloEffect.o \
	effects/ChorusEffect.o \
	effects/WaveShaperEffect.o

OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cpp
	@if [ ! -d $(@D) ]; then mkdir -p $(@D); echo "entering folder $(@D)"; fi
	@echo "building $<"; $(CXX) $(CFLAGS) -c $(INC) -o $@ $< $(CFLAGS)

$(ODIR)/%.a: $(SDIR)/%.a
	@if [ ! -d $(@D) ]; then mkdir -p $(@D); fi
	@echo "copying library $<"; cp $< $@

$(OUT): $(OBJS)
	@echo "Linking files";
	@$(CXX) $(LDFLAGS) -o $(OUT) $^;
	@echo "\nBuild complete\nRun ./$(OUT)"

.PHONY: clean

$(BUILD_DIR)%/:
	 mkdir -p $@

clean:
	rm -f -R $(OUTDIR)
