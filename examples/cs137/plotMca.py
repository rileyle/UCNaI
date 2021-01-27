import matplotlib.pyplot as plt
import numpy as np
import sys

#======================================================================
# Read a spectrum from an ADMCA .mca file
#
#   To load the spectrum in the file "myspectrum.mca" (stored in the
#   same directory as the notebook):
#
#   realTime, liveTime, bins, counts = readMca("myspectrum.mca", 10)
#
#   realTime: duration of the measurement
#   liveTime: live time of the acquisition system
#   bins:  list of bin positions
#   counts list of count values
#
#======================================================================
def readMca(filename, binning = 1):
    infile = open(filename, 'r')
    
    # Skip to line 8 and store the live time.
    for i in range(8):
        line = infile.readline()
    words = line.split()
    liveTime = float(words[2])
    
    # Store the real time.
    line = infile.readline()
    words = line.split()
    realTime = float(words[2])
    
    # Skip the rest of the header.
    for i in range(7):
        line = infile.readline()
    
    # Empty lists for the spectrum
    bins   = []
    counts = []
    
    bin = 1
    while 1:
        line = infile.readline();
        if "END" in line:  # Stop when you read the <<END>> tag
            break
        words = line.split()
        bins.append(bin)
        bin += 1
        counts.append(float(words[0]))
    bins   = np.array(bins)
    counts = np.array(counts)
    
    # Rebin the spectrum.
    if binning > 1:
        newbins = []
        newcounts = []
        j = 0
        bin = 0
        count = 0
        for i in range(len(bins)):
            j += 1
            count += counts[i]
            bin   += bins[i]
            if j == binning:
                newbins.append(bin/binning)
                newcounts.append(count)
                j = 0
                bin = 0
                count = 0
        bins   = np.array(newbins)
        counts = np.array(newcounts)
        
    return realTime, liveTime, bins, counts

if(len(sys.argv) == 3):
    binning = int(sys.argv[2])
elif(len(sys.argv) == 2):
    binning = 1
else:
    print('Usage: python plotPCA.py <filename> <binning=1>')
    exit

realTime, liveTime, bins, counts = readMca(sys.argv[1], binning)

plt.step(bins, counts, where='mid', color='blue')
#plt.yscale('log')
plt.xlabel('E (keV)')
plt.ylabel('Counts/bin')
plt.title(sys.argv[1])

plt.show()
