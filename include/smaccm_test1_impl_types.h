#ifndef __SMACCM_test1_impl_Instance_types__H
#define __SMACCM_test1_impl_Instance_types__H

/**************************************************************************
  Copyright (c) 2013, 2014, 2015 Rockwell Collins and the University of Minnesota.
  Developed with the sponsorship of the Defense Advanced Research Projects Agency (DARPA).

  Permission is hereby granted, free of charge, to any person obtaining a copy of this data,
  including any software or models in source or binary form, as well as any drawings, specifications, 
  and documentation (collectively "the Data"), to deal in the Data without restriction, including 
  without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
  and/or sell copies of the Data, and to permit persons to whom the Data is furnished to do so, 
  subject to the following conditions: 

  The above copyright notice and this permission notice shall be included in all copies or
  substantial portions of the Data.

  THE DATA IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
  LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
  IN NO EVENT SHALL THE AUTHORS, SPONSORS, DEVELOPERS, CONTRIBUTORS, OR COPYRIGHT HOLDERS BE LIABLE 
  FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE DATA OR THE USE OR OTHER DEALINGS IN THE DATA. 

 **************************************************************************/


/**************************************************************************

   File: C:\docs\git_smaccm\smaccm\models\Trusted_Build_Test\vChan_demo\include\smaccm_test1_impl_types.h
   Created on: 2015/04/10 17:39:06
   using Dulcimer AADL system build tool suite 

   ***AUTOGENERATED CODE: DO NOT MODIFY***

  This file contains the datatypes used for communications between 
  AADL components as defined in the system implementation test1_impl_Instance.

 **************************************************************************/

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
// Headers for externally declared types.
typedef 
      struct { 
         int32_t domain  ; 
         int32_t dest  ; 
         int32_t thePort  ; 
      } vChan_demo__structs_vchan_ctrl ; 

typedef uint8_t vChan_demo__arrays_fourK_char [4096]; 

typedef 
      struct { 
         int32_t owner  ; 
         vChan_demo__arrays_fourK_char sync_data  ; 
         int32_t filled  ; 
         int32_t read_pos  ; 
         int32_t write_pos  ; 
      } vChan_demo__structs_vchan_buff ; 

typedef vChan_demo__structs_vchan_buff vChan_demo__arrays_two_buffs [2]; 

typedef 
      struct { 
         int32_t alloced  ; 
         vChan_demo__arrays_two_buffs bufs  ; 
      } vChan_demo__structs_vchan_shared_mem ; 

typedef vChan_demo__structs_vchan_shared_mem vChan_demo__arrays_shared_buffers [2]; 

typedef 
      struct { 
         vChan_demo__arrays_shared_buffers shared_buffers  ; 
         int32_t token  ; 
      } vChan_demo__structs_vchan_shared_mem_headers ; 

typedef 
      struct { 
         vChan_demo__structs_vchan_ctrl v  ; 
         int32_t server  ; 
         int32_t eventfd  ; 
         uint32_t event_mon  ; 
      } vChan_demo__structs_vchan_connect ; 

/* endif for: #ifndef __SMACCM_test1_impl_Instance_types__H */
#endif

/**************************************************************************
  End of autogenerated file: smaccm_test1_impl_types.h
 **************************************************************************/

