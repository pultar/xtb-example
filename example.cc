#include <cstddef>
#include <iostream>
#include "xtb.h"

int main (int argc, char** argv)
{
  /*
   * Parameters for the molecule.
   */
  int    const natoms = 7;
  int    const attyp[7] = {6,6,6,1,1,1,1};
  double const charge = 0.0;
  int    const uhf = 0;
  double const coord[3*7] =
      {0.00000000000000, 0.00000000000000,-1.79755622305860,
       0.00000000000000, 0.00000000000000, 0.95338756106749,
       0.00000000000000, 0.00000000000000, 3.22281255790261,
      -0.96412815539807,-1.66991895015711,-2.53624948351102,
      -0.96412815539807, 1.66991895015711,-2.53624948351102,
       1.92825631079613, 0.00000000000000,-2.53624948351102,
       0.00000000000000, 0.00000000000000, 5.23010455462158};
  double energy = 0;
  
  /*
   * Parameters for external point charges.
   */
  int    npc = 7;
  double pc[npc] =
      {0.234, -0.234, 0.785, 0.568, -0.975, 0.123, -0.501};
  double pccoord[npc*7] =
      {0.50000000000000, 0.00000000000000,-1.79755622305860,
       0.00000000000000, 0.50000000000000, 0.95338756106749,
       0.00000000000000, 0.50000000000000, 3.22281255790261,
      -0.96412815539807,-1.16991895015711,-2.53624948351102,
      -0.96412815539807, 1.16991895015711,-2.53624948351102,
       1.92825631079613, 0.50000000000000,-2.53624948351102,
       0.00000000000000, 0.50000000000000, 5.23010455462158};
  int numbers[npc] = {0, 0, 0, 0, 0, 0, 0};
  double pcgrad[npc*7] =
      {1.0, 2.0, 3.0,
       1.0, 2.0, 3.0,
       1.0, 2.0, 3.0,
       1.0, 2.0, 3.0,
       1.0, 2.0, 3.0,
       1.0, 2.0, 3.0,
       1.0, 2.0, 3.0};

  /*
   * All objects except for the molecular structure can be
   * constructued without other objects present.
   *
   * The construction of the molecular structure locks the
   * number of atoms, atomic number, total charge, multiplicity
   * and boundary conditions.
  **/
  xtb_TEnvironment env = xtb_newEnvironment();
  xtb_TCalculator calc = xtb_newCalculator();
  xtb_TResults res = xtb_newResults();
  xtb_TMolecule mol = xtb_newMolecule(
      env, &natoms, attyp, coord, &charge, &uhf, NULL, NULL);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  /*
   * Apply changes to the environment which will be respected
   * in all further API calls.
  **/
  xtb_setVerbosity(env, XTB_VERBOSITY_FULL);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  /*
   * Load a parametrisation, the last entry is a char* which can
   * be used to provide a particular parameter file.
   *
   * Otherwise the XTBPATH environment variable is used to find
   * parameter files.
   *
   * The calculator has to be reconstructed if the molecular
   * structure is reconstructed.
  **/
  xtb_loadGFN1xTB(env, mol, calc, NULL);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  xtb_setExternalCharges(env, calc, &npc, numbers, pc, pccoord);
   if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
   }

  /*
   * Actual calculation, will populate the results object,
   * the API can raise errors on failed SCF convergence or other
   * numerical problems.
   *
   * Not supported boundary conditions are usually raised here.
  **/
  xtb_singlepoint(env, mol, calc, res);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  /*
   * Query the environment for properties, an error in the environment
   * is not considered blocking for this calls and allows to query
   * for multiple entries before handling possible errors
  **/
  xtb_getEnergy(env, res, &energy);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  xtb_getPCGradient(env, calc, pcgrad);
  if (xtb_checkEnvironment(env)) {
    xtb_showEnvironment(env, NULL);
    return 1;
  }

  std::cout << "Gradients on point charges:" << std::endl;
  for (unsigned int i = 0; i < 3*npc; ++i) {
    std::cout << "# " << i << std::endl;
    std::cout << pcgrad[i] << "\n" << std::endl;
  }

  /*
   * deconstructor will deallocate the objects and overwrite the
   * pointer with NULL
  **/
  xtb_delResults(&res);
  xtb_delCalculator(&calc);
  xtb_delMolecule(&mol);
  xtb_delEnvironment(&env);

  return 0;
}