#ifndef SourceData_h
#define SourceData_h 1
class SourceData
{
public:
  SourceData() {}
  SourceData(G4double def_e, G4double def_b) : e(def_e), b(def_b) {}
  virtual ~SourceData() {}

  G4double e,b;

};
#endif
