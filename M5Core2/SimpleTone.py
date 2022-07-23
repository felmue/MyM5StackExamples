# Copyright (c) 2022 by GWENDESIGN. All rights reserved.
# Licensed under the MIT license. See LICENSE file in the project root for full license information.

# Tone example adapted for M5Core2
# https://github.com/miketeachman/micropython-i2s-examples/blob/master/examples/play_tone.py
import os
import math
import struct
from machine import I2S
from machine import Pin

def make_tone(rate, bits, frequency):
    # create a buffer containing the pure tone samples
    samples_per_cycle = rate // frequency
    sample_size_in_bytes = bits // 8
    samples = bytearray(samples_per_cycle * sample_size_in_bytes)
    volume_reduction_factor = 4
    range = pow(2, bits) // 2 // volume_reduction_factor
    
    if bits == 16:
        format = "<h"
    else:  # assume 32 bits
        format = "<l"
    
    for i in range(samples_per_cycle):
        sample = range + int((range - 1) * math.sin(2 * math.pi * i / samples_per_cycle))
        struct.pack_into(format, samples, i * sample_size_in_bytes, sample)
        
    return samples

# ======= I2S CONFIGURATION =======
SCK_PIN = 12 # BCLK
WS_PIN = 0   # LRLK
SD_PIN = 2   # SADTA
I2S_ID = 0
BUFFER_LENGTH_IN_BYTES = 2000

# ======= AUDIO CONFIGURATION =======
TONE_FREQUENCY_IN_HZ = 1000
SAMPLE_SIZE_IN_BITS = 16
FORMAT = I2S.MONO  # only MONO supported in this example
SAMPLE_RATE_IN_HZ = 22_050

audio_out = I2S(
    I2S_ID,
    sck=Pin(SCK_PIN),
    ws=Pin(WS_PIN),
    sd=Pin(SD_PIN),
    mode=I2S.TX,
    bits=SAMPLE_SIZE_IN_BITS,
    format=FORMAT,
    rate=SAMPLE_RATE_IN_HZ,
    ibuf=BUFFER_LENGTH_IN_BYTES,
)

power.speaker(True)
samples = make_tone(SAMPLE_RATE_IN_HZ, SAMPLE_SIZE_IN_BITS, TONE_FREQUENCY_IN_HZ)

# continuously write tone sample buffer to an I2S DAC
print("==========  START PLAYBACK ==========")
try:
    while True:
        num_written = audio_out.write(samples)

except (KeyboardInterrupt, Exception) as e:
    print("caught exception {} {}".format(type(e).__name__, e))

# cleanup
audio_out.deinit()
print("Done")
