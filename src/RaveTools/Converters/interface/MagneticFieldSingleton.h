#ifndef _MagneticFieldSingleton_H_
#define _MagneticFieldSingleton_H_

//#include "MagneticField/Engine/interface/MagneticField.h"
#include <rave/MagneticField.h>

namespace rave{
class MagneticFieldSingleton : public MagneticField
{
  /** singleton that provides the magnetic field.
   */
  public:
    static MagneticFieldSingleton * Instance();
    GlobalVector inTesla ( const GlobalPoint & o ) const;
    void registry ( MagneticField * field );
    void release ();
    bool hasField() const;
    const MagneticField * field() const;
    virtual MagneticField * copy() const;
  private:
    MagneticFieldSingleton();
    MagneticFieldSingleton ( const MagneticFieldSingleton & );
    const MagneticField * theField;
};
} // namespace rave
#endif
