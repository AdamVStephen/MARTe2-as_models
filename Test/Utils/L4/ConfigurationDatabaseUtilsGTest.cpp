/**
 * @file LorenzAttractorGTest.cpp
 * @brief Source file for class LorenzAttractorGTest
 * @date 2020-09-08T14:54:57.061624
 * @author Adam V Stephen
 */

/*
 * @copyright United Kingdom Atomic Energy Authority
 *
 * Licensed under the EUPL, Version 1.1 or - as soon they will be approved
 * by the European Commission - subsequent versions of the EUPL (the "Licence")
 * You may not use this work except in compliance with the Licence.
 * You may obtain a copy of the Licence at: http://ec.europa.eu/idabc/eupl
 *
 * @warning Unless required by applicable law or agreed to in writing, 
 * software distributed under the Licence is distributed on an "AS IS"
 * basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the Licence permissions and limitations under the Licence.
 */

/*
 * @details This source file contains the definition of all the methods for
 * the class ConstantGAM (public, protected, and private). Be aware that some
 * methods, such as those inline could be defined on the header file, instead.
 */

#define DLL_API

/*---------------------------------------------------------------------------*/
/*                         Standard header includes                          */
/*---------------------------------------------------------------------------*/
#include "gtest/gtest.h"
/*---------------------------------------------------------------------------*/
/*                         Project header includes                           */
/*---------------------------------------------------------------------------*/

#include "ConfigurationDatabaseUtils.h"
#include "ConfigurationDatabaseUtilsTest.h"

/*---------------------------------------------------------------------------*/
/*                           Static definitions                              */
/*---------------------------------------------------------------------------*/

TEST(ConfigurationDatabaseUtilsGTest,TestDefaultConstructor) {
    ConfigurationDatabaseUtilsTest test;
    ASSERT_TRUE(test.TestDefaultConstructor());
}

/*---------------------------------------------------------------------------*/
/*                           Method definitions                              */
/*---------------------------------------------------------------------------*/

