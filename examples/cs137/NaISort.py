import numpy as np
from matplotlib import pyplot as plt
import sys

# The detector resolution is simulated with a Gaussian distribution
# with energy-dependent width sigma = sigmaPar*sqrt(E)
sigmaPar   = 0.75    # Energy resolution parameter

# Linear energy calibration
a          = 0       # Energy calibration offset (keV)
b          = 1       # Energy calibration slope (keV/bin)

# Histogram specifications
eMax       = 2048
nBins      = 2048

def readInputFile(fileName = "NaISort.inp"):

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

    inFile.close()

    return sigmaPar, a, b, eMax, nBins 

def Sort(fileName):

    try:
        inFile = open(fileName, 'r')
    except IOError:
        print('Error: unable to open file {0}'.format(fileName))
        return

    # List of energies at bin centers.
    energies = []
    width = float(eMax/nBins)
    for bin in range(nBins):
        energies.append((bin+0.5)*width)
        
    # Sort the output file.
    counts = np.zeros(nBins)
    photopeakCounts = 0
    for line in inFile.readlines():
        words = line.split()
        eSim  = float(words[2])

        if int(words[6]) == 1:
            photopeakCounts += 1
        
        # Fold in simulated resolution.
        sigma = sigmaPar*np.sqrt(eSim)
        eRes = eSim + np.random.normal(scale=sigma)

        # De-calibrate to match measured histogram
        eRes = (eRes - a)/b
        
        bin  = int(eRes/eMax*nBins)
        if bin >= 0 and bin < nBins:
            counts[bin] += 1

    print('{0:d} photopeak counts'.format(photopeakCounts))
        
    return energies, counts

def writeMCA(counts):
    fileName = sys.argv[1]
    outFileName = fileName.replace('.out', '.mca')
    
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

sigmaPar, a, b, eMax, nBins = readInputFile()

energies, counts = Sort(sys.argv[1])

writeMCA(counts)

#plt.step(energies, counts, where='mid')
#plt.show()
