#ifndef _XJJUTI_H_
#define _XJJUTI_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <cstring>
#include <cmath>

namespace xjjuti
{
  template<size_t N>
  int findibin(const float (*array_)[N], float element_);
  template<size_t N>
  int findiedge(const float (*array_)[N], float element_);
  std::string number_to_string(float param_);
  std::string number_to_string(double param_);
  std::string number_to_string(int param_);
  std::string number_remove_zero(float param_);
  std::string number_remove_zero(double param_);
  void progressbar(int index_, int total_, int morespace_=0);
  void progressbar_summary(int total_);
}

//
template<size_t N>
int xjjuti::findibin(const float (*array_)[N], float element_)
{
  int ielement = -1;
  for(std::size_t i=0;i<((sizeof(*array_)/sizeof((*array_)[0]))-1) && ielement<0;i++)
    {
      if(element_>=(*array_)[i] && element_<(*array_)[i+1]) ielement = i;
    }
  return ielement;
}

template<size_t N>
int xjjuti::findiedge(const float (*array_)[N], float element_)
{
  int ielement = -1;
  for(std::size_t i=0;i<(sizeof(*array_)/sizeof((*array_)[0])) && ielement<0;i++)
    {
      if(element_==(*array_)[i]) ielement = i;
    }
  return ielement;
}

std::string xjjuti::number_to_string(float param_)
{
  if(param_<0) return "";
  std::string str = std::to_string(param_);
  std::size_t found = str.find('.');
  if(found==std::string::npos)
    {
      str+="p0";
      return str;
    }
  str.replace(found,1,"p");
  while(*(str.end()-1)=='0' && *(str.end()-2)!='p' && !str.empty()) str.erase(str.end()-1);
  return str;
}

std::string xjjuti::number_to_string(double param_)
{
  if(param_<0) return "";
  std::string str = std::to_string(param_);
  std::size_t found = str.find('.');
  if(found==std::string::npos)
    {
      str+="p0";
      return str;
    }
  str.replace(found,1,"p");
  while(*(str.end()-1)=='0' && *(str.end()-2)!='p' && !str.empty()) str.erase(str.end()-1);
  return str;
}

std::string xjjuti::number_to_string(int param_)
{
  if(param_<0) return "";
  std::string str = std::to_string(param_);
  std::size_t found = str.find('.');
  if(found==std::string::npos)
    {
      str+="p0";
      return str;
    }
  str.replace(found,1,"p");
  while(*(str.end()-1)=='0' && *(str.end()-2)!='p' && !str.empty()) str.erase(str.end()-1);
  return str;
}

std::string xjjuti::number_remove_zero(float param_)
{
  if(param_<0) return "";
  std::string str = std::to_string(param_);
  std::size_t found = str.find('.');
  if(found==std::string::npos) return str;
  while(*(str.end()-1)=='0') str.erase(str.end()-1);
  if(*(str.end()-1)=='.') str.erase(str.end()-1);
  return str;
}

std::string xjjuti::number_remove_zero(double param_)
{
  if(param_<0) return "";
  std::string str = std::to_string(param_);
  std::size_t found = str.find('.');
  if(found==std::string::npos) return str;
  while(*(str.end()-1)=='0') str.erase(str.end()-1);
  if(*(str.end()-1)=='.') str.erase(str.end()-1);
  return str;
}

void xjjuti::progressbar(int index_, int total_, int morespace_/*=0*/)
{
  std::cout<<std::setiosflags(std::ios::left)<<"  [ \033[1;36m"<<std::setw(10+morespace_)<<index_<<"\033[0m"<<" / "<<std::setw(10+morespace_)<<total_<<" ] "<<"\033[1;36m"<<std::fixed<<std::setprecision(0)<<100.*index_/total_<<"%\033[0m"<<"\r"<<std::flush;
}

void xjjuti::progressbar_summary(int total_)
{
  std::cout<<std::endl<<"  Processed "<<"\033[1;31m"<<total_<<"\033[0m event(s)."<<std::endl;
}


#endif
