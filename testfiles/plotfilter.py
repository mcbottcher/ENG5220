import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import numpy as np

#Plot the filtered signal
filtered = [None]*4
for i in range(4):
    filtered[i] = np.fromfile("testdata/filtered{}.bin".format(i),dtype=np.dtype('d'))
    plt.figure(i)
    plt.plot(filtered[i])
    plt.savefig('testdata/filtered{}.png'.format(i))

#Plot the impulse response
impulse = [None]*4
for i in range(4):
    impulse[i] = np.fromfile("testdata/impulse{}.bin".format(i),dtype=np.dtype('d'))
    plt.figure(10+i)
    plt.plot(impulse[i])
    plt.savefig('testdata/impulse{}.png'.format(i))