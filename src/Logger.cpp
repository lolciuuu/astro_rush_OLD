#include "../include/Logger.hpp"

string Logger::LOGS("Astro Rush game log\n");

Logger::Logger( string className ): className( className )
{

}

Logger::Logger() {

}

void Logger::methodStart( string methodName ) {
	info( className + "::" + methodName + " | start"  );
}

void Logger::methodEnd( string methodName ) {
	info( className + "::" + methodName + " | end"  );
}

void Logger::info( string Str ) {
#ifdef DEBUG
    cout<< "[ Info ] " << Str  << " | class::" << className << "| " << endl;
#endif
	LOGS += "[ Info ] " + Str + "\n";
}

void Logger::warring( string Str ) {
#ifdef DEBUG
    cout<< "[ Warning ] " << Str  << " | class::" << className << "| "<<endl;
#endif
	LOGS += "[ Warning ] " + Str + "\n";
}

void Logger::error( string Str ) {
#ifdef DEBUG
    cerr<< "[ Error ] " << Str  << " | class::" << className << "| " <<endl;
#endif
	LOGS += "[ Error ] " + Str + "\n";
}

void Logger::critical( string Str ) {
#ifdef DEBUG
    cerr<< "[ Critical ] " << Str  << " | class::" << className << "| "<<endl;
#endif
	LOGS += "[ Critical ] " + Str + "\n";
}

/** @TODO dopisac zapisywanie logow w osobnym watkow i wywolywane przez timer */
void Logger::initTimer() {

}
