all:  cs137.root
	echo "Geant4 simulations done."

# Pattern rules for running Geant4 simulations.
%.out : %.mac
	if test -e $*.out; \
	then echo "Removing existing file $*.out"; rm $*.out; \
	fi
	time UCNaI $*.mac 2>&1 | tee $*.log

# Pattern rule for sorting the simulation output into Root histograms
# and Radware ascii spectra
%.root : %.out	
	root -l -b -q 'NaISort.C("$*.out","NaISort.inp")' 2>&1 | tee -a $*.log
	root -l -b -q 'root2rad.C("$*.root","$*")' 2>&1 | tee -a $*.log

clean:
	rm *.log *.out *.root *.rad *.spe *.wrl
