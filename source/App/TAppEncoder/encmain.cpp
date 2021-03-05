/* The copyright in this software is being made available under the BSD
 * License, included below. This software may be subject to other third party
 * and contributor rights, including patent rights, and no such rights are
 * granted under this license.
 *
 * Copyright (c) 2010-2017, ITU/ISO/IEC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *  * Neither the name of the ITU/ISO/IEC nor the names of its contributors may
 *    be used to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/** \file     encmain.cpp
    \brief    Encoder application main
*/

#include <time.h>
#include <iostream>
#include <fstream>
#include "TAppEncTop.h"
#include "TAppCommon/program_options_lite.h"
#include <cstdlib>
#include "TLibCommon/TComDataCU.h"

//! \ingroup TAppEncoder
//! \{

#include "../Lib/TLibCommon/Debug.h"

// ====================================================================================================================
// Main function
// ====================================================================================================================

float depthMatrix[DM_Y][DM_X];
float balanceMatrix[4][4] = {{0.667,0.333,0,0},{0.5,0.333,0.167,0},{0.4,0.3,0.2,0.1},{0}};
float* semigopVec[semiGOP];
double v4K[26] = {1,1,1,1,0.9330,0.6215,0.4142,0.2704,0.1685,0.0966,0.0474,0.0167,0.0018,0.0018,0.0167,0.0474,0.0966,0.1685,0.2704,0.4142,0.6215,0.9330,1,1,1,1};
double v8K[32] = {1,1,1,1,1,0.9451,0.6787,0.4891,0.3496,0.2450,0.1659,0.1062,0.0621,0.0309,0.0109,0.0012,0.0012,0.0109,0.0309,0.0621,0.1062,0.1659,0.2450,0.3496,0.4891,0.6787,0.9451,1,1,1,1,1};
IntraData m64[mSizeY][mSizeX];
IntraData m32[mSizeY][mSizeX];
IntraData m16[mSizeY][mSizeX];
IntraData m8[mSizeY][mSizeX];
IntraData m4[mSizeY][mSizeX];
ofstream intraDataFile;

int main(int argc, char* argv[])
{ 
  //instanciando as matrizes em cada posicao do vetor
  for(int i=0;i<semiGOP;i++){      
    float **tempMatrix = new float*[DM_Y];
        for(int j=0;j<DM_Y;j++){
            tempMatrix[j] = new float[DM_X];
        }
    semigopVec[i] = *tempMatrix;
  }
  
  intraDataFile.open("intraDataFile.csv");
  intraDataFile << "Frame,PosY,PosX,Size,BestMode,BestModeCost,MPM1,MPM2,MPM3,RMD1,RMD2,RMD3,RMD4,RMD5,RMD6,RMD7,RMD8" << endl;
  
  TAppEncTop  cTAppEncTop;
  
  // print information
  fprintf( stdout, "\n" );
  fprintf( stdout, "HM software: Encoder Version [%s] (including RExt)", NV_VERSION );
  fprintf( stdout, NVM_ONOS );
  fprintf( stdout, NVM_COMPILEDBY );
  fprintf( stdout, NVM_BITS );
  fprintf( stdout, "\n\n" );  
          
  // create application encoder class
  cTAppEncTop.create();

  // parse configuration
  try
  {
    if(!cTAppEncTop.parseCfg( argc, argv ))
    {
      cTAppEncTop.destroy();
#if ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
      EnvVar::printEnvVar();
#endif
      return 1;
    }
  }
  catch (df::program_options_lite::ParseFailure &e)
  {
    std::cerr << "Error parsing option \""<< e.arg <<"\" with argument \""<< e.val <<"\"." << std::endl;
    return 1;
  }

#if PRINT_MACRO_VALUES
  printMacroSettings();
#endif

#if ENVIRONMENT_VARIABLE_DEBUG_AND_TEST
  EnvVar::printEnvVarInUse();
#endif

  // starting time
  Double dResult;
  clock_t lBefore = clock();

  // call encoding function
  cTAppEncTop.encode();

  // ending time
  dResult = (Double)(clock()-lBefore) / CLOCKS_PER_SEC;
  printf("\n Total Time: %12.3f sec.\n", dResult);

  // destroy application encoder class
  cTAppEncTop.destroy();    

  intraDataFile.close();
  
  return 0;
}

//! \}
