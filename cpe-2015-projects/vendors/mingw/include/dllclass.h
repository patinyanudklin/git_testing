#ifndef dllclass_h_included
#define dllclass_h_included

#if __GNUC__ && ! defined (__declspec)
# error This example needs newer egcs 1.1 or newer. Sorry.
#endif

#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */

struct DLLIMPORT 
DllClassBase {
  virtual int virtual_method () const;
};

class DLLIMPORT 
DllClass : public DllClassBase {
public:
  DllClass (int i = 0);
  ~DllClass ();
  int non_virtual_method () const;
  virtual int virtual_method () const;
#ifdef __GNUC__
  DLLIMPORT 			// work around an egcs-1.1 bug
#endif
  static int instances;
private:
  int i_;
};

#endif /* dllclass_h_included */
