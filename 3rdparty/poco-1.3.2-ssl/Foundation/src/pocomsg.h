//
// pocomsg.mc[.h]
//
// $Id: //poco/1.3/Foundation/src/pocomsg.mc#1 $
//
// The Poco message source/header file.
//
// NOTE: pocomsg.h is automatically generated from pocomsg.mc.
//       Never edit pocomsg.h directly!
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
//
// Categories
//
//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//


//
// Define the severity codes
//


//
// MessageId: POCO_CTG_FATAL
//
// MessageText:
//
// Fatal
//
#define POCO_CTG_FATAL                   0x00000001L

//
// MessageId: POCO_CTG_CRITICAL
//
// MessageText:
//
// Critical
//
#define POCO_CTG_CRITICAL                0x00000002L

//
// MessageId: POCO_CTG_ERROR
//
// MessageText:
//
// Error
//
#define POCO_CTG_ERROR                   0x00000003L

//
// MessageId: POCO_CTG_WARNING
//
// MessageText:
//
// Warning
//
#define POCO_CTG_WARNING                 0x00000004L

//
// MessageId: POCO_CTG_NOTICE
//
// MessageText:
//
// Notice
//
#define POCO_CTG_NOTICE                  0x00000005L

//
// MessageId: POCO_CTG_INFORMATION
//
// MessageText:
//
// Information
//
#define POCO_CTG_INFORMATION             0x00000006L

//
// MessageId: POCO_CTG_DEBUG
//
// MessageText:
//
// Debug
//
#define POCO_CTG_DEBUG                   0x00000007L

//
// MessageId: POCO_CTG_TRACE
//
// MessageText:
//
// Trace
//
#define POCO_CTG_TRACE                   0x00000008L

//
// Event Identifiers
//
//
// MessageId: POCO_MSG_LOG
//
// MessageText:
//
// %1
//
#define POCO_MSG_LOG                     0x00001000L

