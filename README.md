# UCNaI

## Compile and install

Install version [4.10.07.p01 of the Geant4 libraries](https://geant4.web.cern.ch/geant4/support/download.shtml). You will need the data files for low energy electromagnetic processes, photon evaporation, and radioactive decay.

Set up your environment (consider adding this to your `.bashrc`):

    $ source <Path to Geant4>/bin/geant4.sh
    $ source <Path to Geant4>/share/Geant4-10.6.3/geant4make/geant4make.sh

Compile:

    $ make

## Example

A simple example collecting a spectrum from a <sup>137</sup>Cs source is included in the `./example/cs137` directory. A sorting code `NaISort.py` is included which produces a histogram in the `.mca` format (requires python3 and the numpy module). A `Makefile` is included. (Run the example by typing `make` at the command line in the `./example/cs137` directory.)

## Macro File Commands

### NaI Detector Placement

    /NaI/setX <double> <unit>
    /NaI/setY <double> <unit>
    /NaI/setZ <double> <unit>

> Set the position of the detector.

    /NaI/rotateX <double> <unit>
    /NaI/rotateY <double> <unit>
    /NaI/rotateZ <double> <unit>

> Orient the detector by rotating about X, Y, Z.

    /NaI/GeometryFile <filename>

> Set the name of the optional geometry file. If this command is present, a NaI detector is placed for each line in the specified file. Each line has the format:

        <X (mm)>  <Y (mm)>  <Z (mm)>  <X rotation (deg)>  <Y rotation (deg)>  <Z rotation (deg)>

> If a geometry file is specified, the positioning and rotation commands above are ignored.

### Source

Realistic simulations of radioactive sources can be run as illustrated by `./examples/cs137/cs137.mac`. The Simple source is a computationally more efficient alternative.

    /Source/Simple <double> <unit>

> Use a simple monoenergetic gamma-ray source with the specified energy.

    /Source/setX <double> <unit>
    /Source/setY <double> <unit>
    /Source/setZ <double> <unit>

> Set the position of the source (and capsule if present).

    /Source/Capsule/rotateX <double> <unit>
    /Source/Capsule/rotateY <double> <unit>
    /Source/Capsule/rotateZ <double> <unit>

> Orient the source capsule by rotating about X, Y, Z.

    /Source/Capsule/Construct

> Include the source capsule. Must be issued after the source positioning and capsule rotation commands.

### Lead Bricks

Optionally, 2" x 4" x 6" lead bricks can be included in simulations.

    /Brick/setX <double> <unit>
    /Brick/setY <double> <unit>
    /Brick/setZ <double> <unit>

> Set the position of the brick.

    /Brick/rotateX <double> <unit>
    /Brick/rotateY <double> <unit>
    /Brick/rotateZ <double> <unit>

> Orient the brick by rotating about X, Y, Z. (The order of these commands matters.)

    /Brick/GeometryFile <filename>

> Set the name of the optional geometry file. If this command is present, a brick  is placed for each line in the specified file.  Each line has the format:

        <X (mm)>  <Y (mm)>  <Z (mm)>  <X rotation (deg)>  <Y rotation (deg)>  <Z rotation (deg)>

> If a geometry file is specified, the positioning and rotation commands above are ignored.

    /Brick/Construct

> Include the brick. Must be issued after the positioning and rotation commands.

### Aluminum Targets

Optionally, cylindrical aluminum targets can be included in simulations.

    /Target/setR <double> <unit>

> Set the radius of the target(s).

    /Target/setL <double> <unit>

> Set the length of the target(s).

    /Target/setX <double> <unit>
    /Target/setY <double> <unit>
    /Target/setZ <double> <unit>

> Set the position of the target.

    /Target/rotateX <double> <unit>
    /Target/rotateY <double> <unit>
    /Target/rotateZ <double> <unit>

> Orient the target  by rotating about X, Y, Z. (The order of these commands matters.)

    /Target/GeometryFile <filename>

> Set the name of the optional geometry file. If this command is present, a target is placed for each line in the specified file.  Each line has the format:

        <X (mm)>  <Y (mm)>  <Z (mm)>  <X rotation (deg)>  <Y rotation (deg)>  <Z rotation (deg)>

> If a geometry file is specified, the positioning and rotation commands above are ignored.

    /Target/Construct

> Include the target(s). Must be issued after the positioning and rotation commands.

## Output

Output is written to a text file. Each line represents a detected event and has the format:

    <Event> <Detector ID> <Energy> <Hit X> <Hit Y> <Hit Z> <Full Energy>

- `<Event>` : event number
- `<Detector ID>` : integer identifying the detector registering the event
- `<Energy>` : energy deposited in keV
- `<Hit X>`, `<Hit Y>`, `<Hit Z>` :  hit position in mm
- `<Full Energy>` : == 1 if the gamma ray deposited its total energy in the detector, ==  0 otherwise

## Visualization

Run the macro file `vis/vis.mac` an interactive session:

    $ UCNaI
    
    Idle> /control/execute vis/vis.mac
    Idle> exit

This generates a VRML 2 file named `g4_XX.wrl` which can be viewed with a VRML viewer (like view3dscene, FreeWRL, or mayavi2).

The macro file `./vis/trajectories.mac` illustrates how to add particle trajectories to visualizations.
