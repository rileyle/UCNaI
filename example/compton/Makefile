all:  cs137.root        compton30.root     compton40.root    compton60.root \
      compton90.root    compton120.root   compton150.root    compton180.root
	echo "Geant4 simulations done."

# Pattern rules for running Geant4 simulations.
%.out : %.mac
	if test -e $*.out; \
	then echo "Removing existing file $*.out"; rm $*.out; \
	fi
	time UCNaI $*.mac | tee $*.log

# Pattern rule for sorting the simulation output into Root histograms
# and Radware ascii spectra
%.root : %.out	
	root -l -b -q 'NaISort.C("$*.out","NaISort.inp")' | tee -a $*.log
	root -l -b -q 'root2rad.C("$*.root","$*")' | tee -a $*.log

clean:
	rm *.log *.out *.root *.rad *.spe *.wrl
