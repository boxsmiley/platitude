//
// Created by william on 7/6/17.
//
#ifndef FAM_EXAMPLE
#define FAM_EXAMPLE

#include <fam.h>
#include <iostream>
#include <string.h>

class Fam
{

private:
        FAMConnection* fc;
        FAMRequest* fr;
        // event data is put here.  This pointer will be reused for each event.
        FAMEvent* fe = new FAMEvent() ;


        enum {
                ERROR_STAT_FILE = 1 ,
                ERROR_DETERMINE_USER ,
                ERROR_FAM_OPEN ,
                ERROR_FAM_MONITOR
        } ;



        void checkStrerror( int error ){
                if( 0 != error ){
                        std::cerr << "System error is: " << strerror( errno ) << std::endl ;
                }
                return ;
        }


public:
    Fam(const char* toWatch)
    {
        // init FAM connection
        fc = new FAMConnection() ;
        fr = new FAMRequest() ;

        // connect to the FAM service
        if( 0 != FAMOpen( fc ) ){
                std::cerr << "FAM connectivity test failed: unable to open FAM connection." << std::endl ;
                std::cerr << "(Hint: make sure FAM (via xinetd) and portmapper are running.)" << std::endl ;
                checkStrerror( errno ) ;
                throw( ERROR_FAM_OPEN ) ;
        }
        // register interest in a directory, here, "/tmp"
        if( 0 != FAMMonitorDirectory( fc , toWatch , fr , NULL ) ){
                std::cerr << "FAM connectivity test failed: unable to monitor \"" << toWatch << "\"" << std::endl ;
                checkStrerror( errno ) ;
                throw( ERROR_FAM_MONITOR ) ;
        }
        std::cout << "connectivity worked.  fam properly configged" << std::endl;

        while (1) {
            while (1 == FAMNextEvent(fc, fe)) {
                std::cout << "\t" << fe->filename << std::endl;
            }
        }



    }

    virtual ~Fam()
    {
                // stop receiving events
        FAMCancelMonitor( fc , fr ) ;


        // disconnect from the FAM service
        FAMClose( fc ) ;

        delete( fr ) ;
        delete( fc ) ;

    }


};

#endif
