import numpy as np
from matplotlib import pyplot as plt
import sys

# The detector resolution is simulated as the sum of two Gaussians
sigmaPar1  = 0.75    # First energy resolution parameter
sigmaPar2  = 1.5     # Second energy resolution parameter
sigma2Frac = 0.5     # Fraction of second resolution

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
    sigmaPar1 = float(words[0])

    line      = inFile.readline()
    words     = line.split()
    sigmaPar2 = float(words[0])

    line       = inFile.readline()
    words      = line.split()
    sigma2Frac = float(words[0])

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

    return sigmaPar1, sigmaPar2, sigma2Frac, a, b, eMax, nBins 

def Sort(fileName):

    try:
        inFile = open(fileName, 'r')
    except IOError:
        print('Error: unable to open file {0}'.format(fileName))
        return

    energies = []
    width = float(eMax/nBins)
    for bin in range(nBins):
        energies.append((bin+0.5)*width)
        
    counts = np.zeros(nBins)
    for line in inFile.readlines():
        words = line.split()
        eSim  = float(words[0])

        # Fold in simulated resolution.
        sigma1 = sigmaPar1*np.sqrt(eSim)
        sigma2 = sigmaPar2*np.sqrt(eSim)
        if(np.random.rand() > sigma2Frac):
            eRes = eSim + np.random.normal(scale=sigma1)
        else:
            eRes = eSim + np.random.normal(scale=sigma2)

        # De-calibrate to match measured histogram
        eRes = (eRes - a)/b
        
        bin  = int(eRes/eMax*nBins)
        if bin >= 0:
            counts[bin] += 1
        
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

sigmaPar1, sigmaPar2, sigma2Frac, a, b, eMax, nBins = readInputFile()

energies, counts = Sort(sys.argv[1])

writeMCA(counts)

#plt.step(energies, counts, where='mid')
#plt.show()
