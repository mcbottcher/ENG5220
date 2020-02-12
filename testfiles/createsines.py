import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

fs = 500
t = 1
samples = np.arange(t * fs) / fs
out = np.zeros(fs*t)

def wave(freq):
    sine_wave = np.sin(2 * np.pi * freq * samples)
    sine_wave = sine_wave/max(sine_wave)
    return sine_wave

out = wave(10) + wave(50) + wave(150) + wave(200)
out.tofile('testdata/sin.bin') 
plt.plot(out)
plt.savefig('testdata/mixsin.png')