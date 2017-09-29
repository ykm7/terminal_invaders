//
// Created by yoakim on 26/09/17.
//

#include "catch.hpp"

// Required, as while Catch is written in C++, the program is in C.
extern "C" {
    #include "../include/aliens.h"
}

/**
 * NOTES: As this is a C++ tool, NULL values are considered differently.
 *
 */

#include "../include/main.h"

//SCENARIO("Power off tests", "[power_button]")
//{
//    GIVEN("the power is off")
//    {
//        power_button_initialize(POWER_OFF);
//
//        WHEN("nothing happens")
//        {
//            THEN("the power is still off")
//            {
//                REQUIRE(power_button_getPowerState() == POWER_OFF);
//            }
//        }
//
//        WHEN("the power button is momentarily pressed")
//        {
//            power_button_pressMomentary();
//
//            THEN("the power turns on")
//            {
//                REQUIRE(power_button_getPowerState() == POWER_ON);
//            }
//        }
//    }
//}

/*
 * # FUNCTIONS TO TEST
 *
 * Aliens* initialiseAliens(const int);
 * void destroyAliens(Aliens *);
 * void moveAliens(Aliens *,Bullets *, int, int, int);
 * void killAlien(Alien *, int *const);
 */

SCENARIO("Aliens creation/ destruction tests", "[Aliens* initialiseAliens(const int)]"){
    WHEN("Non zero initiation."){
        const int testValue = 10;
        Aliens* aliens = initialiseAliens(testValue);
        THEN("Created aliens"){
            REQUIRE(aliens != 0);
            CHECK(aliens->totalNumAliens == testValue);
            int counter = 0;
            while(counter < aliens->totalNumAliens){
                counter++;
            }
            CHECK(counter == testValue);
        }

        THEN("Destroying aliens"){
            destroyAliens(&aliens);
//            CHECK(aliens->aliens[0] == 0);
            CHECK(aliens == 0);
        }
    }

    WHEN("Zero passed to alien creation."){
        const int testValue = 0;
        Aliens* aliens = initialiseAliens(testValue);
        THEN("Created aliens"){
            REQUIRE(aliens == 0);
        }

        THEN("Destroying aliens"){
            destroyAliens(&aliens);
            CHECK(aliens == 0);
        }
    }

    WHEN("Negative value passed to alien creation."){
        const int testValue = -5;
        Aliens* aliens = initialiseAliens(testValue);
        THEN("Created aliens"){
            REQUIRE(aliens == 0);
        }

        THEN("Destroying aliens"){
            destroyAliens(&aliens);
            CHECK(aliens == 0);
        }
    }
}

