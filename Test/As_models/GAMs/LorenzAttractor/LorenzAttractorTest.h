/**
 * @file LorenzAttractorTest.h
 * @brief Header file for class LorenzAttractorTest
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
 * @details This header file contains the declaration of the class 
 * with all of its public, protected and private members. It may also include
 * definitions for inline methods which need to be visible to the compiler.
 */

// TODO : COOKIECUTTER GENERATE IDEMPOTENT GUARD

#ifndef LORENZATTRACTORTEST_H_
#define LORENZATTRACTORTEST_H_

/*---------------------------------------------------------------------------*/
/*                        Standard header includes                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                        Project header includes                            */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                           Class declaration                               */
/*---------------------------------------------------------------------------*/
/**
 * @brief Tests the LorenzAttractor public methods.
 */
class LorenzAttractorTest {
public:
    /**
     * @brief Constructor. NOOP.
     */
    LorenzAttractorTest();

    /**
     * @brief Destructor. NOOP.
     */
    virtual ~LorenzAttractorTest();

    /**
     * @brief Tests the default constructor
     * @return true after GAM instantiation.
     */
    bool TestConstructor();

    /**
     * @brief Tests the Execute() method
     * @return true if Execute succeeds.
     */
    bool TestExecute();

    /**
     * @brief Tests the Setup() method
     * @details Verify the post-conditions
     * @return true if Setup() succeeds.
     */
    bool TestSetup();


};

/*---------------------------------------------------------------------------*/
/*                        Inline method definitions                          */
/*---------------------------------------------------------------------------*/

#endif /* LORENZATTRACTORTEST_H_ */

