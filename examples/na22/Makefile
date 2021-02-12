all:  center.out       center.mca       center_coinc.mca \
      off_center.out   off_center.mca   off_center_coinc.mca 
	echo "Geant4 simulations done."

# Pattern rules for running Geant4 simulations.
%.out : %.mac
	if test -e $*.out; \
	then echo "Removing existing file $*.out"; rm $*.out; \
	fi
	UCNaI $*.mac 2>&1 | tee $*.log

# Pattern rule for sorting the simulation output into Root histograms
# and Radware ascii spectra
%.mca : %.out
	python3 NaISort.py $*.out 2>&1 | tee -a $*.log

%_coinc.mca : %.out
	python3 coincSort.py $*.out 2>&1 | tee -a $*.log

clean:
	rm *.log *.out *.mca *.wrl
