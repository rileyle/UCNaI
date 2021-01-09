all:  cs137.out                     cs137.root
	echo "Geant4 simulations done."

# Pattern rules for running Geant4 simulations.
%.out : %.mac
	if test -e $*.out; \
	then echo "Removing existing file $*.out"; rm $*.out; \
	fi
	time UCNaI $*.mac > $*.log

# Pattern rule for sorting the simulation output into Root histograms
# and Radware ascii spectra
%.root : %.out	
	root -l -b -q 'NaISort.C("$*.out","NaI.dat")'
	root -l -b -q 'root2rad.C("$*.root","$*")'

clean:
	rm *.log *.out *.root *.rad *.spe *.wrl
