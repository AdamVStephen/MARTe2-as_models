#ifndef CONFIGURATIONDATABASEUTILSTEST_H_
#define CONFIGURATIONDATABASEUTILSTEST_H_

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
 * @brief Tests the ConfigurationDatabase functions.
 */
class ConfigurationDatabaseUtilsTest {
public:
    /**
     * @brief Tests that the default constructor initialises the shared mutex Semaphore.
     */
    bool TestDefaultConstructor();

    /**
     * @brief Tests an inline configuration
     */
    bool TestInlineConfiguration();

    
};

#endif /* CONFIGURATIONDATABASEUTILSTEST_H_ */

