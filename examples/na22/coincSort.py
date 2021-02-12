import numpy as np
from matplotlib import pyplot as plt
import matplotlib as mpl
import sys

# The detector resolution is simulated as the sum of two Gaussians
sigmaPar   = 0.75    # First energy resolution parameter

# Linear energy calibration
a          = 0       # Energy calibration offset (keV)
b          = 1       # Energy calibration slope (keV/bin)

# Histogram specifications
eMax       = 2048
nBins      = 2048

def readInputFile(fileName = "coincSort.inp"):

    try:
        inFile = open(fileName, 'r')
    except IOError:
        return
    
    line      = inFile.readline()
    words     = line.split()
    sigmaPar  = float(words[0])

    line  = inFile.readline()
    words = line.split()
    a     = float(words[0])

    line  = inFile.readline()
    words = line.split()
    b     = float(words[0])

    line  = inFile.readline()
    words = line.split()
    eMax  = float(words[0])

    line  = inFile.readline()
    words = line.split()
    nBins = int(words[0])

    line  = inFile.readline()
    words = line.split()
    lLim  = int(words[0])

    line  = inFile.readline()
    words = line.split()
    uLim  = int(words[0])

    inFile.close()

    return sigmaPar, a, b, eMax, nBins, lLim, uLim

def Sort(fileName):

    try:
        inFile = open(fileName, 'r')
    except IOError:
        print('Error: unable to open file {0}'.format(fileName))
        return

    # Sort the output file.
    counts = np.zeros(nBins)
    eventNumLast = -1
    detIDLast    = 0
    eResLast     = 0
    e1s = []
    e2s = []
    for line in inFile.readlines():
        words = line.split()

        eventNum = int(words[0])
        detID    = int(words[1])
        eSim     = float(words[2])

        # Fold in simulated resolution.
        sigma = sigmaPar*np.sqrt(eSim)
        eRes = eSim + np.random.normal(scale=sigma)

        # De-calibrate to match measured histogram
        eRes = (eRes - a)/b

        # Check for a coincidence
        if eventNum == eventNumLast:
            # Get the energy deposited in each detector
            if detID == 1:
                e1 = eRes
                e2 = eResLast
            else:
                e1 = eResLast
                e2 = eRes
            e1s.append(e1)
            e2s.append(e2)
            
        eventNumLast = eventNum
        detIDLast    = detID
        eResLast     = eRes
        
    return e1s, e2s

def writeMCA(counts, fname):

    outFileName = fname
    
    try:
        outFile = open(outFileName, 'w')
    except IOError:
        print('Error: unable to open output file {0}'.format(fileName))
        return

    header = '''
<<PMCA SPECTRUM>>
TAG - 
DESCRIPTION - UCNaI simulation 
GAIN - 0
THRESHOLD - 0
LIVE_MODE - 0
PRESET_TIME - 0
LIVE_TIME - 0
REAL_TIME - 0
START_TIME - 0
SERIAL_NUMBER - 0
<<DATA>>
'''
    outFile.write(header)
    for count in counts:
        outFile.write(str(int(count))+'\n')

    outFile.write('<<<END>>>')
    
    return

sigmaPar, a, b, eMax, nBins, lLim, uLim = readInputFile()

e1s, e2s = Sort(sys.argv[1])

plt.figure(1)
# matplotlib does a good job of filling histograms from lists.
# The norm=mpl.colors.LogNorm() uses a log scale for the color map
# which is helpful for seeing weak coincidences.
matrix, xedges, yedges, _ = plt.hist2d(e1s, e2s, bins=[nBins, nBins],
                                       range=[[0, eMax],[0, eMax]],
                                       cmap='inferno',
                                       norm=mpl.colors.LogNorm())
ax = plt.gca()
ax.set_aspect('equal')
plt.colorbar(orientation='vertical')
plt.xlabel('Detector 1 Energy (keV)')
plt.ylabel('Detector 2 Energy (keV)')
plt.title('{0} Coincidence Matrix'.format(sys.argv[1]))

# Det 2 spectrum gated on det 1
lBin = int(lLim/eMax*nBins)
uBin = int(uLim/eMax*nBins)
slice = matrix[lBin:uBin+1, 0:200]
scounts = []
for bin in range(nBins):
    scounts.append(sum(slice[:,bin]))

mcaFileName = sys.argv[1]
mcaFileName = mcaFileName.replace('.out', '_coinc.mca')

writeMCA(scounts, mcaFileName)

plt.figure(2)
# It's not straightforward to produce a matplotlib 1D histogram from a
# 2D array, so we'll use the plt.step() to plot the gated spectrum.

# yedges[0:-1] is the list of lower bin edges, so use where='post'.
plt.step(yedges[0:-1], scounts, where='post')
plt.title('{0}: Detector 2 {1:.0f}:{2:.0f} keV Gate'\
          .format(sys.argv[1], lLim, uLim))    
plt.xlabel('Energy (keV)')
plt.ylabel('Counts/{0:.0f} keV'.format(yedges[1]-yedges[0]))

print('{0}: {1:.0f}:{2:.0f} keV Gate total = {3} counts'\
          .format(sys.argv[1], lLim, uLim, sum(scounts)))

plt.show()
