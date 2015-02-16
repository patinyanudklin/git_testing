#include "dllclass.h"

int 
DllClassBase::virtual_method () const 
{ 
  return -1; 
}

DllClass::DllClass (int i) : i_(i) { ++instances; }
DllClass::~DllClass () { --instances; }

int 
DllClass::virtual_method () const 
{
  return i_ * i_ * i_; 
}

int 
DllClass::non_virtual_method () const 
{
  return i_ * i_;
}

int DllClass::instances;
