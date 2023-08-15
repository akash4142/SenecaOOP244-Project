/*name - akash yadav
student no. = 172566218
seneca email- ayadav35@myseneca.ca
section - ncc

citation-:

 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
#include "Error.h"

namespace sdds {

        
        Error::Error() : message_(nullptr) {}

        
        Error::Error(const char* errorMessage) {
            if (errorMessage != nullptr && *errorMessage != '\0') {
                message_ = new char[strlen(errorMessage) + 1];
                strcpy(message_, errorMessage);
            }
            else {
                message_ = nullptr;
            }
        }

        
        Error::Error(const Error& other) : message_(nullptr) {
            *this = other;
        }

        
        Error& Error::operator=(const Error& other) {
            if (this != &other) {
                delete[] message_;
                message_ = nullptr;
                if (other.message_ != nullptr) {
                    message_ = new char[strlen(other.message_) + 1];
                    strcpy(message_, other.message_);
                }
            }
            return *this;
        }

        
        Error::~Error() {
            delete[] message_;
        }

        
        void Error::message(const char* errorMessage) {
            delete[] message_;
            message_ = nullptr;
            if (errorMessage != nullptr && *errorMessage != '\0') {
                message_ = new char[strlen(errorMessage) + 1];
                strcpy(message_, errorMessage);
            }
        }

       
        Error::operator bool() const {
            return message_ != nullptr;
        }

        
        Error& Error::clear() {
            delete[] message_;
            message_ = nullptr;
            return *this;
        }

       
        const char* Error::getMessage() const {
            return message_;
        }

        std::ostream& operator<<(std::ostream& os, const Error& error) {
            if (error) {
                os << error.getMessage();
            }
            return os;
        }
    }


